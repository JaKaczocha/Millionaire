#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "cMillionaire.h"



bool cMillionaire::loadData()
{
    // Returns: false if OK
    try
    {
        readFile();
    }
    catch(const logic_error& lError)
    {
        cerr << lError.what() << endl;
        return true;
    }

    return false;
}

void cMillionaire::readFile()
{
    ifstream file; // Domyslnie ustawiona zmienna do odczytu
    const string folder = "../millionaire/stages/", extension = ".csv";
    string fPath{};

    // TYLKO JEDEN PLIK W BAZIE
    //for (unsigned i = 0, fileNum = 1; i < STAGE_COUNT; i++, fileNum++)
    {
        fPath = folder + to_string(9) + extension;

        file.open(fPath);

        if (!file.good())
        {
            file.close();
            throw logic_error("Problem z otwarciem pliku: " + fPath);
        }

        /*
            Wczytanie calej jednej linii
            Wyslanie jej do funkcji, ktora sprawdza i zapisuje po kolei
            checkSave(vector<stageData>& vData, const string& line)
        */

        string line{};
        getline(file, line);
        if (checkHeader(line))
            throw logic_error("Blad w naglowku: " + fPath);

        while(getline(file, line))
        {

        }

        file.close();

    }
}

bool cMillionaire::checkHeader(string line)
{
    const char CHR_TO_LOOK = ',';
    const int COMMA_COUNT = 6, TXT_COUNT = 7;
    const string H_TXT[TXT_COUNT] = {
        "ID", "QUESTION", "ANSWER1", "ANSWER2", "ANSWER3", "ANSWER4", "CORRECT_ANSWER"
    };

    if (count(line.begin(), line.end(), ',') != COMMA_COUNT)
        return true;

    for (int i = 0; i < TXT_COUNT; i++)
    {
        string shortLine = line.substr(0, line.find_first_of(CHR_TO_LOOK));
        if (shortLine != H_TXT[i])
            return true;

        line.erase(0,shortLine.length() + 1); // + 1 beacuse of comma
    }

    return false;
}
