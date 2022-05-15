#include "cMillionaire.h"
#include <cstdlib>
#include <ctime>

cMillionaire::cMillionaire()
{
    const unsigned int MIN_QUEST_COUNT = 10;

    for (unsigned i = 0; i < STAGE_COUNT; i++)
        vData[i].reserve(MIN_QUEST_COUNT);
}

bool cMillionaire::CheckingAnswer(int stage)
{
    if((answer=='a'||answer=='A')&&vData[stage][selectedQuestion][COL_COUNT-1]=="1")
    {
       return true;
    }
    else if((answer=='b'||answer=='B')&&vData[stage][selectedQuestion][COL_COUNT-1]=="2")
    {
       return true;
    }
    else if((answer=='c'||answer=='C')&&vData[stage][selectedQuestion][COL_COUNT-1]=="3")
    {
       return true;
    }
    else if((answer=='d'||answer=='D')&&vData[stage][selectedQuestion][COL_COUNT-1]=="4")
    {
       return true;
    }
    else
    {
        return false;
    }

}

int cMillionaire::GameFlow(cMillionaire &millionaireGame)
{
    srand( time( NULL ) );
    string next;

    for(int i=0;i<STAGE_COUNT;i++)
    {

        cout<<"etap "<<i+1<<endl;
        millionaireGame.SelectQuestion(i);
        millionaireGame.DisplayQuestion(i);
        millionaireGame.DisplayAnswer(i);
        millionaireGame.EnterAnswer(i);

        cout<<"etap "<<i+1<<endl;
        //millionaireGame.DisplayQuestion(i);
        // millionaireGame.DisplayAnswer(i,answer);
        if(!millionaireGame.CheckingAnswer(i))
        {

            cout<<"Przegrałeś. Udało ci się dojść do "<<i+1<<" etapu!"<<endl;
            break;
        }
        getchar();

        if(i==STAGE_COUNT-1)
        {
            cout<<"\nPOPRAWNA ODPOWIEDŹ!\nJESTEŚ ZWYCIĘZCĄ!\n";
            getline(cin,next,'\n');
            break;
        }
        else
        {
            cout<<"\nPOPRAWNA ODPOWIEDŹ!\nAby przejść do "<<i+2<<" etapu naciśnij ENTER.";
            getline(cin,next,'\n');
            clearScreen();
        }



        cout<<endl;
    }




    return 0;
}
