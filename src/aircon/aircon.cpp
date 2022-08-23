#include <aircon/aircon.h>

Aircon::Aircon(uint8_t pinClock, uint8_t pinData, uint8_t pinReset)
{
    this->pinClock = pinClock;
    this->pinData = pinData;
    this->pinReset = pinReset;

    this->clockCount = 0;
    this->lcdData = 0;
    this->prevData = 0;

    this->fan = Fan(&this->lcdData);
    this->mode = Mode(&this->lcdData);

    this->tens = Digit(&this->lcdData);
    this->ones = Digit(&this->lcdData);
    this->tenths = Digit(&this->lcdData);

    this->tens.setSegmentIndices(9, 26, 22, 21, 20, 10, 12);
    this->ones.setSegmentIndices(25, 30, 29, 28, 27, 23, 24);
    this->tenths.setSegmentIndices(41, 39, 38, 37, 36, 34, 35);

    this->setupPins();
}

void Aircon::setupPins()
{
    pinMode(this->pinClock, INPUT);
    pinMode(this->pinData, INPUT);
    pinMode(this->pinReset, INPUT);
}

void Aircon::onLCDUpdate()
{
    bool fanIcon = this->getSegmentState(6);
    bool temp = this->getSegmentState(8);
    bool max = this->getSegmentState(7);
    bool autom = this->getSegmentState(43);
    uint8_t fanSpeed = this->fan.getFanSpeed();
    ACMode mode = this->mode.getMode();

    double temperature = this->getTemperature();

    Serial.printf("Mode: %d, Fan Icon: %d, Fan Speed: %d, Temperature: %.1f, TEMP: %d, MAX: %d, AUTO: %d\n", 
                    mode, fanIcon, fanSpeed, temperature, temp, max, autom);
}

void Aircon::onLCDClock()
{
    uint8_t data = digitalRead(this->pinData);

    this->lcdData |= ((uint64_t)data << this->clockCount);
    this->clockCount++;
}

void Aircon::onLCDClear()
{
    if (clockCount == DATA_SIZE && this->lcdData != this->prevData)
    {
        this->onLCDUpdate();
        this->prevData = this->lcdData;
    }
    this->lcdData = 0;
    this->clockCount = 0;
}

/**
 * Gets the temperature, in celsius, currently being displayed on the 
 * climate control LCD. This value can range between TEMP_MAX_COLD (17.5) 
 * and TEMP_MAX_HOT (32.5), in increments of 0.5 degrees
 * @return the currently displayed temperature 
 */
float Aircon::getTemperature()
{
    /* When the temperature dial is set to either the very maximum
     * or the very minimum possible position, the LCD will display 
     * "MAX COLD" or "MAX HOT" in lieu of displaying the temperature
     * value. For simplicity, we'll convert these values to 17.5°C
     * and 32.5°C respectively */
    if (this->getSegmentState(SEGMENT_HOT))
        return TEMP_MAX_HOT;

    if (this->getSegmentState(SEGMENT_COLD))
        return TEMP_MAX_COLD;

    /* Check that all three required digits are valid */
    if (this->tens.isValid() && this->ones.isValid() && this->tenths.isValid())
    {
        double temperature = this->ones.getValue();

        temperature += this->tens.getValue() * TENS_MULTIPLIER;
        temperature += this->tenths.getValue() * TENTHS_MULTIPLIER;

        return temperature;
    }

    return INVALID_TEMP;
}

uint8_t Aircon::getSegmentState(uint8_t segment)
{
    return (this->lcdData >> segment) & 0x1;
}