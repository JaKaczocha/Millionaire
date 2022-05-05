#include "cMillionaire.h"

void clearScreen();

int main()
{
    system("chcp 65001"); // Encoding utf-8
    clearScreen();

    cMillionaire millionaireGame;
    if (millionaireGame.loadData())
        return 1;


    millionaireGame.printStageContent();
    return 0;
}

void clearScreen()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}
