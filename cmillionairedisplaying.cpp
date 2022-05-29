#include <windows.h>
#include <random>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <list>
#include "cMillionaireDisplaying.h"

static inline int ctoi(const char c)
{
    // Works on [0; 9] chars
    // Returns given character if conversion can't happen
    return (c >= '0' && c <= '9') ? c - '0' : c;
}

cMillionaireDisplaying::cMillionaireDisplaying()
    : stagePrize{"0", "100", "200", "300", "500", "1'000", "2'000", "4'000", "8'000", "16'000", "32'000",
                 "64'000", "125'000", "250'000", "500'000", "1'000'000"}
{}

int cMillionaireDisplaying::EnterAnswer()
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
    ClearScreen();

    cout<<"*ETAP* "<<stage+1 << '\n';

    DisplayBuoyMenu();
    DisplayQuestion();
    DisplayColoredAnswer(answer);

    return b_none;
}
void cMillionaireDisplaying::DisplayQuestion()
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);
    cout<< vData[stage][selectedQuestion]["QUESTION"] <<endl;
}

void cMillionaireDisplaying::DisplayAnswer()
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
            ColorTxt( string(1, ansChar)  + "." + vData[stage][selectedQuestion][i] + "   ", 0x00);
        }
    }
    cout << '\n';
}
void cMillionaireDisplaying::DisplayColoredAnswer(const char answer)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hOut,15);

    for(int i=2;i<COL_COUNT-1;i++)
    {

        switch(i)
        {
        case 2:
            if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="1")
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
            if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="2")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="2")&&(answer=='b'||answer=='B'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"B."<<vData[stage][selectedQuestion][i]<<"    ";
            SetConsoleTextAttribute(hOut,15);
            break;

        case 4:
            if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="3")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="3")&&(answer=='c'||answer=='C'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"C."<<vData[stage][selectedQuestion][i]<<"   ";
            SetConsoleTextAttribute(hOut,15);
            break;

        default:
            if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="4")
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN );
            }
            else if(!(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="4")&&(answer=='d'||answer=='D'))
            {
                SetConsoleTextAttribute( hOut, FOREGROUND_RED );
            }
            cout<<"D."<< vData[stage][selectedQuestion][i]<<endl;
            SetConsoleTextAttribute(hOut,15);
            break;

        }
    }
}


void cMillionaireDisplaying::ClearScreen()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}
int cMillionaireDisplaying::GameFlow()
{
    srand( static_cast<unsigned int>(time( NULL )));
    string next;
    buoyType bType = b_none;

    for(; this->stage < STAGE_COUNT; this->stage++)
    {
        SelectQuestion();

        do
        {
            ClearScreen();

            cout << "*ETAP* "<< stage + 1 << '\n';
            if (0 < stage)
            {
                cout << "Masz ";
                ColorTxt(stagePrize[stage] + "$\n", 0x02);
            }
            cout << "Grasz o ";
            ColorTxt(stagePrize[stage+1] + "$\n", 0x04);

            EnableBuoy( bType);
            DisplayBuoyMenu();
            DisplayQuestion();
            DisplayAnswer();

            bType = buoyType(EnterAnswer());

        } while (bType != b_none);

        if(!CheckingAnswer())
        {

            cout << "\nPrzegrałeś. Udało ci się dojść do "<<stage+1<<" etapu!"<<endl;
            cout << "Twoja nagroda to: ";
            ColorTxt(stagePrize[stage] + "$\n", 0x0A);
            break;
        }

        if(stage==STAGE_COUNT-1)
        {
            cout<<"\nPOPRAWNA ODPOWIEDŹ!\nJESTEŚ ZWYCIĘZCĄ!\n";
            cout << "$ NAGRODA $\n";
            ColorTxt(stagePrize[stage+1], 0x0E);
            getline(cin,next,'\n');
            break;
        }
        else
        {
            cout<<"\nPOPRAWNA ODPOWIEDŹ!\nMasz juz w kieszeni " << stagePrize[stage+1] << "$\nAby przejść do "<<stage+2<<" etapu naciśnij ENTER.";
            getline(cin,next,'\n');
            ClearScreen();
        }

        cout<<endl;

        ResetAccessFlags(1);
    }
    return 0;
}

void cMillionaireDisplaying::DisplayBuoyMenu()
{
    cout << "\t\t\t*        KOŁA RATUNKOWE       *\n";
    cout << "\t\t\t*-----------------------------*\n";
    cout << "\t\t\t| 1. ";
    ColorTxt(        "50/50", IsBuoyAvailable[b_50_50] ? 0x0F : 0x04);
    cout <<               "                    |\n";
    cout << "\t\t\t| 2. ";
    ColorTxt(        "Telefon do przyjaciela", IsBuoyAvailable[b_friend] ? 0x0F : 0x04);
    cout <<                                "   |\n";
    cout << "\t\t\t| 3. ";
    ColorTxt(        "Pytanie do publiczności", IsBuoyAvailable[b_audience] ? 0x0F : 0x04);
    cout <<                                 "  |\n";
    cout << "\t\t\t*-----------------------------*\n";
    cout << "\t\t\t*Wybranie 1/2/3 to użycie koła*\n\n";

}

void cMillionaireDisplaying::EnableBuoy(const buoyType bType)
{
    static int currentStage = -1;
    static list<funDef> funList;

    // Delete all list elements if stage has changed
    if (currentStage != stage)
    {
        funList.clear();
    }

    switch(bType)
    {
        case b_50_50: {
            if (IsBuoyAvailable[b_50_50])
            {
                IsBuoyAvailable[b_50_50] = 0;
                Buoy50_50();
            }
            break;
        }
        case b_friend: {

            if (IsBuoyAvailable[b_friend])
            {
                IsBuoyAvailable[b_friend] = 0;
                LoadFriendCall();
                funList.push_front(&cMillionaireDisplaying::BuoyFriendDisplay);
            }
            break;
        }
        case b_audience: {
            if (IsBuoyAvailable[b_audience])
            {
                IsBuoyAvailable[b_audience] = 0;
                BuoyAudience();
                funList.push_front(&cMillionaireDisplaying::BuoyAudienceDisplay);
            }
            break;
        }
         case b_none:{
            return;
            break;
        }
    }
    // Call every function in list
    for (list<funDef>::iterator iter = funList.begin(); iter != funList.end(); iter++)
    {
        (this->*(*iter))(); // iter is pointer to function pointer
    }
    currentStage = stage;
}

void cMillionaireDisplaying::Buoy50_50()
{
    ResetAccessFlags(0);

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

void cMillionaireDisplaying::BuoyAudience()
{
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
}

void cMillionaireDisplaying::BuoyAudienceDisplay()
{
    ColorTxt("\nPytanie do publiczności...", 0x06);

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

void cMillionaireDisplaying::BuoyFriendDisplay()
{
    ColorTxt("\nTelefon do przyjaciela...\n", 0x06);
    cout<<friendCall<< "\n\n";
}

void cMillionaireDisplaying::ColorTxt(const string& Txt, const uint1 color)
{
    HANDLE hOut;
    hOut = GetStdHandle( STD_OUTPUT_HANDLE );

    SetConsoleTextAttribute(hOut, color);
    cout << Txt;
    SetConsoleTextAttribute(hOut, 0x0F); // Reseting console text to white
}
