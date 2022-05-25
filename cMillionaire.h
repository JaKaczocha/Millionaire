#ifndef CMILLIONAIRE_H
#define CMILLIONAIRE_H

#include <iostream>
#include <string>
#include <vector>
#include "cStageData.h"
//#include "cmillionairedisplaying.h"

class cMillionaireDisplaying;

using namespace std;



class cMillionaire : public stageData
{
    friend class cMillionaireDisplaying;
public:

    cMillionaire();
    bool loadData();
    void printStageContent();
    void SelectQuestion(int );
    bool CheckingAnswer(int);

private:
    static const int STAGE_COUNT = 15;
    static const int ANSWER_COUNT = 4;
    static const int BUOY_COUNT = 3;
    static const char COMMA;

    vector<stageData> vData[STAGE_COUNT]; // <- Main data structure

    int selectedQuestion; //.
    char answer;//.
    bool IsAnswerAvailable[ANSWER_COUNT];
    bool IsBuoyAvailable[BUOY_COUNT + 1]; // +1 to match enum buoyType

    void resetAccessFlags(const bool val);

    void readFile();
    bool headerIsGood(string line);
    void saveLine(string line, vector<stageData>& vData);

    enum buoyType
    {
        b_none,
        b_50_50,
        b_friend,
        b_audience
    };



};

#endif // CMILLIONAIRE_H
