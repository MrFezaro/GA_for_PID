# Genetic Algorithm PID Optimizer

This project implements a **Continuous Genetic Algorithm (CGA)** in C++ to optimize PID and SEC controller parameters. It evolves a population of controller parameter sets to minimize a defined error score for a simulated system.

## Features

- Population-based optimization
- Crossover and mutation operations
- Configurable PID parameter limits
- Goal-based stopping criteria

## Project Structure

- `main.cpp` – Contains the main GA loop and configuration of GA parameters like population size, mutation rate, and goal threshold.
- Header files (`*.hpp`) – Contain additional parameters and definitions not directly related to the GA:
  - `sorting.hpp` – Functions to sort and select the best population members
  - `population.hpp` – Population initialization and related utilities
  - `simulation.hpp` – System simulation logic for PID evaluation
  - `crossover.hpp` – Crossover operations for GA
  - `mutation.hpp` – Mutation operations for GA

#
 Shoutout to C++ and their vector data type <3
