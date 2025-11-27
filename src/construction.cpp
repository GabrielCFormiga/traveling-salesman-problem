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

    std::vector<size_t> candidates;

    for (size_t i = 2; i <= m_instance.get_dimension(); ++i) {
        if (i != x && i != y && i != z) {
            candidates.push_back(i);
        }
    }

    solution.objective += m_instance.get_distance(1, x) + m_instance.get_distance(x, y) + m_instance.get_distance(y, z) + m_instance.get_distance(z, 1);

    // 2) Insert the remaining nodes using a randomized insertion heuristic
    std::vector<std::pair<std::pair<double, size_t>, std::pair<size_t, size_t>>> insertions; // {{cost, j}, {k, i}}

    while (!candidates.empty()) {
        insertions.clear();

        for (size_t j = 0; j < candidates.size(); ++j) {
            for (size_t i = 0; i < solution.sequence.size() - 1; i++) {
                size_t k = candidates[j];
                double insertion_cost = m_instance.get_distance(solution.sequence[i], k) + m_instance.get_distance(k, solution.sequence[i + 1]) - m_instance.get_distance(solution.sequence[i], solution.sequence[i + 1]);
                insertions.push_back({{insertion_cost, j}, {k, i}});
            } 
        }

        sort(insertions.begin(), insertions.end());

        size_t limit = static_cast<size_t>(floor(alpha * insertions.size())) + 1;
        std::uniform_int_distribution<size_t> distrib(0, limit - 1);
        size_t ind = distrib(m_rng);
        
        solution.objective += insertions[ind].first.first;
        size_t k = insertions[ind].second.first;
        size_t i = insertions[ind].second.second;
        solution.sequence.insert(solution.sequence.begin() + i + 1, k);
        std::swap(candidates[insertions[ind].first.second], candidates[candidates.size() - 1]);
        candidates.pop_back();
    }

    assert(solution.test_feasibility(m_instance));
    
    return solution;
}