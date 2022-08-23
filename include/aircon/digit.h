#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include <Arduino.h>
#include <aircon/segmentgroup.h>

#define INVALID_DIGIT -1
#define SEG_COUNT 7
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6

class Digit: public SegmentGroup
{
private:
    uint8_t segmentIndexes[SEG_COUNT];
    uint8_t digits[10] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B };
public:
    Digit();
    Digit(uint64_t *lcdData);
    void setSegmentIndices(uint8_t sA, uint8_t sB, uint8_t sC, uint8_t sD, uint8_t sE, uint8_t sF, uint8_t sG);
    int8_t getValue();
    bool isValid();
};

#endif