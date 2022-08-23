#include <aircon/digit.h>

Digit::Digit() : Digit(NULL) {};

Digit::Digit(uint64_t *lcdData) : SegmentGroup(lcdData)
{
    this->setSegmentIndices(0, 0, 0, 0, 0, 0, 0);
}

void Digit::setSegmentIndices(uint8_t sA, uint8_t sB, uint8_t sC, uint8_t sD, uint8_t sE, uint8_t sF, uint8_t sG)
{
    this->segmentIndexes[SEG_A] = sA;
    this->segmentIndexes[SEG_B] = sB;
    this->segmentIndexes[SEG_C] = sC;
    this->segmentIndexes[SEG_D] = sD;
    this->segmentIndexes[SEG_E] = sE;
    this->segmentIndexes[SEG_F] = sF;
    this->segmentIndexes[SEG_G] = sG;
}

int8_t Digit::getValue()
{
    uint8_t segments = 0;

    // Iterate through the list of index positions for
    // the segments stored in the shift register data
    for (uint8_t i = 0; i < SEG_COUNT; i++)
    {
        // Get the bit index
        uint8_t index = this->segmentIndexes[i];

        segments |= this->getDataValue(index) << ((SEG_COUNT - 1) - i);
    }

    for (uint8_t i = 0; i < 10; i++)
    {
        if (segments == this->digits[i])
            return i;
    }
    return INVALID_DIGIT;
}

bool Digit::isValid()
{
    return (this->getValue() == INVALID_DIGIT);
}