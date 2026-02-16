#ifndef SORTING_HPP
#define SORTING_HPP

#include <vector>
#include <algorithm>
using namespace std;

inline void selectBestHalf(vector<vector<float>>& population) {

    // Sort ascending by score (lower error is better)
    ranges::sort(population,[](const vector<float>& a, const vector<float>& b) {
        return a.back() < b.back();
    });

    // Keep only best half
    population.resize(population.size() / 2);
}

#endif
