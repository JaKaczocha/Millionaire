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
};

#endif // CMILLIONAIREDISPLAYING_H
