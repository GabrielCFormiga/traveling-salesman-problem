#include "TSP.hpp"

void TSP::RVND(Solution &solution) {
    std::vector<TSP::Neighborhood> neighborhoods = {
        TSP::Neighborhood::Swap
    };

    bool improved;
    size_t neighborhood;

    while (!neighborhoods.empty()) {
        std::uniform_int_distribution<size_t> distrib(0, neighborhoods.size() - 1);
        neighborhood = distrib(m_rng);

        switch (neighborhoods[neighborhood]) {
            case TSP::Neighborhood::Swap:
                improved = best_improvement_swap(solution);
                break;
        }

        if (improved) {
            neighborhoods = {
                TSP::Neighborhood::Swap
            };
        } else {
            neighborhoods.erase(neighborhoods.begin() + neighborhood);
        }
    }
    
}