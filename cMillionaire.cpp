#include "cMillionaire.h"

cMillionaire::cMillionaire()
{
    const unsigned int MIN_QUEST_COUNT = 10;

    for (unsigned i = 0; i < STAGE_COUNT; i++)
        vData[i].reserve(MIN_QUEST_COUNT);
}
