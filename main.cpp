#include "cmillionairedisplaying.h"

int main()
{
    system("chcp 65001"); // Encoding utf-8


    cMillionaireDisplaying millionaireGame;
    if (millionaireGame.loadData())
        return 1;

    millionaireGame.clearScreen();

   millionaireGame.GameFlow();


    return 0;
}
