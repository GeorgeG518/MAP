#include <set>
#include <vector>
#include <iostream>
#include "map.h"
#include <algorithm>
#include <numeric>
#define DEBUG 1
bool match_comparator(const match &cost_l, const match &cost_r){

    return cost_l.cost<cost_r.cost;
}

void print_matches(const  std::vector<match>& matches){
    for(match m : matches){
        std::cout<<m.i << ' ' << m.j << ' ' << m.k << ' '<<std::endl;
    }
}
template <class T>
void print_vector(const std::vector<T>& vec){
    for(T item : vec){
        std::cout<< item << ' ';
    }
    std::cout << std::endl;
}

template <class T>
void print_set(const std::set<T>& s){
    for(T item : s){
        std::cout<< item << ' ';
    }
    std::cout << std::endl;
}

bool ijk_sort(const match &match1, const match &match2){
    if(match1.i<match2.i) return true;
    if(match2.i<match1.i) return false;
    
    if(match1.j<match2.j) return true;
    if(match2.j<match1.j) return false;

    if(match1.k<match2.k) return true;
    if(match2.k<match1.k) return false;
}

bool valid_choice(const match & m, std::set<int>& i_used,std::set<int>& j_used,std::set<int>& k_used){
    return i_used.find(m.i) == i_used.end() and \
    j_used.find(m.j)== j_used.end() and \
    k_used.find(m.k)== k_used.end();
}

bool valid_path(const  std::vector<match>& matches){
    if(matches.size()!=SOLUTION_LENGTH)
        return false;    
    bool valid=true;
    std::set<int> i_used;
    std::set<int> j_used;
    std::set<int> k_used;

    for(auto m : matches){
        if(valid_choice( m, i_used, j_used,k_used)){
            i_used.insert(m.i);
            j_used.insert(m.j);
            k_used.insert(m.k);

        }else{
            valid=false;
        }
    }
    return valid;
}

std::vector<int> return_possible_picks(const std::vector<match> matches, std::set<int> i_used,std::set<int> j_used,std::set<int> k_used){
    std::vector<int> options;
    for(int i=0; i<matches.size(); i++){
        if(valid_choice( matches[i], i_used, j_used,k_used)){
            options.push_back(i);
        }
    }

    return options;
}

std::forward_list<match> brute_force(const std::vector<match> matches){
    float GLOBAL_MIN_COST = FLT_MAX;
    std::forward_list<match> final_path;
    int current_node = 0;
    int num_nodes=matches.size();
    for (auto it = matches.begin(); it!=matches.end(); ++it) {
        std::set<int> i_used;
        std::set<int> j_used;
        std::set<int> k_used;
        std::stack<int> frontier;
        std::vector<bool> visited;
        std::vector<match> current_solution;
        //visited=std::vector<bool>(num_nodes, false);

        int match_index=std::distance(matches.begin(),it);
        frontier.push(match_index);
        while(!frontier.empty()){
            if(DEBUG){
                std::cout<<"Stack size: " << frontier.size() <<" nodes left to be explored"<<std::endl;
            }
            int index=frontier.top();
            frontier.pop();         
            match m=matches[index];
            current_solution.push_back(m);
            i_used.insert((m).i);
            j_used.insert((m).j);
            k_used.insert((m).k);
            if(valid_path(current_solution)){
                std::cout<<"Choice Found"<<std::endl;
                print_vector(current_solution);
                i_used.erase(m.i);
                j_used.erase(m.j);
                k_used.erase(m.k);
                current_solution.pop_back();
                continue;
            }else if(current_solution.size()==SOLUTION_LENGTH){ // i.e. it wasn't valid path, but it had right size
                std::cout<<"Bad Choice Found"<<std::endl;
                print_vector(current_solution);
                i_used.erase(m.i);
                j_used.erase(m.j);
                k_used.erase(m.k);
                current_solution.pop_back();                
                continue;
            }

            std::vector<int> picks=return_possible_picks(matches, i_used, j_used, k_used);

            for(int pick: picks){
                if(DEBUG){
                    std::cout << "Adding pick to queue..." << pick<<std::endl;
                }
                frontier.push(pick);
            }
        }
        break; // only do one node

    }
    return final_path;
}

int main()
{
    // Seed the random number generator
    std::srand(std::time(0));
    int SIZE=3;
    // Declare a SIZExSIZExSIZE matrix
    double max_value = 6000;
    // Fill the matrix with random values
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for(int k=0; k<SIZE;++k){
                double value = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_value)));
                match_vector.emplace_back(i,j,k,value);
            }
        }
    }
    std::cout << "Match vector size: " << match_vector.size()<<std::endl;
    std::set<int> i_used;
    std::set<int> j_used;
    std::set<int> k_used;
    std::vector<int> indices(match_vector.size());
    iota(indices.begin(), indices.end(),0);


    std::sort(indices.begin(), indices.end(), [&] (int i1, int i2) {return match_vector[i1].cost<match_vector[i2].cost;});
    std::sort(match_vector.begin(), match_vector.end(), ijk_sort);

    //print_matches(match_vector);
    brute_force(match_vector);
    return 0;
}