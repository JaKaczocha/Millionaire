#include "cMillionaireDisplaying.h"

int main()
{
    system("chcp 65001"); // Encoding utf-8

    cMillionaireDisplaying millionaireGame;
    if (millionaireGame.LoadData())
    {
        return 1;
    }

    millionaireGame.ClearScreen();

    millionaireGame.GameFlow();
    return 0;
}
