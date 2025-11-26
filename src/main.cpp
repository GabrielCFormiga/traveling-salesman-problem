#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "TSP.hpp"
#include "instance.hpp"
#include "solution.hpp"


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <instance_file> [seed] [max_iterations] [max_ils_iterations] [alpha]" << '\n';
        std::cerr << "  instance_file: TSP instance file path" << '\n';
        std::cerr << "  seed: Random seed (default: 0 = use time-based seed)" << '\n';
        std::cerr << "  max_iterations: GRASP iterations (default: 10)" << '\n';
        std::cerr << "  max_ils_iterations: ILS iterations (default: 100)" << '\n';
        std::cerr << "  alpha: GRASP alpha parameter (default: 0.3)" << '\n';
        return 1;
    }

    // Read instance
    Instance instance(argc, argv[1]);
    instance.read();

    // Argparse
    uint64_t seed = (argc > 2) ? std::stoull(argv[2]) : 0;
    size_t max_iterations = (argc > 3) ? std::stoull(argv[3]) : 10;
    size_t max_ils_iterations = (argc > 4) ? std::stoull(argv[4]) : 100;
    double alpha = (argc > 5) ? std::stod(argv[5]) : 0.3;

    // Display configuration
    std::cout << std::left;
    std::cout << std::string(40, '=') << '\n';
    std::cout << "GILS-RVND Configuration:" << '\n';
    std::cout << std::setw(20) << "Instance:" << instance.get_name() << '\n';
    std::cout << std::setw(20) << "GRASP iterations:" << max_iterations << '\n';
    std::cout << std::setw(20) << "ILS iterations:" << max_ils_iterations << '\n';
    std::cout << std::setw(20) << "Alpha:" << alpha << '\n';
    std::cout << std::string(40, '=') << '\n';

    TSP tsp(instance, seed);

    Solution s = tsp.GILS_RVND(max_iterations, max_ils_iterations, alpha);

    std::cout << std::string(40, '=') << '\n';
    std::cout << "Solution:" << '\n';   
    std::cout << "Objective: " << s.objective << '\n';
    std::cout << "Sequence: " << '\n';
    s.print_sequence();
    std::cout << std::string(40, '=') << '\n';

    return 0;
}
