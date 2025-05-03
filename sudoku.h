#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <filesystem>

#include "config.h"
#include "grid.h"
#include "keyboard.h"
#include "command.h"
#include "start.h"

using namespace std;


class Sudoku {
public:
    Sudoku(int index = 3);
    void eraseGrids(const int value);
    void generate();
    void game();
    void printGrid();
    bool setCurValue(const int nCurValue, int& nLastValue);
    bool setPointValue(const pt_r&, const int);
    pt_r getCurPoint();
    bool isComplete();
    
    void save(string filename);
    void load(string filename);
    void loop();
    void ptrinit();
    void difficulty();
private:
    void init();    
    void fillVals(const int);
    void printMargin(int num = -1) const;
    void fillVal(const pt_r &, const int);
private:
    int max_col;
    int grid_inerase;
    int user_action;
    pt_r cur_pt;
    Grid row_grid[9];
    Grid col_grid[9];
    Grid single_grid[3][3];
    pt_val_r sudoku_map[81];
    vector<Fill> _vCommand;
    Keyboard kb;
    Config cfg;
    vector<int> answers {KEY_Y, KEY_y, KEY_N, KEY_n};
};

inline void clean(void) {
    system("clear");
}