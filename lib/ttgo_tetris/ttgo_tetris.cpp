#include "ttgo_tetris.h"


void TTGO_tetris::draw_board(){
    display->setRotation(2);
    for(int i = 0; i < 20; ++i){
        for(int j = 0; j < 10; ++j){
            if(playfield[i][j] != 0){
                display->fillRect(j * 8, i * 8, 8, 8, TFT_BLUE);
            }else{
                display->fillRect(j * 8, i * 8, 8, 8, TFT_BLACK);
            }
            display->drawRect(j*8,i*8, 8, 8, TFT_GREEN);
        }
    }
    display->setRotation(0);
}


void TTGO_tetris::draw_score(){
    display->setTextColor(TFT_WHITE,TFT_BLACK);  display->setTextSize(1);
    display->setCursor(0, 0, 2);
    display->println("score:");
    display->println(score);

}


void TTGO_tetris::draw_orientation(){
    
}


void TTGO_tetris::draw(){
    draw_board();
    draw_score();
    // draw_tetromino();
}


void TTGO_tetris::check_buttons(){
    if(!digitalRead(button_left)  ){ 
            Serial.println("lefdt");
        move_left();}
    if(!digitalRead(button_middle)){ 
        Serial.println("down");
        move_down();}
    if(!digitalRead(button_right) ){ 
            Serial.println("right");
        move_right();}
}



void TTGO_tetris::check_gyroscope(){

}




void TTGO_tetris::setup_display(TFT_eSPI* target){
    display = target;
}


void TTGO_tetris::setup_buttons(const uint8_t& b_left, const uint8_t& b_middle, const uint8_t& b_right){
    button_left   = b_left;
    button_middle = b_middle;
    button_right  = b_right;

    pinMode(button_left,   INPUT);
    pinMode(button_middle, INPUT);
    pinMode(button_right,  INPUT);
}


void TTGO_tetris::run(){
    uint_fast8_t counter = 0;
    while(true){
        begin();

        while(!gameover){
            check_buttons();
            draw();
            delay(200);

            if(counter == 5){ counter = 0; move_down();}
            ++counter;
    }   }   
}