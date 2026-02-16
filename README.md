# Genetic Algorithm PID Optimizer

This project implements a **Continuous Genetic Algorithm (CGA)** in C++ to optimize PID or SEC controller parameters. It evolves a population of controller parameter sets to minimize a defined error score for a simulated system.

## Features

- Population-based optimization
- Crossover and mutation operations
- Configurable PID parameter limits
- Goal-based stopping criteria
- Python script for simulation visualization

## Project Structure

- **`main.cpp`**  
  Contains the main GA loop and configuration of GA parameters.

- **Header Files (`*.hpp`)**  
  Contain additional parameters and definitions not directly related to the GA core loop:
  - `sorting.hpp` – Functions to sort and select the best population members
  - `population.hpp` – Population initialization and related utilities
  - `simulation.hpp` – Second order system simulation with PID or SEC controller
  - `crossover.hpp` – Crossover operations for GA
  - `mutation.hpp` – Mutation operations for GA

- **`testParameters.py`**  
  After running the GA, you can use `testParameters.py` to simulate the system with the resulting parameters and plot a step response graph.

## Configuration

In `main.cpp`, you can configure:

- `populationSize` – Number of candidate solutions per generation  
- `maxGenerations` – Maximum number of generations to run  
- `mutationRate` – Probability of mutation per gene  
- `mutationStrength` – Maximum change in a mutated gene  
- `goal` – Target score to stop evolution early  
- `genes` – Initial PID parameter limits and default score  

All other configuration parameters are located in the included header files:

- `sorting.hpp`
- `population.hpp`
- `simulation.hpp`
- `crossover.hpp`
- `mutation.hpp`

## Output

After running, the program outputs:

- Whether the goal was achieved or maximum generations were reached  
- Best score found  
- Best PID parameters (`Kp`, `Ki`, `Kd`)  

Example Output:
```
Goal achieved! Generation: 42
Best score: 0.102
Best parameters: Kp=12.3 Ki=8.5 Kd=0.7
```
### Acknowledgments
Shoutout to C++ and its std::vector data type <3
