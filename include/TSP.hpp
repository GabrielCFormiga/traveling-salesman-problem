#ifndef TSP_HPP
#define TSP_HPP

#include <instance.hpp>
#include <solution.hpp>
#include <random>

class TSP {
    private:
        Instance m_instance;

        std::mt19937_64 m_rng;

    public:
        enum class Neighborhood : uint8_t { Swap , _2_OPT };

        TSP(Instance &instance, uint64_t seed = 0);
        
        // Constructive heuristics
        Solution randomized(double alpha);

        // Local Search Procedures
        void RVND(Solution &solution);

        // Neighborhoods
        bool best_improvement_swap(Solution &solution);
        bool best_improvement_2_opt(Solution &solution);
        // bool best_improvement_or_opt(Solution &solution, size_t segment_size);

        // Methaheuristics
        Solution GILS_RVND(const size_t max_iterations, const size_t max_ils_iterations, double alpha);

        // Perturbations
        void double_bridge(Solution &solution);  
};

#endif