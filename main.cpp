#include <iostream>
#include "sudoku.h"
using namespace std;

Sudoku sudoku;

int main() {
    printf("\033[?25l");
    sudoku.ptrinit();
    sudoku.loop();
}
