#ifndef CMILLIONAIREDISPLAYING_H
#define CMILLIONAIREDISPLAYING_H

#include "cStageData.h"
#include "cMillionaire.h"


class cMillionaireDisplaying:public cMillionaire
{

public:
    cMillionaireDisplaying();
    int GameFlow();//transitional place
    void EnterAnswer(int);//transitional place
    void DisplayQuestion(int);
    void DisplayAnswer(int);
    void DisplayAnswer(int,char);
    void clearScreen();

    void DisplayBuoys(const int);
    void Buoy_50_50(const int);
};

#endif // CMILLIONAIREDISPLAYING_H
