#ifndef AIRCON_H_
#define AIRCON_H_

#include <Arduino.h>
#include <aircon/fan.h>
#include <aircon/mode.h>
#include <aircon/digit.h>

#define DATA_SIZE 44
#define SEGMENT_HOT 33
#define SEGMENT_COLD 42
#define TEMP_MAX_HOT 32.5
#define TEMP_MAX_COLD 17.5
#define INVALID_TEMP -1

#define TENS_MULTIPLIER 10.0
#define TENTHS_MULTIPLIER 0.1

class Aircon
{
private:
    // Pin assignments
    uint8_t pinClock;
    uint8_t pinData;
    uint8_t pinReset;

    uint8_t clockCount;
    uint64_t lcdData;
    uint64_t prevData;

    Fan fan;
    Mode mode;

    Digit tens;
    Digit ones;
    Digit tenths;
public:
    Aircon(uint8_t pinClock, uint8_t pinData, uint8_t pinReset);
    void onLCDClock();
    void onLCDClear();
private:
    uint8_t getSegmentState(uint8_t segment);
    void setupPins();
    void onLCDUpdate();
    float getTemperature();
};

#endif