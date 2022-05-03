#include "cMillionaire.h"

const string cMillionaire::H_TXT[COL_COUNT]{"ID", "QUESTION", "ANSWER1", "ANSWER2", "ANSWER3", "ANSWER4", "CORRECT_ANSWER"};

cMillionaire::cMillionaire()
{
    const unsigned int MIN_QUEST_COUNT = 10;

    for (unsigned i = 0; i < STAGE_COUNT; i++)
        vData[i].reserve(MIN_QUEST_COUNT);
}


