#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <chrono>

#include "TSP.hpp"
#include "instance.hpp"
#include "solution.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <instance_file> [seed] [max_iterations] [max_ils_iterations] [alpha]" << '\n';
        std::cerr << "  instance_file: TSP instance file path" << '\n';
        std::cerr << "  seed: Random seed (default: 0 = use time-based seed)" << '\n';
        std::cerr << "  max_iterations: GRASP iterations (default: 50)" << '\n';
        std::cerr << "  max_ils_iterations: ILS iterations (default: (|V| >= 150) ? |V|/2 : |V|)" << '\n';
        std::cerr << "  alpha: GRASP alpha parameter (default: 0.3)" << '\n';
        return 1;
    }

    // Read instance
    Instance instance(argc, argv[1]);
    instance.read();

    // Argparse
    uint64_t seed = (argc > 2) ? std::stoull(argv[2]) : 0;
    size_t max_iterations = (argc > 3) ? std::stoull(argv[3]) : 50;
    size_t max_ils_iterations = (argc > 4) ? std::stoull(argv[4]) : (instance.get_dimension() >= 150 ? instance.get_dimension() / 2 : instance.get_dimension());
    double alpha = (argc > 5) ? std::stod(argv[5]) : 0.3;

    // // Display configuration
    // std::cout << std::left;
    // std::cout << std::string(40, '=') << '\n';
    // std::cout << "GILS-RVND Configuration:" << '\n';
    // std::cout << std::setw(20) << "Instance:" << instance.get_name() << '\n';
    // std::cout << std::setw(20) << "GRASP iterations:" << max_iterations << '\n';
    // std::cout << std::setw(20) << "ILS iterations:" << max_ils_iterations << '\n';
    // std::cout << std::setw(20) << "Alpha:" << alpha << '\n';
    // std::cout << std::string(40, '=') << '\n';

    TSP tsp(instance, seed);

    uint64_t start = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> distrib(0.01, 1.0);
    double avg_objective = 0.0;

    for (size_t i = 0; i < 10; i++) {
        alpha = distrib(rng);
        Solution s = tsp.GILS_RVND(max_iterations, max_ils_iterations, alpha);
        avg_objective += s.objective;
    }

    uint64_t end = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    double avg_time = (end - start) / 10.0;
    avg_objective /= 10.0;

    std::cout << avg_objective << "," << avg_time / 1e9 << '\n';

    // std::cout << std::string(40, '=') << '\n';
    // std::cout << "Solution:" << '\n';   
    // std::cout << "Objective: " << s.objective << '\n';
    // std::cout << "Sequence: " << '\n';
    // s.print_sequence();
    // std::cout << std::string(40, '=') << '\n';

    return 0;
}
