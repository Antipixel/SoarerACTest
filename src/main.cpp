#include <Arduino.h>
#include <aircon/aircon.h>

#define PIN_CLOCK GPIO_NUM_12
#define PIN_DATA GPIO_NUM_14
#define PIN_CLEAR GPIO_NUM_27

Aircon aircon(PIN_CLOCK, PIN_DATA, PIN_CLEAR);

void onAirconLCDClock()
{   
    aircon.onLCDClock();
}

void onAirconLCDClear()
{
    aircon.onLCDClear();
}

void setup() 
{
    Serial.begin(115200);
    attachInterrupt(PIN_CLOCK, onAirconLCDClock, RISING);
    attachInterrupt(PIN_CLEAR, onAirconLCDClear, RISING);
}

void loop() 
{

}