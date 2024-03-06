#include "process_numbers.hpp"
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <ranges>

void split_odd_even(std::istream& numbers,
                    std::ostream& odds, std::ostream& evens) {
    using namespace std;

    vector<int> nums(istream_iterator<int>{numbers}, {});

    ranges::sort(nums);

    ranges::copy_if(nums, ostream_iterator<int>{odds, " "},
                    [](int n) { return n % 2 != 0; });
    odds << '\n';

    ranges::copy_if(nums, ostream_iterator<int>{evens, "\n"},
                    [](int n) { return n % 2 == 0; });
}