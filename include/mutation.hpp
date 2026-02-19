#ifndef MUTATION_HPP
#define MUTATION_HPP

#include <random>
#include <algorithm>
using namespace std;

inline void mutate(
    vector<vector<float>>& population,
    const vector<float>& geneLimits,
    float mutationRate,
    float mutationStrength)
{
    mt19937 rng(random_device{}());
    uniform_real_distribution<float> probDist(0.0f, 1.0f);
    normal_distribution<float> mutationDist(0.0f, mutationStrength);

    int geneCount = geneLimits.size();
    int eliteCount = static_cast<int>(population.size() * 0.10f);

    for (int idx = eliteCount; idx < population.size(); ++idx) {
        auto& ind = population[idx];

        for (int i = 0; i < geneCount - 1; ++i) {
            if (probDist(rng) < mutationRate) {
                ind[i] += mutationDist(rng) * geneLimits[i];
                ind[i] = clamp(ind[i], 0.0f, geneLimits[i]);
            }
        }
    }
}

#endif //MUTATION_HPP
