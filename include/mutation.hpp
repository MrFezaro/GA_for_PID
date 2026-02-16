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
    uniform_real_distribution probDist(0.0f, 1.0f);
    normal_distribution mutationDist(0.0f, mutationStrength);

    int geneCount = geneLimits.size();

    for (auto& ind : population) {
        for (int i = 0; i < geneCount - 1; ++i) {
            if (probDist(rng) < mutationRate) {

                ind[i] += mutationDist(rng) * geneLimits[i];
                ind[i] = clamp(ind[i], 0.0f, geneLimits[i]);
            }
        }
    }
}

#endif //MUTATION_HPP
