#include "cStageData.h"

const std::string stageData::H_TXT[COL_COUNT]{"ID", "QUESTION", "ANSWER1", "ANSWER2", "ANSWER3", "ANSWER4", "CORRECT_ANSWER"};

stageData::stageData() : nKey("")
{}

std::string& stageData::operator[](const std::string& key)
{
    nKey="";
    for (int i = 0; key[i]; i++)
    {
        nKey += toupper(key[i]);
    }

    for (int i = 0; i < COL_COUNT; i++)
    {
        if (nKey == H_TXT[i])
        {
            return headerData[i];
        }
    }

    // Returns given key if not found any match.
    return nKey;
}

std::string& stageData::operator[](const int index)
{
    return headerData[index];
}
