#ifndef CMILLIONAIRE_H
#define CMILLIONAIRE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class cMillionaire
{
public:
    cMillionaire();
    bool loadData();
private:
    // Static const members can be initialize in header file of class.
    static const int ANSWER_COUNT = 4, STAGE_COUNT = 15, COL_COUNT = 7;
    static const char COMMA = ',';

    static const string H_TXT[COL_COUNT];

    // Data handling
    class stageData
    {
    public:
        stageData();
        string& operator[](const string& key);
        string& operator[](const int index);
    private:
        string headerData[COL_COUNT];
        string errorMsg;
    };

    vector<stageData> vData[STAGE_COUNT]; // Tablica 15 wektorow dla kazdego etapu

    void readFile();
    bool checkHeader(string line);
    void saveLine(string line, vector<stageData>& vData);

};

#endif // CMILLIONAIRE_H
