#include <aircon/mode.h>

Mode::Mode() : Mode(NULL) {}

Mode::Mode(uint64_t *lcdData) : SegmentGroup(lcdData)
{
    this->modeIndices[FACE_ONLY] = IDX_FACE_ONLY;
    this->modeIndices[FACE_FEET] = IDX_FACE_FEET;
    this->modeIndices[FEET_ONLY] = IDX_FEET_ONLY;
    this->modeIndices[FEET_DEFR] = IDX_FEET_DEFR;
}

ACMode Mode::getMode()
{
    for (int8_t i = 0; i < MODE_COUNT; i++)
    {
        if (this->getDataValue(this->modeIndices[i]))
        {
            return (ACMode)i;
        }
    }
    return UNKN_MODE;
}
