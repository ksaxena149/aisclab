import numpy as np

# Objective function: f(x) = x^2
def objective(x):
    return x**2

# Hill climbing algorithm
def hillclimbing(objective, bounds, n_iterations, step_size):
    # Initialize the current solution randomly within bounds
    solution = np.random.uniform(bounds[0], bounds[1])
    # Evaluate the current solution
    solution_eval = objective(solution)
    print(f"Initial solution: x = {solution}, f(x) = {solution_eval}")
    
    # Run the hill climbing search
    for i in range(n_iterations):
        # Generate a new candidate by perturbing the current solution
        candidate = solution + np.random.randn() * step_size
        # Ensure the candidate is within the bounds
        candidate = np.clip(candidate, bounds[0], bounds[1])
        # Evaluate the candidate solution
        candidate_eval = objective(candidate)
        
        # If the candidate is better, update the solution
        if candidate_eval < solution_eval:
            solution, solution_eval = candidate, candidate_eval
            print(f"Iteration {i+1}: x = {solution}, f(x) = {solution_eval}")
    
    return solution, solution_eval

# Seed the random number generator for reproducibility
np.random.seed(5)

# Define parameters
bounds = [-5.0, 5.0]  # Search space bounds
n_iterations = 100     # Number of iterations
step_size = 0.1        # Maximum step size

# Perform the hill climbing search
best_solution, best_score = hillclimbing(objective, bounds, n_iterations, step_size)

# Print the final result
print("Done!")
print(f"Best solution: x = {best_solution}, f(x) = {best_score}")
