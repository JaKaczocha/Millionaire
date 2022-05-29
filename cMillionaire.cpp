#include "cMillionaire.h"

cMillionaire::cMillionaire()
    : stage(0), IsAnswerAvailable{1, 1, 1, 1}, IsBuoyAvailable{1, 1, 1, 1}
{

    const unsigned int MIN_QUEST_COUNT = 10;

    for (unsigned i = 0; i < STAGE_COUNT; i++)
    {
        vData[i].reserve(MIN_QUEST_COUNT);
    }
}

bool cMillionaire::CheckingAnswer()
{
    if((answer=='a'||answer=='A')&&vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="1")
    {
       return true;
    }
    else if((answer=='b'||answer=='B')&&vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="2")
    {
       return true;
    }
    else if((answer=='c'||answer=='C')&&vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="3")
    {
       return true;
    }
    else if((answer=='d'||answer=='D')&&vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="4")
    {
       return true;
    }
    else
    {
        return false;
    }

}

void cMillionaire::SelectQuestion()
{
    selectedQuestion = rand()%vData[stage].size();
}

void cMillionaire::ResetAccessFlags(const bool val)
{
    for (auto& flag : IsAnswerAvailable)
    {
        flag = val;
    }
}
