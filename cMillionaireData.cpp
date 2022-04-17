#include "cMillionaire.h"

#include <fstream>
#include <iostream>

bool cMillionaire::loadData()
{
    // Returns: false if OK
    try
    {
        readFile();
    }
    catch(std::string Exception)
    {
        std::cout << Exception << std::endl;
        return true;
    }
    return false;
}

void cMillionaire::readFile()
{
    std::fstream file;

}
