#include "cMillionaire.h"

int main()
{
    system("chcp 65001"); // Encoding utf-8


    cMillionaire millionaireGame;
    if (millionaireGame.loadData())
        return 1;

    millionaireGame.clearScreen();

   millionaireGame.GameFlow(millionaireGame);


    return 0;
}
