#ifndef CMILLIONAIRE_H
#define CMILLIONAIRE_H

#include <iostream>
#include <string>
#include <vector>
#include "cStageData.h"

using namespace std;

class cMillionaire : public stageData
{
public:
    cMillionaire();
    bool loadData();
    void printStageContent();

private:
    static const int STAGE_COUNT = 15;
    static const char COMMA;

    vector<stageData> vData[STAGE_COUNT]; // <- Main data structure

    void readFile();
    bool headerIsGood(string line);
    void saveLine(string line, vector<stageData>& vData);

};

#endif // CMILLIONAIRE_H
