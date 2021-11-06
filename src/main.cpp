#include "Arduino.h"

#include "ttgo_tetris.h"

// #include <User_Setup.h>


#include <TFT_eSPI.h>
// #define TAB_COLOUR ST7735_GREENTAB
// #define ST7735_GREENTAB
// #define ST7735_DRIVER 
// #define TFT_WIDTH  128
// #define TFT_HEIGHT 160

// #define TFT_MISO    -1
// #define TFT_MOSI    23
// #define TFT_SCLK    5
// #define TFT_CS      16  // Chip select control pin
// #define TFT_DC      17  // Data Command control pin
// #define TFT_RST     -1  // Reset pin (could connect to RST pin)
// #define TFT_BL      27

// auto Tet= Tetris<16,12>();

constexpr uint8_t BUTTON_LEFT   = 36;
constexpr uint8_t BUTTON_MIDDLE = 37;
constexpr uint8_t BUTTON_RIGHT  = 39;


auto tft= TFT_eSPI();
auto tetris = TTGO_tetris();

void setup(){
    Serial.begin(9600);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    tft.begin();
    // tft.fillScreen(TFT_BLACK);

    tetris.setup_buttons(BUTTON_LEFT, BUTTON_MIDDLE, BUTTON_RIGHT);
    tetris.setup_display(&tft);
    tetris.run();
}

void loop(){};




