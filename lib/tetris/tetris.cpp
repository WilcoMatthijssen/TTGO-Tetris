#include <Arduino.h>
#include <array>
#include <random>
#include <algorithm>

#include "tetris.h"

/* --------------------------------------------------
                    PUBLIC
---------------------------------------------------*/

void Tetris::begin(){
    for(auto& row: playfield){  row.fill(0);  }
    score=0;
    spawn_tetromino_if_fits();
}

void Tetris::rotate_left(){    move_tetromino_if_fits(Point2D{ 0, 0},  1); }
void Tetris::rotate_right(){   move_tetromino_if_fits(Point2D{ 0, 0}, -1); }


void Tetris::move_left(){      move_tetromino_if_fits(Point2D{ 1, 0}, 0); }
void Tetris::move_right(){     move_tetromino_if_fits(Point2D{-1, 0}, 0); }

void Tetris::move_down(){
    if(!move_tetromino_if_fits( Point2D{0, -1}, 0)){
        check_rows();
        spawn_tetromino_if_fits();
    }
}

/* --------------------------------------------------
                    PRIVATE
---------------------------------------------------*/

void Tetris::set_tetromino(const int8_t& value){
    for(const auto& point: tetromino_positions){ 
        playfield[point.y][point.x] = value; 
    }
}


bool Tetris::move_tetromino_if_fits(const Point2D& delta, const int8_t& rotation){
    // Remove tetromino from playfield to not interfere with does_tetromino_fit and save color to later revert this action with the same color
    const auto color = playfield[tetromino_positions.front().y][tetromino_positions.front().x];
    set_tetromino(0);

    const array<Point2D, 4> positions = get_new_tetromino_positions(delta, rotation);
    const bool can_position_change = does_tetromino_fit(positions);

    if(can_position_change){
        tetromino_origin    += delta;
        tetromino_positions  = positions;
    }
    set_tetromino(color);
    return can_position_change;
}


array<Point2D, 4> Tetris::get_new_tetromino_positions(const Point2D& delta, const int8_t& rotation) const{
    array<Point2D, 4> new_positions = tetromino_positions;
    const Point2D origin = tetromino_origin + delta;
    for(auto& point: new_positions){ 
        point = get_rotated_position(origin, point + delta, rotation);
    }
    return new_positions;
}


bool Tetris::does_tetromino_fit(const array<Point2D, 4>& positions) const{
    const auto is_space_free = [&](const Point2D& pos ){
                                            return  pos.x >= 0    && 
                                                    pos.x < width && 
                                                    pos.y >= 0    && 
                                                    playfield[pos.y][pos.x] == 0; };
                                                    
    return std::all_of(positions.begin(), positions.end(), is_space_free);
}


void Tetris::check_rows(){
    uint8_t full_rows = 0;

    for(auto row_it = playfield.begin(); row_it != playfield.end(); ++row_it){
        if(std::count(row_it->begin(), row_it->end(), 0) == 0){
            row_it->fill(0);
            std::rotate(playfield.begin(), playfield.begin() + 1, row_it + 1 );
            ++full_rows;
        }
    }
    
    increase_score(full_rows);
}


void Tetris::spawn_tetromino_if_fits(){
    constexpr const Point2D origin{(width / 2) - 2, height - 5};
    const auto& tetromino_template = tetromino_shapes[random(7)];

    int8_t found = 0;
    array<Point2D, 4> positions;

    for(Point2D p{0,0}; p.y < tetromino_template.size();         ++p.y){
        for(p.x = 0 ; p.x < tetromino_template.front().size(); ++p.x){
            if(tetromino_template[p.y+1][p.x] != 0){
                positions[found] = origin + p;
                ++found;
    }   }   }

    gameover = !does_tetromino_fit(positions);
    if(!gameover){
        tetromino_origin = origin;
        tetromino_positions = positions;
        set_tetromino(1);
    }
}


void Tetris::increase_score(const int8_t & full_rows){
    // https://tetris.wiki/Scoring
    // Original BPS scoring system
    switch(full_rows){
        case 1: score += 40u;   break;
        case 2: score += 100u;  break;
        case 3: score += 300u;  break;
        case 4: score += 1200u; break;
        default:                break;
    }
}


Point2D Tetris::get_rotated_position(const Point2D& origin, const Point2D& position, const int8_t& rotation) const{
    uint8_t pi;
    Point2D p = position - origin;

    switch(rotation % 4){
        case 0: pi = p.y * 4 + p.x;        break;
        case 1: pi = 12 + p.y - (p.x * 4); break;
        case 2: pi = 15 - (p.y * 4) - p.x; break;
        default:pi = 3 - p.y + (p.x * 4);  //case 3:
    }

    p.x = pi % 4;
    p.y = pi / 4;

    return p + origin;
}




