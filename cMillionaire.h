#ifndef CMILLIONAIRE_H
#define CMILLIONAIRE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define ANSWER_COUNT 4
#define STAGE_COUNT 15

class cMillionaire
{
public:
    cMillionaire();
    bool loadData();
private:
    // Data handling
    struct stageData
    {
        unsigned int id;
        string question;
        string Answer[ANSWER_COUNT];
        char correctAnswer;
    };

    vector<stageData> vData[STAGE_COUNT]; // Tablica 15 wektorow dla kazdego etapu

    void readFile();
    bool checkHeader(string line);

};

#endif // CMILLIONAIRE_H
