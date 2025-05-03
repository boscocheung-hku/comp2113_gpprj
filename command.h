#pragma once

#include <memory>
#include "config.h"

class Sudoku;
class Fill
{
public:
    Fill(Sudoku* pOwner);
    Fill(Sudoku *pOwner, const pt_r &point, int preValue, int curValue);
    Fill(const Fill &);
    ~Fill();

    bool execute(int nInputValue);
    void undo();
    pt_r getPoint() { return ranpt; }
    int getPreValue() { return _Preval; }
    int getCurValue() { return _Curval; }
    void setPoint(const pt_r &point) { ranpt = point; }
    void setPreValue(int preValue) { _Preval = preValue; }
    void setCurValue(int curValue) { _Curval = curValue; }

private:
    Sudoku* _ptr;
    pt_r ranpt;
    int _Preval;
    int _Curval;
};