#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

double objectiveFunction(double x) {
    return x * x;
}

double getRandom(double lower_bound, double upper_bound) {
    return lower_bound + static_cast<double>(rand()) / RAND_MAX * (upper_bound - lower_bound);
}

double hillClimbing(double lower_bound, double upper_bound, double step_size, int max_iterations) {
    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Step 1: Initialize the current solution
    double current_solution = getRandom(lower_bound, upper_bound);
    double current_value = objectiveFunction(current_solution);

    for (int iteration = 0; iteration < max_iterations; ++iteration) {
        // Step 4: Generate neighboring solution by perturbing the current solution
        double new_solution = current_solution + getRandom(-step_size, step_size);
        
        // Keep new solution within bounds
        if (new_solution < lower_bound) new_solution = lower_bound;
        if (new_solution > upper_bound) new_solution = upper_bound;

        double new_value = objectiveFunction(new_solution);

        // Update if the new solution is better
        if (new_value < current_value) {
            current_solution = new_solution;
            current_value = new_value;
        } else {
            // Decrease step size to refine the search
            step_size *= 0.9;
        }
    }

    return current_solution;
}

int main() {
    double lower_bound = -5.0;
    double upper_bound = 5.0;
    double step_size = 1.0;
    int max_iterations = 1000;

    // Run hill climbing
    double solution = hillClimbing(lower_bound, upper_bound, step_size, max_iterations);

    std::cout << "Optimal solution: x = " << solution << std::endl;
    std::cout << "Minimum value of f(x) = " << objectiveFunction(solution) << std::endl;

    return 0;
}
