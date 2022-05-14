#include "cMillionaire.h"
#include <cstdlib>
#include <ctime>

cMillionaire::cMillionaire()
{
    const unsigned int MIN_QUEST_COUNT = 10;

    for (unsigned i = 0; i < STAGE_COUNT; i++)
        vData[i].reserve(MIN_QUEST_COUNT);
}


int cMillionaire::GameFlow(cMillionaire &millionaireGame)
{
    srand( time( NULL ) );
    for(int i=0;i<STAGE_COUNT;i++)
    {
        millionaireGame.SelectQuestion(i);
        millionaireGame.DisplayQuestion(i);
        millionaireGame.DisplayAnswer(i);
        cout<<endl;
    }


    return 0;
}
