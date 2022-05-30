#ifndef CMILLIONAIREDISPLAYING_H
#define CMILLIONAIREDISPLAYING_H

#include "cStageData.h"
#include "cMillionaire.h"

class cMillionaireDisplaying;

typedef unsigned char uint1;
typedef void (cMillionaireDisplaying::*funDef)();

class cMillionaireDisplaying: public cMillionaire
{
public:
    cMillionaireDisplaying();
    int GameFlow();
    void ClearScreen();

private:
    int EnterAnswer();

    void DisplayQuestion();
    void DisplayAnswer();
    void DisplayColoredAnswer(const char answer);

    void ColorTxt(const string& Txt, const uint1 color);

    void EnableBuoy(const buoyType bType);
    void Buoy50_50();
    void BuoyAudience();

    void DisplayBuoyMenu();
    void BuoyAudienceDisplay();
    void BuoyFriendDisplay();

    int Votes[4]{0};
    const string stagePrize[STAGE_COUNT + 1];
};


#endif // CMILLIONAIREDISPLAYING_H
