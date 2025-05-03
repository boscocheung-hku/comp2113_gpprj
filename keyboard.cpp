#include "keyboard.h"



Keyboard::Keyboard() {
    in = 0;
    this->is_listening = false;
}

void Keyboard::scan() {
    int temp_in;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    // new_settings.c_lflag |= ISIG;
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new_settings);
    temp_in = getchar();

    this->in = temp_in;
}

void Keyboard::loop() {
    while (this->is_listening) {
        scan();
    }
}

void Keyboard::listen() {
    this->is_listening = true;
    t = thread(&Keyboard::loop, this);
    t.detach();
}

int Keyboard::read() {
    if (in != 0) {
        int return_in = in;
        in = 0;
        return return_in;
    } else {
        return 0;
    }
}

int Keyboard::wait_for(vector<int> key) {
    while (true) {
        int k = read();
        if (k != 0) {
            for (int i = 0; i < key.size(); i++) {
                if (k == key[i]) {
                    return k;
                }
            }
        }
    }
}

int Keyboard::select_difficulty() {
    difficulty = wait_for({KEY_ONE, KEY_TWO, KEY_THREE});
    if (difficulty == '1') {
        grids_inerase = 20;
    } else if (difficulty == '2') {
        grids_inerase = 35;
    } else if (difficulty == '3') {
        grids_inerase = 50;
    }
    return grids_inerase;
}
