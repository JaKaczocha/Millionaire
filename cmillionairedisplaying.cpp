#include <windows.h>//.
#include "cmillionairedisplaying.h"

#include <cstdlib>
#include <ctime>

cMillionaireDisplaying::cMillionaireDisplaying()
{

}
void cMillionaireDisplaying::EnterAnswer(int stage)
{

    do
    {
        cout<<"Twoja odpowiedź:_\b";
        cin>>answer;
    }while(answer!='a'&&answer!='b'&&answer!='c'&&answer!='d'
           &&answer!='A'&&answer!='B'&&answer!='C'&&answer!='D');
    clearScreen();
    DisplayQuestion(stage);
    DisplayAnswer(stage,answer);

}
void cMillionaireDisplaying::DisplayQuestion(int stage)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);
    cout<< vData[stage][selectedQuestion][1] <<endl;
}

void cMillionaireDisplaying::DisplayAnswer(int stage)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);
    for(int i=2;i<cMillionaire::COL_COUNT-1;i++)
    {

        switch(i)
        {
        case 2:
            cout<<"A."<<vData[stage][selectedQuestion][i]<<"   ";

                break;
        case 3:
            cout<<"B."<<vData[stage][selectedQuestion][i]<<"    ";
            break;

        case 4:
            cout<<"C."<<vData[stage][selectedQuestion][i]<<"   ";

            break;

        default:
            cout<<"D."<< vData[stage][selectedQuestion][i]<<endl;
            break;

        }
    }
}
void cMillionaireDisplaying::DisplayAnswer(int stage,char answer)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);



    for(int i=2;i<COL_COUNT-1;i++)
    {

        switch(i)
        {
        case 2:
            if(vData[stage][selectedQuestion][COL_COUNT-1]=="1")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="1")&&(answer=='a'||answer=='A'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"A."<<vData[stage][selectedQuestion][i]<<"   ";
            SetConsoleTextAttribute(hOut,15);

                break;
        case 3:
            if(vData[stage][selectedQuestion][COL_COUNT-1]=="2")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion][COL_COUNT-1]=="2")&&(answer=='b'||answer=='B'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"B."<<vData[stage][selectedQuestion][i]<<"    ";
            SetConsoleTextAttribute(hOut,15);
            break;

        case 4:
            if(vData[stage][selectedQuestion][COL_COUNT-1]=="3")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion][COL_COUNT-1]=="3")&&(answer=='c'||answer=='C'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"C."<<vData[stage][selectedQuestion][i]<<"   ";
            SetConsoleTextAttribute(hOut,15);
            break;

        default:
            if(vData[stage][selectedQuestion][COL_COUNT-1]=="4")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion][COL_COUNT-1]=="4")&&(answer=='d'||answer=='D'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"D."<< vData[stage][selectedQuestion][i]<<endl;
            SetConsoleTextAttribute(hOut,15);
            break;

        }
    }
}


void cMillionaireDisplaying::clearScreen()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}
int cMillionaireDisplaying::GameFlow()
{
    srand( time( NULL ) );
    string next;

    for(int i=0;i<STAGE_COUNT;i++)
    {

        cout<<"etap "<<i+1<<endl;
        SelectQuestion(i);
        DisplayQuestion(i);
        DisplayAnswer(i);
        EnterAnswer(i);

        cout<<"etap "<<i+1<<endl;
        //millionaireGame.DisplayQuestion(i);
        // millionaireGame.DisplayAnswer(i,answer);
        if(!CheckingAnswer(i))
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
