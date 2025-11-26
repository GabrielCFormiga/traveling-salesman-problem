#include "TSP.hpp"

void TSP::RVND(Solution &solution) {
    std::vector<TSP::Neighborhood> neighborhoods = {
        TSP::Neighborhood::Swap
    };

    bool improved;
    size_t neighborhood;

    while (!neighborhoods.empty()) {
        neighborhood = rand() % neighborhoods.size();

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