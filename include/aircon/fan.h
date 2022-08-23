#ifndef FAN_SPEED_H_
#define FAN_SPEED_H_

#include <Arduino.h>
#include <aircon/segmentgroup.h>

#define FAN_OFF 0
#define SPEEDS_COUNT 5
#define SEG_SPEED_1 0
#define SEG_SPEED_2 1
#define SEG_SPEED_3 2
#define SEG_SPEED_4 3
#define SEG_SPEED_5 4
#define SEG_INDEX_1 5 
#define SEG_INDEX_2 4
#define SEG_INDEX_3 3
#define SEG_INDEX_4 2
#define SEG_INDEX_5 18

class Fan: public SegmentGroup
{
private:
    uint8_t speedBars[SPEEDS_COUNT];
public:
    Fan();
    Fan(uint64_t *lcdData);
    uint8_t getFanSpeed();
};

#endif