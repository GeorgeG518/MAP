#include <vector>
#include <tuple>
#include <iterator>
#include <forward_list>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <ostream>
#include <stack>
#include <algorithm>

typedef struct match{
    int i;
    int j;
    int k;
    double cost;
    match(int i, int j, int k, double cost)
        : i(i),j(j), k(k), cost(cost){};
    std::ostream& ijk(std::ostream &o){
        return o << " " << this->i << " " << this->j<< " " << this->k << std::endl;
    }
} match;

std::ostream& operator <<(std::ostream& o, const match& m) {
    return o << " " << m.i << " " << m.j<< " " << m.k ;
}

int SOLUTION_LENGTH=3;

std::vector<match> match_vector;
std::vector<int> indices;

bool match_comparator(const match &, const match &);
void print_matches(const  std::vector<match>);

bool ijk_sort(const match &, const match &);
bool valid_choice(const match &, std::set<int>& ,std::set<int>& ,std::set<int>& );
bool valid_path(const  std::vector<match>& );

std::vector<int> return_possible_picks(const std::vector<match>, std::set<int>,std::set<int>,std::set<int>);
std::forward_list<match> brute_force(const std::vector<match>);