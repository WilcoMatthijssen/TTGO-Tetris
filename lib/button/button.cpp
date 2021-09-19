#include "button.h"

Button::Button(const int& button_pin, const unsigned long& debounce_delay):button_pin(button_pin), debounce_delay(debounce_delay){
    pinMode(button_pin, INPUT);
}

bool Button::is_pressed(){
        int reading = digitalRead(button_pin);

        bool ret = false;
        
        switch(state){
            case pressed:
                if((millis() - last_pressed) > debounce_delay&&
                    reading != been_pressed){

                }
                break;
            case waiting:
                if(reading){
                    ret = true;
                    last_pressed = millis();
                }
                break;

        }

        return ret;

            //     if (reading != last_state) {
    //         debounce_delay = millis();
    //     }

    //     if ((millis() - last_pressed) > debounce_delay) {
    //         if (reading != last_state) {
    //             last_state = reading;

    //         if (last_state == HIGH) {
    //         return true;
    //         }   }
    //     }
    //     return false;
    // }
    }