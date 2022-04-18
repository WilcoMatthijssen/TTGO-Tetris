#include <Arduino.h>
#include <array>
#include <random>
#include <algorithm>

#include "tetris.h"

/* --------------------------------------------------
                    PUBLIC
---------------------------------------------------*/

// Initializes everything to the begin state of tetris
// Use before starting a tetris game
void Tetris::begin(){
    for(auto& row: playfield){  row.fill(0);  }
    score=0;
    spawn_tetromino_if_fits();
}

// Rotates current tetromino clockwise if possible
// Used for game interaction
void Tetris::rotate_counter_clockwise(){    move_tetromino_if_fits(Point2D{ 0, 0},  1); }

// Rotates current tetromino counter-clockwise if possible
// Used for game interaction
void Tetris::rotate_clockwise(){            move_tetromino_if_fits(Point2D{ 0, 0}, -1); }

 // Moves current tetromino to the left if possible
 // Used for game interaction
void Tetris::move_left(){      move_tetromino_if_fits(Point2D{ 1, 0}, 0); }

// Moves current tetromino to the right if possible
// Used for game interaction
void Tetris::move_right(){     move_tetromino_if_fits(Point2D{-1, 0}, 0); }

// Moves current tetromino to the down and when not possible it leaves the tetromino where it is, checks for full rows and handles them and spawns a new tetromino.
// Used for game interaction
void Tetris::move_down(){
    if(!move_tetromino_if_fits( Point2D{0, -1}, 0)){
        handle_full_rows();
        spawn_tetromino_if_fits();
    }
}

/* --------------------------------------------------
                    PRIVATE
---------------------------------------------------*/

// Sets value on playfield for the positions of a tetromino
// Mainly used for removing a tetromino from the playfield to not interfere with collision checks
void Tetris::set_tetromino(const int8_t& value){
    for(const auto& point: tetromino_positions){ 
        playfield[point.y][point.x] = value; 
    }
}

// Moves tetromino on tetromino_positions tetromino_origin and playfield by the given delta and rotation if there arent any colliding pieces or walls.
// Used as abstraction for the move_(left, right & down) and rotate_(clockwise & counter_clockwise).
bool Tetris::move_tetromino_if_fits(const Point2D& delta, const int8_t& rotation){
    // Remove tetromino from playfield to not interfere with does_tetromino_fit and save color to later revert this action with the same color
    const auto color = playfield[tetromino_positions.front().y][tetromino_positions.front().x];
    set_tetromino(0);

    const array<Point2D, 4> positions = get_updated_tetromino_positions(delta, rotation);
    const bool can_position_change = does_tetromino_fit(positions);

    // Update elements when the positon can change 
    if(can_position_change){
        tetromino_origin    += delta;
        tetromino_positions  = positions;
    }

    //apply the tetromino on the board on its old or new position
    set_tetromino(color);
    return can_position_change;
}


// Get updated tetromino positions by applying rotation and delta with disregard to if the move is possible
// Used in move_tetromino_if_fits as step before checking collision and set for actual tetromino when it fits
array<Point2D, 4> Tetris::get_updated_tetromino_positions(const Point2D& delta, const int8_t& rotation) const{
    array<Point2D, 4> new_positions = tetromino_positions;
    const Point2D origin = tetromino_origin + delta;
    for(auto& point: new_positions){ 
        point = get_rotated_position(origin, point + delta, rotation);
    }
    return new_positions;
}


// Checks if tetromino positions are occupied on board or are outside the board when changing position.
// This function doesn't take account for the current tetromino so remove it to prevent collisions with itself
bool Tetris::does_tetromino_fit(const array<Point2D, 4>& positions) const{
    const auto is_space_free = [&](const Point2D& pos ){
                                            return  pos.x >= 0    && 
                                                    pos.x < width && 
                                                    pos.y >= 0    && 
                                                    playfield[pos.y][pos.x] == 0; };
                                                    
    return std::all_of(positions.begin(), positions.end(), is_space_free);
}

// Handles full rows by finding, removing and adding them to the score
// Use after a tetromino is placed on the playfield
void Tetris::handle_full_rows(){
    uint8_t full_rows = 0;

    // Id rather use a normal for range loop but the std::rotate function need the iterator
    for(auto row_it = playfield.begin(); row_it != playfield.end(); ++row_it){
        if(std::count(row_it->begin(), row_it->end(), 0) == 0){
            row_it->fill(0);
            std::rotate(playfield.begin(), playfield.begin() + 1, row_it + 1 );
            ++full_rows;
        }
    }
    
    increase_score(full_rows);
}

// Spawns a new tetromino if spawn position isn't obstructed or ends the game when it does
// Used after a tetromino has been placed
void Tetris::spawn_tetromino_if_fits(){
    Point2D origin{(width / 2) - 2, height - 5};
    const auto& tetromino_template = tetromino_shapes[random(7)];

    int8_t found = 0;
    array<Point2D, 4> positions;

    for(Point2D p{0,0}; p.y < tetromino_template.size();       ++p.y){
        for(p.x = 0 ; p.x < tetromino_template.front().size(); ++p.x){
            if(tetromino_template[p.y][p.x] != 0){
                positions[found] = origin + p;
                ++found;
    }   }   }
    --origin.y; // adjust for having 2 rows instead of 4 for tetrominos in tetromino_template -> 

    gameover = !does_tetromino_fit(positions);
    if(!gameover){
        tetromino_origin = origin;
        tetromino_positions = positions;
        set_tetromino(1);
    }
}


// Increases score based on full rows using the original BPS scoring system referenced from https://tetris.wiki/Scoring
// Used in handle_full_rows function
void Tetris::increase_score(const int8_t & full_rows){
    switch(full_rows){
        case 1: score += 40u;   break;
        case 2: score += 100u;  break;
        case 3: score += 300u;  break;
        case 4: score += 1200u; break;
        default:                break;
    }
}


// Rotates postion in 90 degree increments
// Used when updating tetromino
Point2D Tetris::get_rotated_position(const Point2D& origin, const Point2D& position, const int8_t& rotation) const{
    uint8_t pi;
    Point2D p = position - origin;

    switch(rotation % 4){
        case 0: pi = p.y * 4 + p.x;        break;
        case 1: pi = 12 + p.y - (p.x * 4); break;
        case 2: pi = 15 - (p.y * 4) - p.x; break;
        default:pi = 3  - p.y + (p.x * 4);  //case 3:
    }

    p.x = pi % 4;
    p.y = pi / 4;

    return p + origin;
}
