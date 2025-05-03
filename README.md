![Logo](https://imgur.com/tkmgdqd.png)
# Group Member
[Cheung Tak Po](https://github.com/Bosco1739)&ensp;(3036221662)

# Application Description
Sudoku is a captivating logic-based number puzzle that challenges the mind. Players fill a 9x9 grid so each row, column, and 3x3 subgrid contains digits 1-9 without repetition. It enhances concentration, problem-solving, and memory while offering endless variations. Sudoku is perfect for relaxation, mental exercise, and sharpening analytical skills.
## App Control
- Press *Enter/Space* to start.
- Press *1-9* to type in the box.
- Press *U* to undo.
- Press *W/A/S/D* to move.
- Press *Esc* to exit.
## Features
- **Generation of random game sets**
  
    - We can generate infinite sudoku sets according to the algorithm.
      
- **Data structures for storing game activity**
  
    - game_info.txt will be generated to play the same sudoku puzzle again
      
- **Dynamic memory management**
  
    - We detect the keyboard inputs by using the dynamic memory.

- **File input/output**
  
    - We can load and save the data in the application.

- **Program codes in multiple files**
    - Separated into different files in .hpp and .cpp to have a clearer look at the programming structure.

- **Multiple difficulty levels**
    - There are three levels to choose from, easy, medium and hard. Each has a different number of blocks deleted.

# Non-standard libraries
Not used, standard libraries only.

# Compilation/Execution instructions
Download the folder and enter the directory of the file and set up the application by using terminal:
```
cd comp2113_gpprj
make
```
Play *Sudoku* by typing:
```
./sudoku
```
