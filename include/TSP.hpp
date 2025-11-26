#ifndef TSP_HPP
#define TSP_HPP

#include <instance.hpp>
#include <solution.hpp>

class TSP {
    private:
        Instance m_instance;

    public:
        TSP(Instance &instance);
        
        // Constructive heuristics
        Solution randomized(double alpha);

        // Local Search Procedures
        void RNVD(Solution &solution);

};

#endif