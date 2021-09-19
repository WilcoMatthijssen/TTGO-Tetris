#pragma once
#include <Arduino.h>

class Button{
private:
    unsigned long last_pressed;
    unsigned long debounce_delay;

    bool been_pressed;
    int button_pin;

    enum State{pressed, cooldown, waiting};
    State state;
    
public:
    Button(const int& pin, const unsigned long& debounce_delay=50);
    bool is_pressed();
};