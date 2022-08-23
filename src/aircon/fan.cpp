#include <aircon/fan.h>

Fan::Fan() : Fan(NULL) {}

Fan::Fan(uint64_t *lcdData) : SegmentGroup(lcdData)
{
    this->speedBars[SEG_SPEED_1] = SEG_INDEX_1;
    this->speedBars[SEG_SPEED_2] = SEG_INDEX_2;
    this->speedBars[SEG_SPEED_3] = SEG_INDEX_3;
    this->speedBars[SEG_SPEED_4] = SEG_INDEX_4;
    this->speedBars[SEG_SPEED_5] = SEG_INDEX_5;
}

uint8_t Fan::getFanSpeed()
{
    for (uint8_t i = 0; i <= SPEEDS_COUNT; i++)
    {
        if (!this->getDataValue(this->speedBars[i]))
            return i;
    }
    return FAN_OFF;
}