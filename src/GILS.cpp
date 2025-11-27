#include "TSP.hpp"

Solution TSP::GILS_RVND(const size_t max_iterations, const size_t max_ils_iterations, double alpha) {
    Solution global_best;
    global_best.objective = INFINITY;

    // std::cout << "Starting GILS-RVND with " << max_iterations << " iterations and alpha = " << alpha << '\n';
    // std::cout << "Max ILS iterations: " << max_ils_iterations << '\n';
    // std::cout << "INFINITY: " << INFINITY << '\n';

    for (size_t i = 0; i < max_iterations; ++i) {
        Solution s = randomized(alpha);
        Solution local_best = s;

        // std::cout << "Iteration " << i + 1 << ": Initial solution objective = " << s.objective << '\n';

        size_t ils_iterations = 0;

        while (ils_iterations <= max_ils_iterations) {

            RVND(s);

            if (s.objective < local_best.objective) {
                local_best = s;
                ils_iterations = 0;
            }

            
            if (local_best.objective < global_best.objective) {
                global_best = local_best;
            }

            s = local_best;
            double_bridge(s);
            ++ils_iterations;
        }
    }
    
    return global_best;
}