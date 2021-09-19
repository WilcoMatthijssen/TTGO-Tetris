#pragma once

#include <Arduino.h>
#include <array>
#include <random>
#include <algorithm>


class Tetris{
    constexpr static int8_t width = 10;
    constexpr static int8_t height = 20;
public:
    void begin();

    void move_left();
    void move_right();
    void move_down();
    void rotate_right();
    void rotate_left();


    void check_rows();
    void place_tetromino();
    const bool does_tetromino_fit() const;
    void spawn_tetromino();
    void increase_score(const int8_t & fullRows);
 
    

//========================================================================//
//                              VARIABLES                                 //
//========================================================================//
//private:
    // std::array<std::array<byte, width>, height> playfield;
     std::array<std::array<byte, width>, height> playfield;
    
    bool gameover;
    ulong score;
    int8_t currentTetromino;
    uint8_t rotation;
    Position tetromino_origin;
   
    

    // Z  S  L  J T O I
    // 64 32 16 8 4 2 1
    static constexpr byte TetrominoShapes[8]{
        0b00000000u, 0b01001110u, 0b01101110u, 0b00111100u,
        0b00000001u, 0b00110011u, 0b01110111u, 0b01011001u 
    };
    
   

  
};

