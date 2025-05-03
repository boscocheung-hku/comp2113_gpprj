#include "grid.h"
#include <cassert>

Grid::Grid() : count(0) {
}

void Grid::print(int cur_point) const {
    cout << pipe << " ";
    for (int i = 0; i < count; ++i) {
      auto number = *(numbers[i]);
      char num;

      if (number.value == 0) {
        num = ' ';
     }
      else {
        num = '0' + static_cast<char>(number.value);
      }
  
      std::cout << num << " " << pipe << " ";
    }
    std::cout << std::endl;
}
void Grid::push_back(pt_val_r *point) {
    assert(nullptr != point);
    numbers[count++] = point;
}

bool Grid::isValid() const
{
    assert(MAX_COUNT == count);

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
            if (NUL == numbers[i]->value || NUL == numbers[j]->value)
                continue;

            if (numbers[i]->value == numbers[j]->value)
                return false;
        }
    }

    return true;
}

bool Grid::isFull() const
{
    for (int i = 0; i < count; ++i)
    {
        pt_val_r *p_point_value = numbers[i];
        if (nullptr == p_point_value || NUL == p_point_value->value)
            return false;
    }
    return true;
}