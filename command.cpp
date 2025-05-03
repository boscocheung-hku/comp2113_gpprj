#include "sudoku.h"
#include "command.h"

Fill::Fill(Sudoku *ptr) : _ptr(ptr)
{}

Fill::Fill(Sudoku *ptr, const pt_r &point, int preValue, int curValue)
    : _ptr(ptr), ranpt(point), _Preval(preValue), _Curval(curValue) {}

Fill::Fill(const Fill &rhs)
: _ptr(rhs._ptr)
, ranpt(rhs.ranpt)
, _Preval(rhs._Preval)
, _Curval(rhs._Curval)
{}

Fill::~Fill(){}

bool Fill::execute(int nInputValue)
{
    if (!_ptr)
        return false;

    ranpt = _ptr->getCurPoint();
    return _ptr->setCurValue(nInputValue, _Preval);
}

void Fill::undo()
{
    if (_ptr)
    {
        _ptr->setPointValue(ranpt, _Preval);
    }

    return;
}