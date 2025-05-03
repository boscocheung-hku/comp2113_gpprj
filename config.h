#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include "keybind.h"

using namespace std;

class Config {
public:
    Config();
    void clear();
};

static const unsigned int NUL = 0;

enum class Status : int {
    INITED = 0,
    ERASED
};

using pt_r = struct pt_r {
    int x;
    int y;
};

using pt_val_r = struct pt_val_r {
    int value;
    Status status;
};

inline unsigned int random(int begin, int end) {
    random_device rd;
    mt19937 g(rd());
    return uniform_int_distribution<unsigned int>(begin, end)(g);
}

inline vector<int> get_num() {
    return vector<int> {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

inline vector<int> shuffle_num() {
    vector<int> num_list = get_num();
    random_device rd;
    mt19937 g(rd());
    shuffle(num_list.begin(),num_list.end(), g);
    return num_list;
}

