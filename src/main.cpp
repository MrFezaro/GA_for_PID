#include "population.hpp"
#include "simulation.hpp"

int main() {
    int populationSize = 4;
    int geneNumber = 4;
    float geneLimit = 1.0;

    // Generate population
    vector<vector<float>> population = makePopulation(populationSize, geneNumber, geneLimit);

    // Simulate system and store scores in population
    simulateSystem(population);

    // Print results
    printPopulation(population);

    return 69;
}
