//
// Created by meet on 6/7/25.
//

#ifndef PAIRHELPERS_H
#define PAIRHELPERS_H
#include <cstddef>

struct mug_int_pair_hash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        // A simple hash combiner
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

struct mug_int_pair_equal {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        return a.first == b.first && a.second == b.second;
    }
};


#endif //PAIRHELPERS_H
