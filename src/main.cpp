#include "sorting.hpp"
#include "population.hpp"
#include "simulation.hpp"
#include "crossover.hpp"
#include "mutation.hpp"

int main() {
    // Configuration
    int populationSize = 1000;
    int maxGenerations = 100;
    int generation = 0;
    float mutationRate = 0.5;
    float mutationStrength = 0.01;
    float goal = 0.115;
    vector<float> genes = {10, 10, 10, 100}; // PID parameter limits + default score

    // Generate population
    vector<vector<float>> population = makePopulation(populationSize, genes);

    // Evolution loop
    while (generation < maxGenerations) {
        // Simulate system and store scores in population
        simulateSystemPID(population);
        // Sort population by score
        selectBestHalf(population);
        // Check if best score meets goal
        if (population[0].back() <= goal)
            break;
        // Crossover
        crossover(population, populationSize);
        // Mutation
        mutate(population, genes, mutationRate, mutationStrength);

        generation++;
    }

    cout << "I <3 C++ and vectors!" << '\n';

    // Check if best score meets goal and print results
    if (population[0].back() < goal) {
        cout << "Goal achieved! Generation: " << generation << '\n';
        cout << "Best score: " << population[0].back() << '\n';
        cout << "Best parameters: Kp=" << population[0][0] << " Ki=" << population[0][1] << " Kd=" << population[0][2] << '\n';
        return 0;
    }
    cout << "Max generations reached without achieving goal." << '\n';
    cout << "Best score: " << population[0].back() << '\n';
    cout << "Best parameters: Kp=" << population[0][0] << " Ki=" << population[0][1] << " Kd=" << population[0][2] << '\n';

    return 69;
}
