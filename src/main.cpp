#include <iostream>

#include "TSP.hpp"
#include "instance.hpp"
#include "solution.hpp"

int main(int argc, char **argv) {
    Instance instance(argc, argv[1]);
    instance.read();

    TSP tsp(instance);

    Solution s = tsp.GILS_RVND(10, 100, 0.3);

    std::cout << "Objective: " << s.objective << '\n';
    s.print_sequence();

    return 0;
}
