#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP

#include <random>
#include <vector>
using namespace std;

inline void crossover(vector<vector<float>>& population, int targetPopulationSize) {
    mt19937 rng(random_device{}());
    uniform_int_distribution<> parentDist(0, population.size() - 1);

    int geneCount = population[0].size();

    while (population.size() < targetPopulationSize) {

        const auto& p1 = population[parentDist(rng)];
        const auto& p2 = population[parentDist(rng)];

        vector child(geneCount, 100.0f);

        int crossPoint = rng() % (geneCount - 2) + 1;

        for (int i = 0; i < geneCount - 1; ++i) {
            child[i] = (i < crossPoint) ? p1[i] : p2[i];
        }

        child.back() = 100000.0f; // reset score
        population.push_back(child);
    }
}

#endif //CROSSOVER_HPP
