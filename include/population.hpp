#ifndef POPULATION_HPP
#define POPULATION_HPP

#include <random>
#include <vector>
#include <iostream>
using namespace std;

inline vector<vector<float>> makePopulation(int populationSize, const vector<float>& genes) {
    int geneNumber = genes.size();
    vector population(populationSize, vector(geneNumber, 0.0f));

    mt19937 rng(random_device{}());

    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < geneNumber - 1; ++j) {   // exclude score index
            uniform_real_distribution dist(0.0f, genes[j]);
            population[i][j] = dist(rng);
        }
    }

    return population;
}

inline void printPopulation(vector<vector<float>> &population) {
    for (auto &ind : population) {
        for (float value : ind) {
            cout << value << " ";
        }
        cout << '\n';
    }
}

#endif
