#pragma once

#include <iostream>
#include <cassert>
#include "config.h"
using namespace std;

class Grid {
    static const int MAX_COUNT = 9;
public:
    Grid();
    bool isValid() const;
    bool isFull() const;
    void print(int cur_point = -1) const;
    void push_back(pt_val_r *point);
private:
    int count;
    pt_val_r *numbers[MAX_COUNT];
};