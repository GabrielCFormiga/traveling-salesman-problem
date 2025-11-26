#include "TSP.hpp"

// Always has sequence[0] == sequence.back() == 1

bool TSP::best_improvement_swap(Solution &solution) {
    double best_delta = 0.0;
    size_t best_i = 0, best_j = 0;

    for (size_t i = 1; i < solution.sequence.size() - 2; ++i) {
        for (size_t j = i + 1; j < solution.sequence.size() - 1; ++j) {
            double delta = 0;

            if (j == i + 1) {
                // Remove edges
                delta -= m_instance.get_distance(solution.sequence[i - 1], solution.sequence[i]);
                delta -= m_instance.get_distance(solution.sequence[j], solution.sequence[j + 1]);
            
                // Add edges
                delta += m_instance.get_distance(solution.sequence[i - 1], solution.sequence[j]);
                delta += m_instance.get_distance(solution.sequence[i], solution.sequence[j + 1]);
            } else {
                // Remove edges
                delta -= m_instance.get_distance(solution.sequence[i - 1], solution.sequence[i]);
                delta -= m_instance.get_distance(solution.sequence[i], solution.sequence[i + 1]);
                delta -= m_instance.get_distance(solution.sequence[j - 1], solution.sequence[j]);
                delta -= m_instance.get_distance(solution.sequence[j], solution.sequence[j + 1]);

                // Add edges
                delta += m_instance.get_distance(solution.sequence[i - 1], solution.sequence[j]);
                delta += m_instance.get_distance(solution.sequence[j], solution.sequence[i + 1]);
                delta += m_instance.get_distance(solution.sequence[j - 1], solution.sequence[i]);
                delta += m_instance.get_distance(solution.sequence[i], solution.sequence[j + 1]);
            }

            if (delta < best_delta) {
                best_delta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (best_delta < 0) {
        std::swap(solution.sequence[best_i], solution.sequence[best_j]);
        solution.objective += best_delta;
        // PRECISO APRENDER O DEBUG MODE
        // assert(solution.test_feasibility(m_instance)); 
    }

    return best_delta < 0;
}