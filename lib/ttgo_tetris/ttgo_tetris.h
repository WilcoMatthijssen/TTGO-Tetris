#pragma once

// #include <TFT_eSPI.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include "tetris.h"


class TTGO_tetris: protected Tetris{
private:
    uint8_t button_left, button_middle, button_right;
    Adafruit_ST7735* display;

    // void draw_tetromino(){
    //     // const auto positions = get_tetromino_positions();
    //     // for(const auto& position: positions){
    //     //     display->fillRect(position.x * 8, position.y * 8, 8, 8, TFT_RED);
    //     //     display->drawRect(position.x * 8, position.y * 8, 8, 8, TFT_GREEN);
    //     // }
    // }

    void draw_board();
    void draw_score();
    void draw_orientation();
    void draw();

    void check_buttons();
    void check_gyroscope();

public:
    void setup_display(Adafruit_ST7735* target);
    void setup_buttons(const uint8_t& b_left, const uint8_t& b_middle, const uint8_t& b_right);
    void run();
};