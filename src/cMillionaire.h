#ifndef CMILLIONAIRE_H
#define CMILLIONAIRE_H

#include <iostream>
#include <vector>
#include "cStageData.h"

using namespace std;

class cMillionaire : public stageData
{
    friend class cMillionaireDisplaying;

public:
    cMillionaire();
    bool LoadData();

private:
    static const int STAGE_COUNT = 15;
    static const int ANSWER_COUNT = 4;
    static const int BUOY_COUNT = 3;
    static const int NUM_FRIEND_ANSWER = 10;
    static const char COMMA;

    enum buoyType
    {
        b_none,
        b_50_50,
        b_friend,
        b_audience
    };

    vector<stageData> vData[STAGE_COUNT]; // <- Main data structure

    int stage, selectedQuestion;
    char answer;
    bool IsAnswerAvailable[ANSWER_COUNT], IsBuoyAvailable[BUOY_COUNT + 1]; // +1 to match enum buoyType
    string friendCall;

    void ResetAccessFlags(const bool val);

    void ReadFriendCall();

    void ReadFile();
    bool HeaderIsGood(string line);
    void SaveLine(string line, vector<stageData>& vData);

    bool LoadFriendCall();
    void SelectQuestion();
    bool CheckingAnswer();
};

#endif // CMILLIONAIRE_H
