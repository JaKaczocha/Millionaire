#include <windows.h>
#include "cmillionairedisplaying.h"
#include <random>
#include <cstdlib>
#include <cstdio>
#include <ctime>

static inline int ctoi(const char c)
{
    // Works on [0; 9] chars
    // Returns given character if conversion can't happen

    return (c >= '0' && c <= '9') ? c - '0' : c;
}

cMillionaireDisplaying::cMillionaireDisplaying() {}

int cMillionaireDisplaying::EnterAnswer(int stage)
{
    do
    {
        cout<<"Twoja odpowiedź:_\b";
        cin>>answer;
        cin.ignore(1024, '\n'); // Clearing stream from additional characters till '\n'

    }while(answer!='a'&&answer!='b'&&answer!='c'&&answer!='d'
           &&answer!='A'&&answer!='B'&&answer!='C'&&answer!='D'
           && answer != '1' && answer != '2' && answer != '3');
    if (answer == '1' || answer == '2' || answer == '3')
    {
        return ctoi(answer);
    }
    clearScreen();

    cout<<"*ETAP* "<<stage+1 << '\n';

    DisplayBuoyMenu();
    DisplayQuestion(stage);
    DisplayColoredAnswer(stage,answer);

    return b_none;
}
void cMillionaireDisplaying::DisplayQuestion(int stage)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);
    cout<< vData[stage][selectedQuestion]["QUESTION"] <<endl;
}

void cMillionaireDisplaying::DisplayAnswer(int stage)
{
    char ansChar = 'A';
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);
    for(int i = 2, j = 0; i<cMillionaire::COL_COUNT-1; i++, j++, ansChar++)
    {

        if (IsAnswerAvailable[j])
        {
            cout << ansChar << '.' << vData[stage][selectedQuestion][i] << "   ";
        }
        else
        {
            // Blanking answer
            colorTxt( string(1, ansChar)  + "." + vData[stage][selectedQuestion][i] + "   ", 0x00);
        }
//        switch(i)
//        {
//        case 2:
//            cout<<"A."<<vData[stage][selectedQuestion][i]<<"   ";

//                break;
//        case 3:
//            cout<<"B."<<vData[stage][selectedQuestion][i]<<"    ";
//            break;

//        case 4:
//            cout<<"C."<<vData[stage][selectedQuestion][i]<<"   ";

//            break;

//        default:
//            cout<<"D."<< vData[stage][selectedQuestion][i]<<endl;
//            break;

//        }
    }
    cout << '\n';
}
void cMillionaireDisplaying::DisplayColoredAnswer(int stage,char answer)
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
        SelectQuestion(i);

        buoyType bType = b_none;
        do
        {
            clearScreen();

            cout<<"*ETAP* "<<i+1<<endl;

            enableBuoy(i, bType);
            DisplayBuoyMenu();
            DisplayQuestion(i);
            DisplayAnswer(i);

            bType = buoyType(EnterAnswer(i));

        }
        while (bType != b_none);

        //millionaireGame.DisplayQuestion(i);
        // millionaireGame.DisplayAnswer(i,answer);
        if(!CheckingAnswer(i))
        {

            cout<<"Przegrałeś. Udało ci się dojść do "<<i+1<<" etapu!"<<endl;
            break;
        }
        // getchar();

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

        resetAccessFlags(1);
    }
    return 0;
}

void cMillionaireDisplaying::DisplayBuoyMenu()
{
    cout << "\t\t\t*        KOŁA RATUNKOWE       *\n";
    cout << "\t\t\t*-----------------------------*\n";
    cout << "\t\t\t| 1. ";
    colorTxt(        "50/50", IsBuoyAvailable[b_50_50] ? 0x0F : 0x04);
    cout <<               "                    |\n";
    cout << "\t\t\t| 2. ";
    colorTxt(        "Telefon do przyjaciela", IsBuoyAvailable[b_friend] ? 0x0F : 0x04);
    cout <<                                "   |\n";
    cout << "\t\t\t| 3. ";
    colorTxt(        "Pytanie do publiczności", IsBuoyAvailable[b_audience] ? 0x0F : 0x04);
    cout <<                                 "  |\n";
    cout << "\t\t\t*-----------------------------*\n";
    cout << "\t\t\t*Wybranie 1/2/3 to użycie koła*\n\n";

}

void cMillionaireDisplaying::enableBuoy(const int stage, buoyType bType)
{
    switch(bType)
    {
    case b_50_50: {
        if (IsBuoyAvailable[b_50_50])
        {
            IsBuoyAvailable[b_50_50] = 0;
            Buoy_50_50(stage);
        }
        break;
    }
    case b_friend: {

        if (IsBuoyAvailable[b_friend])
        {
            IsBuoyAvailable[b_friend] = 0;
            cout << "\nFRIEND CALL\n\n";
        }
        else if(whenFriend==stage)
        {
            cout<<"FRIEND CALL\n\n";
        }
        break;
    }
    case b_audience: {
        if (IsBuoyAvailable[b_audience])
        {
            IsBuoyAvailable[b_audience] = 0;
            Buoy_Audience(stage);
        }
        else if(whenAudience==stage)
        {
            Buoy_Audience_Display();
        }
        break;
    }
     case b_none:{
        return;
        break;
    }

    }
}

void cMillionaireDisplaying::Buoy_50_50(const int stage)
{
    resetAccessFlags(0);

    string correctAnswer = vData[stage][selectedQuestion]["CORRECT_ANSWER"];
    int Ans1 = stoi(correctAnswer) - 1, Ans2;
    do
    {
        Ans2 = rand() % ANSWER_COUNT;
    }
    while (Ans2 == Ans1);

    IsAnswerAvailable[Ans1] = 1;
    IsAnswerAvailable[Ans2] = 1;

    // Ans1 <- correct, Ans2 <- random
}

void cMillionaireDisplaying::Buoy_Audience(int stage)
{
    whenAudience=stage;

    int Ans;
    int index=stoi(vData[stage][selectedQuestion]["CORRECT_ANSWER"])-1;
    Votes[index]=rand()%51+50;
    for(int i=0;i<100-Votes[index];i++)
    {
        do
        {
            Ans=rand()%4;

        }while(!IsAnswerAvailable[Ans] || Ans==index);
        Votes[Ans]++;

    }
    Buoy_Audience_Display();
}

void cMillionaireDisplaying::Buoy_Audience_Display()
{
    cout<<"\nA."<<Votes[0]<<"%";
    if(Votes[0]<10)
    {
        cout<<" ";
    }
    cout<<"|";
    for(int z=0;z<Votes[0];z++)
    {
        cout<<"*";
    }

    cout<<"\nB."<<Votes[1]<<"%";
    if(Votes[1]<10)
    {
        cout<<" ";
    }
    cout<<"|";
    for(int z=0;z<Votes[1];z++)
    {
        cout<<"*";
    }

    cout<<"\nC."<<Votes[2]<<"%";
    if(Votes[2]<10)
    {
        cout<<" ";
    }
    cout<<"|";
    for(int z=0;z<Votes[2];z++)
    {
        cout<<"*";
    }

    cout<<"\nD."<<Votes[3]<<"%";
    if(Votes[3]<10)
    {
        cout<<" ";
    }
    cout<<"|";
    for(int z=0;z<Votes[3];z++)
    {
        cout<<"*";
    }

    cout<<"\n\n";
}
void cMillionaireDisplaying::colorTxt(const string& Txt, uint1 color)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );

    SetConsoleTextAttribute(hOut, color);
    cout << Txt;
    SetConsoleTextAttribute(hOut, 0x0F); // Reseting console text to white
}
