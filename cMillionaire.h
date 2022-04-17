#ifndef CMILLIONAIRE_H
#define CMILLIONAIRE_H

#include <string>
#include <vector>

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
        std::string Question;
        std::string Answer[ANSWER_COUNT];
        std::string CorrectAnswer;
    };

    std::vector<stageData> vData[STAGE_COUNT]; // Tablica 15 wektorow dla kazdego etapu

    void readFile();

};

#endif // CMILLIONAIRE_H
