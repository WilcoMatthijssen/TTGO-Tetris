#include <Arduino.h>
#include <array>
#include <random>
#include <algorithm>

#include <tetris.h>


void Tetris::begin(){
    // clear playfield
    for(auto & row : playfield){
        for(auto & spot : row){
            spot = 0;
        }
    }
    
    gameOver=false;
    score=0;
    spawn_new_tetromino();
}


const bool Tetris::move_left(){
    --tetromino_x; 

    const bool is_possible = does_tetromino_fit();
    if(!is_possible){ ++tetromino_x; }

    return is_possible;
}


const bool Tetris::move_right(){
    ++tetromino_x; 

    const bool is_possible = does_tetromino_fit();
    if(!is_possible){  --tetromino_x;  }

    return is_possible;
}


const bool Tetris::move_down(){
    --tetromino_y;
    if(does_tetromino_fit()){ 
        ++tetromino_y; 
        return false;
    }
    
    place_tetromino_on(playfield);
    check_rows();
    spawn_new_tetromino();
    
    return true;
}



const bool Tetris::rotate(){ 
    rotation = (rotation + 1) % 4;

    const bool is_possible = does_tetromino_fit();
    if(!is_possible){ rotation = (rotation - 1) % 4; }

    return is_possible;
}




const std::array<std::array<byte, 10>, 20> Tetris::get_playfield() const{
    auto tempPlayfield = playfield;
    place_tetromino_on(tempPlayfield);

    return tempPlayfield;
}


void Tetris::remove_row(const int8_t & index){
    for(int8_t i = index; i< HEIGHT-1; ++i){
        playfield[i]= playfield[i+1];
    }
    
    // //Clear top row
    auto& top_row = playfield[HEIGHT-1];
    std::fill(top_row.begin(), top_row.end(), 0);
 
}


const bool Tetris::is_row_full(const int8_t & index) const{
    const auto& row = playfield[index];
    auto is_spot_filled = [](const int8_t& spot){ return spot != 0; };
    auto is_row_full = [](const std::array<WIDTH, uint8_t> & row){ return std::all_of(row.begin(), row.end(), is_spot_filled(row)); };
    return is_row_full(row);
}


void Tetris::check_rows(){

    increase_score(full_rows)
    remove_row(full_rows)

    int8_t full_rows = 0;
    for(int8_t i = HEIGHT - 1; i >= 0; --i){
        if( is_row_full(i) ){ 
            remove_row(i); 
            ++full_rows; 
        }
    }
}

void Tetris::place_tetromino_on(std::array<std::array<byte, WIDTH>, HEIGHT>& given_playfield) const{
    for(int8_t i = tetromino_x; i <  tetromino_x + 4; ++i){
        for(int8_t j =  tetromino_y; j <  tetromino_y + 4; ++j){
            given_playfield[i][j] = TetrominoShapes[currentTetromino][i + ((tetromino_y - j) * 4)];
        }
    }
    
    // int8_t incr;
    // int8_t rowIncr;
    // int8_t n;

    // switch(rotation){
    //     case 0:  rowIncr =  0 ;    incr =  1;    n = 0 ;   break;  // 0 degrees
    //     case 1:  rowIncr =  17;    incr = -4;    n = 12;   break;  // 90 degrees
    //     case 2:  rowIncr =  0 ;    incr = -1;    n = 15;   break;  // 180 degrees
    //     default: rowIncr = -17;    incr =  4;    n = 3 ;   break;  // 270 degrees
    // }
    
    // for(int8_t i =tetromino_y; i<tetromino_y + 4 ; ++i, n+=rowIncr){
    //     for(int8_t j =tetromino_x; j< tetromino_x +4; ++j, n+=incr){
    //         if(TetrominoShapes[currentTetromino][n] != 0){
    //             given_playfield[i][j]=TetrominoShapes[currentTetromino][n];
    //         }
    //     }
    // }
}



const bool Tetris::is_space_free(const int8_t& y, const int8_t& x) const{
    // Check if space is out of bounds and if it isn't occupied.
    return x >= 0 && x < WIDTH && y >= 0 && playfield[y][x] == 0;
}


const bool Tetris::does_tetromino_fit() const{
    auto is_space_free = [&](const int8_t& y, const int8_t& x){ return x >= 0 && x < WIDTH && y >= 0 && playfield[y][x] == 0; };


    for(int8_t i = tetromino_x; i < tetromino_x + 4; ++i){
        for(int8_t j = tetromino_y; j < tetromino_y + 4; ++j){
            if(TetrominoShapes[currentTetromino][i + ((tetromino_y-j) * 4)] != 0){
                if( !is_space_free(i, j) ){
                    return false;
                }
                
            }
        }
    }
    return true;
  


    }


void Tetris::spawn_new_tetromino(){
    rotation = 0;
    tetromino_y = HEIGHT - 5;
    tetromino_x = (WIDTH / 2) - 2;
    currentTetromino = random(28);

    gameOver = !does_tetromino_fit();
}


void Tetris::increase_score(const int8_t & fullRows){
    // https://tetris.wiki/Scoring
    // Original BPS scoring system
    switch(fullRows){
        case 1: score += 40u;   break;
        case 2: score += 100u;  break;
        case 3: score += 300u;  break;
        case 4: score += 1200u; break;
        default:                break;
    }
}
    

// template<int8_t HEIGHT, int8_t WIDTH> constexpr byte Tetris<HEIGHT, WIDTH>::TetrominoShapes[7][16];
// template<int8_t WIDTH, int8_t HEIGHT> constexpr byte Tetris<WIDTH, HEIGHT>::TetrominoShapes[8];