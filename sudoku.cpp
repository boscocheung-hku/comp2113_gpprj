#include "sudoku.h"

Sudoku::Sudoku(int index) : max_col(static_cast<int>(pow(index, 2))), cur_pt({0, 0}){
    init();
}
void Sudoku::ptrinit() {
    this->kb = Keyboard();
    this->kb.listen();
    this->cfg = Config();
}

void Sudoku::init() {
    memset(sudoku_map, NUL, sizeof(sudoku_map));

    for (int col = 0; col < max_col; ++col) {

        Grid _col_grid;

        for (int row = 0; row < max_col; ++row) {
            _col_grid.push_back(sudoku_map + row * max_col + col);
        }
        col_grid[col] = _col_grid;
    }

    for (int row = 0; row < max_col; ++row) {
        Grid _row_grid;

        for (int col = 0; col < max_col; ++col) {
            _row_grid.push_back(sudoku_map + row  * max_col + col);
        }

        row_grid[row] = _row_grid;
    }

    for (int row = 0; row < max_col; ++row) {
        for (int col = 0; col < max_col; ++col) {
            single_grid[row / 3][col / 3].push_back(sudoku_map + row * max_col + col);
        }
    }

    return;
}

void Sudoku::printGrid() {
    this->cfg.clear();
    printMargin();

    for (int row = 0; row < max_col; row++) {
        Grid grid = row_grid[row];
        if (cur_pt.y == row) {
            grid.print(cur_pt.x);
        } else {
            grid.print();
        }
        printMargin(row);
    }
}

void Sudoku::printMargin(int num) const{
    auto is_curline = (cur_pt.y == num);
    for (int col = 0; col < 9; ++col) {
        cout << corner;
        auto third_symbol = (is_curline && cur_pt.x == col) ? arrow : line;
        cout << line << third_symbol << line;
    }
    cout << corner << endl;
}

void Sudoku::eraseGrids(const int value) {
    pt_val_r emp = {NUL, Status::ERASED};
    vector<int> pos_map(81);
    for (int i = 0; i < 81; ++i) {
        pos_map[i] = i;
    }

    for (int i = 0; i < value; ++i) {
        int r = random(0, static_cast<int>(pos_map.size() - 1));
        sudoku_map[pos_map[r]] = emp;
        pos_map.erase(pos_map.begin() + r);
    }
}

void Sudoku::fillVal(const pt_r& p, const int value) {
    sudoku_map[p.x + p.y * 9].value = value;
}

void Sudoku::fillVals(const int value)
{
    auto p = cur_pt;
    this->fillVal(p, value);
}

void Sudoku::generate() {
    vector<vector<int>> matrix;
    for (int i = 0; i < 9; i++) {
        matrix.push_back(vector<int>(9,0));
    }
    for (int num = 0; num < 3; num++) {
        vector<int> unit = shuffle_num();
        int beg_index = 3 * num;
        for (int i = beg_index; i < beg_index + 3; i++) {
            for (int j = beg_index; j < beg_index + 3; j++) {
                matrix[i][j] = unit.back();
                unit.pop_back();
            }
        }
    }

    vector<tuple<int, int>> box_list;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (matrix[i][j] == 0) {
                box_list.push_back(make_tuple(i, j));
            }
        }
    }

    unordered_map<string, vector<int>> nums_available {};
    int ref_num = 0;
    int emp_num = static_cast<int>(box_list.size());
    while (ref_num < emp_num) {
        tuple<int, int> pos = box_list[ref_num];
        int row = get<0>(pos);
        int col = get<1>(pos);
        vector<int> able_unit;
        string key = to_string(row) + "x" + to_string(col);
        if (nums_available.find(key) == nums_available.end()) {

            able_unit = get_num();
            for (int i = row/3*3; i < row/3*3+3; i++) {
                for (int j = col/3*3; j < col/3*3+3; j++) {
                    able_unit.erase(remove(able_unit.begin(), able_unit.end(), matrix[i][j]), able_unit.end());
                }
            }

            for (int i = 0; i < 9; i++) {
                if(matrix[row][i] != 0) {
                    able_unit.erase(remove(able_unit.begin(), able_unit.end(), matrix[row][i]), able_unit.end());
                }
            }

            for (int i = 0; i < 9; i++) {
                if(matrix[i][col] != 0) {
                    able_unit.erase(remove(able_unit.begin(), able_unit.end(), matrix[i][col]), able_unit.end());
                }
            }
            
            nums_available[key] = able_unit;
        } else {
            able_unit = nums_available[key];
        }

        if (nums_available[key].size() <= 0) {
            ref_num -= 1;
            if (nums_available.find(key) != nums_available.end()) {
                nums_available.erase(key);
            }
            matrix[row][col] = 0;
            continue;
        } else {
            matrix[row][col] = nums_available[key].back();
            nums_available[key].pop_back();
            ref_num += 1;
        }
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            pt_r point = {row, col};
            fillVal(point, matrix[row][col]);
        }
    }
    return;
}

void Sudoku::game() {
    printGrid();
    while (true) {
        vector<int> Key = {KEY_W, KEY_A, KEY_S, KEY_D, KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, KEY_U, KEY_ESC, KEY_ENTER};
        user_action = this->kb.wait_for(Key);
        if (48 <= user_action && user_action <= 57) {
            Fill oCommand(this);
            if(!oCommand.execute(user_action - '0') ) {
                cout << "This box can\'t be modified" << endl;
            } else {
                _vCommand.push_back(std::move(oCommand));
                printGrid();
                continue;
            }
        } else if (user_action == KEY_W) {
            cur_pt.y = (cur_pt.y - 1) < 0 ? 0 : cur_pt.y - 1;
            printGrid();
        } else if (user_action == KEY_S) {
            cur_pt.y = (cur_pt.y + 1) > 8 ? 0 : cur_pt.y + 1;
            printGrid();
        } else if (user_action == KEY_A) {
            cur_pt.x = (cur_pt.x - 1) < 0 ? 0 : cur_pt.x - 1;
            printGrid();
        } else if (user_action == KEY_D) {
            cur_pt.x = (cur_pt.x + 1) > 8 ? 0 : cur_pt.x + 1;
            printGrid();
        } else if (user_action == KEY_U) {
          if (_vCommand.empty()) {
            cout << "Cannot undo" << endl;
            } else {
            Fill &oCommand = _vCommand.back();
            oCommand.undo();
            _vCommand.pop_back();
            printGrid();
            }
        } else if (user_action == KEY_ENTER) {
          if (isComplete()) {
            cout << "Yay, you win the sudoku" << endl;
            getchar();
            exit(0);
            } else {
            cout << "The sudoku has not yet finished / wrong answer." << endl;
            }
        } else if (user_action == KEY_ESC) {
            cout << "Are you going to quit? (y/n)" << endl;
            int answer = this->kb.wait_for(answers);
            if (answer == KEY_Y || answer == KEY_y) {
                cout << "Are you going to save? (y/n)";
                int answer = this->kb.wait_for(answers);
                if (answer == KEY_Y || answer == KEY_y) {
                    save("game_info.txt");
                }
                this->cfg.clear();
                printf("\033[?25h");
                exit(0);
            } else {
                cout << "Game Continue!" << endl;
            } 
        }
    }
}

bool Sudoku::setPointValue(const pt_r &stPoint, const int nValue)
{
    auto point = sudoku_map[stPoint.x + stPoint.y * 9];
    if (Status::ERASED == point.status)
    {
        cur_pt = stPoint;
        fillVals(nValue);
        return true;
    }
    else
        return false;
}

pt_r Sudoku::getCurPoint()
{
    return cur_pt;
}

bool Sudoku::setCurValue(const int nCurValue, int &nLastValue)
{
    auto point = sudoku_map[cur_pt.x + cur_pt.y * 9];
    if (point.status == Status::ERASED)
    {
        nLastValue = point.value;
        fillVals(nCurValue);
        return true;
    }
    else
        return false;
}

bool Sudoku::isComplete()
{
    for (size_t i = 0; i < 81; ++i)
    {
        if (sudoku_map[i].value == NUL)
            return false;
    }

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (!row_grid[row].isValid() || 
                !col_grid[col].isValid() || 
                !single_grid[row / 3][col / 3].isValid())
                return false;
        }
    }

    return true;
}

void Sudoku::save(string filename) {
    ofstream fout(filename);

    for (int i = 0; i < 81; i++) {
        fout << sudoku_map[i].value << ' ' << static_cast<int>(sudoku_map[i].status) << std::endl;
    }

    fout << cur_pt.x << ' ' << cur_pt.y << std::endl;
  
    fout << _vCommand.size() << std::endl;
      for (Fill command : _vCommand) {
          pt_r point = command.getPoint();
          fout << point.x << ' ' << point.y << ' '
             << command.getPreValue() << ' '
             << command.getCurValue() << std::endl;
      }
  
      fout.close();
}

void Sudoku::load(string filename) {
      ifstream fin;
      fin.open("game_info.txt");

      // load _map
      for (int i = 0; i < 81; i++) {
          int tmpState;
          fin >> sudoku_map[i].value >> tmpState;
          sudoku_map[i].status = static_cast<Status>(tmpState);
      }
  
      // load _cur_point
      fin >> cur_pt.x >> cur_pt.y;
  
      // load _vCommand
      int commandSize;
      fin >> commandSize;
      for (int i = 0; i < commandSize; i++) {
          pt_r point;
          int preValue, curValue;
          fin >> point.x >> point.y >> preValue >> curValue;
          _vCommand.emplace_back(this, point, preValue, curValue);
      }
      fin.close();
}

void Sudoku::loop() {
    this->cfg.clear();
    for (int i=0; i < start_screen.size(); i++) {
        cout << start_screen[i] << endl;
    }
    this->kb.wait_for({KEY_ENTER, KEY_SPACE});
    this->cfg.clear();
    ifstream f("game_info.txt");
    if (f.good()) {
            cout << "Load save file (y/n)?" << endl;
            int key = this->kb.wait_for({KEY_Y, KEY_N, KEY_y, KEY_n});
            if (key == KEY_Y || key == KEY_y) {
                load("game_info.txt");
            } else {
                this->cfg.clear();
                difficulty();
                generate();
                eraseGrids(grid_inerase);
            }
    } else {
        difficulty();
        generate();
        eraseGrids(grid_inerase);
    }
    game();
}

void Sudoku::difficulty() {
    cout << "Select difficulty: " << endl << "1 Easy 2 Medium 3 Hard" << endl;
    grid_inerase = this->kb.select_difficulty();
}