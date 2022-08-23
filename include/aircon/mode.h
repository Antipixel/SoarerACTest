#ifndef MODE_H_
#define MODE_H_

#include <Arduino.h>
#include <aircon/segmentgroup.h>

#define MODE_COUNT 4
#define IDX_FACE_ONLY 14
#define IDX_FACE_FEET 15
#define IDX_FEET_ONLY 16
#define IDX_FEET_DEFR 17

enum ACMode: int8_t
{
    FACE_ONLY = 0,
    FACE_FEET = 1,
    FEET_ONLY = 2,
    FEET_DEFR = 3,
    UNKN_MODE = -1,
};

class Mode: public SegmentGroup
{
private:
    uint8_t modeIndices[MODE_COUNT];
public:
    Mode();
    Mode(uint64_t *lcdData);
    ACMode getMode(); 
};

#endif