#include <aircon/segmentgroup.h>

SegmentGroup::SegmentGroup(uint64_t *lcdData)
{
    this->lcdData = lcdData;
}

uint8_t SegmentGroup::getDataValue(uint8_t index)
{
    return (*this->lcdData >> index) & 0x1;
}