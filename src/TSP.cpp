#include "TSP.hpp"
#include <chrono>

TSP::TSP(Instance &instance, uint64_t seed) : m_instance(instance) {
    if (seed == 0) {
        seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    
    m_rng.seed(seed);
    
    std::cout << "RNG seed: " << seed << std::endl;
}