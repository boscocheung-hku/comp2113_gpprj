#pragma once

#include <iostream>
#include <thread>
#include <termios.h>
#include <vector>
#include <stdio.h>
#include "config.h"
#include <fcntl.h>

using namespace std;


class Keyboard {
public:
    Keyboard();
    void scan();
    void loop();
    void listen();
    int read();
    int wait_for(vector<int> key);
    int select_difficulty();
    struct termios new_settings;
    struct termios stored_settings;
public:
    thread t;
    int in;
    int difficulty;
    int grids_inerase;
    bool is_listening = false;
    bool correct_input = false;
};

