#ifndef CSTAGEDATA_H
#define CSTAGEDATA_H

#include <string>

class stageData
{

public:
    stageData();
    std::string& operator[](const std::string& key);
    std::string& operator[](const int index);

protected:
    static const int COL_COUNT = 7;
    static const std::string H_TXT[COL_COUNT];

    std::string headerData[COL_COUNT];
    std::string nKey;
};

#endif // CSTAGEDATA_H
