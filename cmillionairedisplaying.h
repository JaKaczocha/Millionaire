#ifndef CMILLIONAIREDISPLAYING_H
#define CMILLIONAIREDISPLAYING_H

#include "cStageData.h"
#include "cMillionaire.h"

typedef unsigned char uint1;
typedef void (cMillionaireDisplaying::*funDef)();

class cMillionaireDisplaying: public cMillionaire
{

public:
    cMillionaireDisplaying();
    int GameFlow();
    int EnterAnswer();
    void DisplayQuestion();
    void DisplayAnswer();
    void DisplayColoredAnswer(char);
    void clearScreen();
    void colorTxt(const string& Txt, uint1 color);

    void DisplayBuoyMenu();
    void enableBuoy(buoyType);
    void Buoy_50_50();
    void Buoy_Audience();
    void Buoy_Audience_Display();
    void Buoy_Friend_Display();

    int Votes[4]{0};
};

#endif // CMILLIONAIREDISPLAYING_H
