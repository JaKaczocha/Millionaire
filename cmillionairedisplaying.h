#ifndef CMILLIONAIREDISPLAYING_H
#define CMILLIONAIREDISPLAYING_H

#include "cStageData.h"
#include "cMillionaire.h"

typedef unsigned char uint1;

class cMillionaireDisplaying: public cMillionaire
{

public:
    cMillionaireDisplaying();
    int GameFlow();//transitional place
    int EnterAnswer(int);//transitional place
    void DisplayQuestion(int);
    void DisplayAnswer(int);
    void DisplayColoredAnswer(int,char);
    void clearScreen();
    void colorTxt(const string& Txt, uint1 color);

    void DisplayBuoyMenu();
    void enableBuoy(const int, buoyType);
    void Buoy_50_50(const int);
};

#endif // CMILLIONAIREDISPLAYING_H
