#include "TSP.hpp"
#include <algorithm>

Solution TSP::randomized(double alpha) {
    Solution solution(m_instance);
    
    // 1) Choose three random nodes to compose an initial solution
    // sequence = {1, x, y, z, 1}
    
    solution.sequence.push_back(1);

    size_t x, y, z;

    std::uniform_int_distribution<size_t> distrib(2, m_instance.get_dimension());
    
    x = distrib(m_rng);
    
    do {
        y = distrib(m_rng);
    } while (y == x);
    
    do {
        z = distrib(m_rng);
    } while (z == x || z == y);
    
    solution.sequence.push_back(x);
    solution.sequence.push_back(y);
    solution.sequence.push_back(z);
    solution.sequence.push_back(1);

    std::vector<bool> used(m_instance.get_dimension() + 1, false);
    used[1] = true;
    used[x] = true;
    used[y] = true;
    used[z] = true;

    // 2) Insert the remaining nodes using a randomized insertion heuristic
    std::vector<std::pair<double, std::pair<size_t, size_t>>> insertions; // {cost, {k, i}}

    while (true) {
        insertions.clear();

        for (size_t k = 2; k <= m_instance.get_dimension(); k++) {
            if (used[k]) continue;

            for (size_t i = 0; i < solution.sequence.size() - 1; i++) {
                double insertion_cost = m_instance.get_distance(solution.sequence[i], k) +
                                       m_instance.get_distance(k, solution.sequence[i + 1]) -
                                       m_instance.get_distance(solution.sequence[i], solution.sequence[i + 1]);
                insertions.push_back({insertion_cost, {k, i}});
            } 
        }

        if (insertions.empty()) break;

        sort(insertions.begin(), insertions.end());

        size_t limit = static_cast<size_t>(floor(alpha * insertions.size())) + 1;
        std::uniform_int_distribution<size_t> distrib(0, limit - 1);
        size_t ind = distrib(m_rng);
        
        size_t k = insertions[ind].second.first;
        size_t i = insertions[ind].second.second;
        solution.sequence.insert(solution.sequence.begin() + i + 1, k);
        used[k] = true;
    }

    solution.update_objective(m_instance);
    return solution;
}