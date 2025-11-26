#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

#include "instance.hpp"

struct Solution {
    std::vector<int> sequence;
  
    double objective;

    Solution() = default;
    Solution(const Instance &instance);

    void update_objective(const Instance &data);
  
    void print_sequence() const;
};

#endif