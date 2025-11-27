#include "TSP.hpp"

void TSP::RVND(Solution &solution) {
    std::vector<TSP::Neighborhood> neighborhoods = {
        TSP::Neighborhood::SWAP,
        TSP::Neighborhood::_2_OPT,
        // TSP::Neighborhood::REINSERTION, 
        // TSP::Neighborhood::OR_OPT_2, 
        // TSP::Neighborhood::OR_OPT_3
    };

    bool improved;
    size_t neighborhood;

    while (!neighborhoods.empty()) {
        std::uniform_int_distribution<size_t> distrib(0, neighborhoods.size() - 1);
        neighborhood = distrib(m_rng);

        switch (neighborhoods[neighborhood]) {
            case TSP::Neighborhood::SWAP:
                improved = best_improvement_swap(solution);
                break;
            case TSP::Neighborhood::_2_OPT:
                improved = best_improvement_2_opt(solution);
                break;
            case TSP::Neighborhood::REINSERTION:
                improved = best_improvement_or_opt(solution, 1);
                break;
            case TSP::Neighborhood::OR_OPT_2:
                improved = best_improvement_or_opt(solution, 2);
                break;
            case TSP::Neighborhood::OR_OPT_3:
                improved = best_improvement_or_opt(solution, 3);
                break;
        }

        if (improved) {
            neighborhoods = {
                TSP::Neighborhood::SWAP,
                TSP::Neighborhood::_2_OPT,
                // TSP::Neighborhood::REINSERTION,
                // TSP::Neighborhood::OR_OPT_2,
                // TSP::Neighborhood::OR_OPT_3
            };
        } else {
            neighborhoods.erase(neighborhoods.begin() + neighborhood);
        }
    }
    
}