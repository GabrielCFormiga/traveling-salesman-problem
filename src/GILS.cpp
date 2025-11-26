#include "solution.hpp"

Solution GILS_RVND(const size_t max_iterations, const size_t max_ils_iterations) {
    Solution global_best;
    global_best.objective = INFINITY;

    for (size_t i = 0; i < max_iterations; ++i) {
        Solution s;
        Solution local_best = s;

        size_t ils_iterations = 0;

        while (ils_iterations <= max_ils_iterations) {
            RNVD(s);

            if (s.objective < local_best.objective) {
                local_best = s;
                ils_iterations = 0;
            }

            perturbation(s);

            if (local_best.objective < global_best.objective) {
                global_best = local_best;
            }
        }
    }
    
    return global_best;
}