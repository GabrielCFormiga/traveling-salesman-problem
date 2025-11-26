#include "solution.hpp"

#include <iostream>

Solution::Solution(const Instance &instance) {
    sequence.reserve(instance.get_dimension() + 1);
    objective = 0.0;
}

void Solution::print_sequence() const {
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << (i == sequence.size() - 1 ? "\n" : " -> "); 
    }
}

void Solution::update_objective(const Instance &data) {
    // poderia atualizar direto objective
    // mas vou criar um new para entar usar um modo debug depois

    double new_objective = 0;
    for (size_t i = 0; i < sequence.size() - 1; i++) {
        new_objective += data.get_distance(sequence[i], sequence[i + 1]);
    }
    
    // queria usar asserts no modo debug
    // testar a viabilidade aqui?
    objective = new_objective;
}