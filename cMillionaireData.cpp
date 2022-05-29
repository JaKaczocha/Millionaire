#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "cMillionaire.h"

const char cMillionaire::COMMA = ',';

bool cMillionaire::LoadData()
{
    // Returns: false if OK
    try
    {
        ReadFile();
    }
    catch(const logic_error& lError)
    {
        cerr << lError.what() << endl;
        return true;
    }

    return false;
}

bool cMillionaire::LoadFriendCall()
{
    // Returns: false if OK
    try
    {
        ReadFriendCall();
    }
    catch(const logic_error& lError)
    {
        cerr << lError.what() << endl;
        return true;
    }

    return false;
}

void cMillionaire::ReadFriendCall()
{

    ifstream file;
    const string folder = "../project_07_35244/friendCall/response.txt";
    string fPath{};

    file.open(folder,ios::in);

    if (!file.good())
    {
        file.close();
        throw logic_error("Problem z otwarciem pliku: " + folder);
    }

    int response=rand()%NUM_FRIEND_ANSWER*2+2;
    string line{};
    int lineNumber=1;
    while(getline(file, line) && lineNumber!=response)
    {
        friendCall=line;
        lineNumber++;
    }

    string correctAns;
    if(stage<5)
    {
        if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="1")
        {
           correctAns="A";
        }
        else if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="2")
        {
           correctAns="B";
        }
        else if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="3")
        {
           correctAns="C";
        }
        else if(vData[stage][selectedQuestion]["CORRECT_ANSWER"]=="4")
        {
           correctAns="D";
        }
        else
        {
            throw logic_error("Error: at stage < 5 in " + folder);

        }
    }
    else
    {
        int friendAns{};
        do
        {
            friendAns=rand()%4+1; // [1; 4]
        }while(!IsAnswerAvailable[friendAns - 1]); // <-- requires [0; 3]

        if(friendAns==1)
        {
           correctAns="A";
        }
        else if(friendAns==2)
        {
           correctAns="B";
        }
        else if(friendAns==3)
        {
           correctAns="C";
        }
        else if(friendAns==4)
        {
           correctAns="D";
        }
        else
        {
            throw logic_error("Error: at stage >= 5 in " + folder);

        }
    }

    friendCall=friendCall + correctAns + line;
    file.close();
}

void cMillionaire::ReadFile()
{
    ifstream file;
    const string folder = "../project_07_35244/stages/", extension = ".csv";
    string fPath{};

    for (unsigned i = 0, fileNum = 1; i < STAGE_COUNT; i++, fileNum++)
    {
        fPath = folder + to_string(fileNum) + extension;

        file.open(fPath);

        if (!file.good())
        {
            file.close();
            throw logic_error("Problem z otwarciem pliku: " + fPath);
        }

        string line{};
        getline(file, line);
        if (!HeaderIsGood(line))
        {
            throw logic_error("Blad w naglowku: " + fPath);
        }

        while(getline(file, line))
        {
            SaveLine(line, vData[i]);
        }

        file.close();
    }
}

bool cMillionaire::HeaderIsGood(string line)
{
    const int COMMA_COUNT = 6;

    if (count(line.begin(), line.end(), COMMA) != COMMA_COUNT)
    {
        return false;
    }

    for (int i = 0; i < COL_COUNT; i++)
    {
        string shortLine = line.substr(0, line.find_first_of(COMMA));
        if (shortLine != H_TXT[i])
        {
            return false;
        }

        line.erase(0, shortLine.length() + 1); // + 1 beacuse of comma
    }

    return true;
}

void cMillionaire::SaveLine(string line, vector<stageData>& vData)
{
    char sign{};
    bool isQuotePresent = 0;

    vData.emplace_back();

    for (int i = 0; i < COL_COUNT; i++)
    {
        sign = COMMA;
        isQuotePresent = 0;

        if (line[0] == '"')
        {
            sign = '"';
            isQuotePresent = 1;
        }

        string shortLine = line.substr(isQuotePresent, line.find(sign, isQuotePresent) - isQuotePresent); // substr(odkąd, ile_znakow)

        vData.back()[i] = shortLine;

        line.erase(0, shortLine.length() + 1 + 2 * isQuotePresent); // + 1 (comma) + 2 * isQuotePresent (quotes)
        // erase(odkad_lacznie, ile_znakow)
    }
}

