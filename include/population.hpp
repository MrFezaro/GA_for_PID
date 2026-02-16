#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <random>
#include <vector>
#include <iostream>
using namespace std;

inline vector<vector<float>> makePopulation(int populationSize, int geneNumber, float geneLimit) {
    vector population(populationSize, vector<float>(geneNumber, 0.0f));

    mt19937 rng(random_device{}());
    uniform_real_distribution<float> dist(0.0f, geneLimit);

    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < geneNumber - 1; ++j) {
            population[i][j] = dist(rng);
        }
    }
    return population;
}

inline void printPopulation(const vector<vector<float>> &population) {
    for (int i = 0; i < population.size(); ++i) {
        for (int j = 0; j < population[i].size(); ++j) {
            cout << population[i][j] << " ";
        }
        cout << '\n';
    }
}

#endif

