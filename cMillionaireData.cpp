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
    const string folder = "../millionaire/stages/", extension = ".csv";  // <---------- ZMIENIC FOLDER - po clone bedzie inna nazwa
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
            // Najpierw zapisac do struktory pozniej sprawdzac ID czy sie dubluje
            saveLine(line, vData[i]);
        }

        file.close();

    }
    for (int etap = 0; etap < STAGE_COUNT; etap++)
    {
        cout << "Etap " << etap << '\n';
        for (int linia = 0; linia < vData[etap].size(); linia++)
        {
            cout << vData[etap][linia]["QUESTION"] << "\n";
        }
        cout << '\n';
    }


}

bool cMillionaire::checkHeader(string line)
{
    const int COMMA_COUNT = 6;

    if (count(line.begin(), line.end(), COMMA) != COMMA_COUNT)
        return true;

    for (int i = 0; i < COL_COUNT; i++)
    {
        string shortLine = line.substr(0, line.find_first_of(COMMA));
        if (shortLine != H_TXT[i])
            return true;

        line.erase(0, shortLine.length() + 1); // + 1 beacuse of comma
    }

    return false;
}

void cMillionaire::saveLine(string line, vector<stageData>& vData)
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
        // DEBUG
        // cout << line << "  FIND( '"<< sign << "', " << isQuotePresent << " ) -> "<< line.find(sign, isQuotePresent) << '\n';
        // cout << shortLine << '\n';
        // vData.emplace_back( pair<string, string>(H_TXT[i], shortLine));

        // NEW IDEA

        vData.back()[i] = shortLine;

        line.erase(0, shortLine.length() + 1 + 2 * isQuotePresent); // + 1 beacuse of comma
        // erase(odkad_lacznie, ile_znakow)
    }
}

// stageData class

cMillionaire::stageData::stageData() : errorMsg("")
{}

string& cMillionaire::stageData::operator[](const string& key)
{
    for (int i = 0; i < COL_COUNT; i++)
    {
        if (key == H_TXT[i])
            return headerData[i];
    }
    return errorMsg;
}

string& cMillionaire::stageData::operator[](const int index)
{
    return headerData[index];
}

