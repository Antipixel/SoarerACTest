#ifndef SEGMENT_GROUP_H_
#define SEGMENT_GROUP_H_

#include <Arduino.h>

class SegmentGroup
{
protected:
    uint64_t *lcdData;
public:
    SegmentGroup(uint64_t *lcdData);
protected:
    uint8_t getDataValue(uint8_t index);
};

#endif