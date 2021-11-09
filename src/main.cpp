#include "Arduino.h"

#include "ttgo_tetris.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h>
#include <SPI.h>


// #define TAB_COLOUR ST7735_GREENTAB
// #define ST7735_GREENTAB
// #define ST7735_DRIVER 
// #define TFT_WIDTH  128
// #define TFT_HEIGHT 160

#define TFT_MISO    -1
#define TFT_MOSI    23
#define TFT_SCLK    5
#define TFT_CS      16  // Chip select control pin
#define TFT_DC      17  // Data Command control pin
#define TFT_RST     -1  // Reset pin (could connect to RST pin)
#define TFT_BL      27

// auto Tet= Tetris<16,12>();

constexpr uint8_t BUTTON_LEFT   = 36;
constexpr uint8_t BUTTON_MIDDLE = 37;
constexpr uint8_t BUTTON_RIGHT  = 39;


// auto tft= TFT_eSPI();
auto tetris = TTGO_tetris();

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup(){
    Serial.begin(9600);

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    tft.initR(INITR_GREENTAB);
    tft.fillScreen(ST7735_BLACK);  // Fill screen with black


    tetris.setup_buttons(BUTTON_LEFT, BUTTON_MIDDLE, BUTTON_RIGHT);
    tetris.setup_display(&tft);
    tetris.run();
}

void loop(){};




