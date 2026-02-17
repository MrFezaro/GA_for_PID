#include "sorting.hpp"
#include "population.hpp"
#include "simulation.hpp"
#include "crossover.hpp"
#include "mutation.hpp"

int main() {
    // Configuration
    int populationSize = 10000;
    int maxGenerations = 1000;
    int generation = 0;
    float mutationRate = 0.5;
    float mutationStrength = 0.01;
    float goal = 0.1;
    vector<float> genes = {20, 20, 20, 100000}; // PID parameter limits + default score
    //vector<float> genes = {5, 5, 5, 10, 10, 100000}; // SEC parameter limits + default score

    // Generate population
    vector<vector<float>> population = makePopulation(populationSize, genes);

    // Evolution loop
    while (generation < maxGenerations) {
        // Simulate system and store scores in population
        simulateSystemPID(population);
        //simulateSystemSEC(population);
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

    // Check if best score meets goal and print results
    if (population[0].back() < goal) {
        cout << "Goal achieved!" << '\n' << "Generation: " << generation << '\n';
        cout << "Best score: " << population[0].back() << '\n';
        cout << "Best parameters: Kp=" << population[0][0] << " Ki=" << population[0][1] << " Kd=" << population[0][2] << '\n';
        //cout << "Best parameters: Ks=" << population[0][0] << " Ke=" << population[0][1] << " Kc=" << population[0][2]
        //     << " Ts=" << population[0][3] << " Tc=" << population[0][4] <<'\n';
        return 0;
    }
    cout << "Max generations reached without achieving goal." << '\n';
    cout << "Best score: " << population[0].back() << '\n';
    cout << "Best parameters: Kp=" << population[0][0] << " Ki=" << population[0][1] << " Kd=" << population[0][2] << '\n';
    //cout << "Best parameters: Ks=" << population[0][0] << " Ke=" << population[0][1] << " Kc=" << population[0][2]
    //         << " Ts=" << population[0][3] << " Tc=" << population[0][4] <<'\n';
    return 69;
}
