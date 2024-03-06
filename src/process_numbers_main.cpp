#include <fstream>
#include <iostream>

#include "process_numbers.hpp"

int main(){
    std::ifstream input{"rand_number.txt"};
    std::ofstream odds{"odd.txt"};
    std::ofstream evens{"evens.txt"};
    split_odd_even(input,odds,evens);
}

