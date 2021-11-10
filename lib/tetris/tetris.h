#pragma once

#include <Arduino.h>
#include <array>
#include <random>
#include <algorithm>
#include "point2d.h"

using std::array;


class Tetris{
    constexpr static int8_t width = 10;
    constexpr static int8_t height = 20;

    Point2D tetromino_origin;
    array<Point2D, 4> tetromino_positions; 

public:
    void    begin(),                        
            move_left(),                   
            move_right(),                   
            move_down(),                    
            rotate_counter_clockwise(),    
            rotate_clockwise();             

private:

    void    handle_full_rows(),
            spawn_tetromino_if_fits(),      
            set_tetromino(const int8_t& value),
            increase_score(const int8_t& full_rows);
            

    array<Point2D, 4> get_updated_tetromino_positions (const Point2D& delta, const int8_t& rotation) const;
    bool  move_tetromino_if_fits (const Point2D& delta, const int8_t& rotation);
    bool  does_tetromino_fit     (const array<Point2D, 4>& points) const;
    Point2D get_rotated_position   (const Point2D& origin, const Point2D& old_position, const int8_t& rotation) const;

protected:
    array<array<int8_t, width>, height> playfield;
    bool gameover;
    size_t score;

    // Z  S  L  J T O I
    // 64 32 16 8 4 2 1
    // static constexpr byte TetrominoShapes[8]{
    //     0b00000000u, 0b01001110u, 0b01101110u, 0b00111100u,
    //     0b00000001u, 0b00110011u, 0b01110111u, 0b01011001u 
    // };

    const array<array<array<bool, 4>,2>,7> tetromino_shapes {{

        {{ // I-tetromino
        {{0,0,0,0}},
        {{1,1,1,1}}
        }},

        {{ // O-tetromino
        {{0,1,1,0}},
        {{0,1,1,0}}
        }},

        {{ // T-tetromino
        {{0,1,1,1}},
        {{0,0,1,0}}
        }},

        {{ // L-tetromino
        {{0,1,1,1}},
        {{0,1,0,0}}
        }},

        {{ // J-tetromino
        {{0,1,1,1}},
        {{0,0,0,1}}
        }},

        {{ // S-tetromino
        {{0,0,1,1}},
        {{0,1,1,0}}
        }},

        {{  // Z-tetromino
        {{0,1,1,0}},
        {{0,0,1,1}}
        }}
    }};

};

