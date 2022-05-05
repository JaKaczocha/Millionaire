#include "cMillionaire.h"

int main()
{
    system("chcp 65001"); // Encoding utf-8
    system("cls");

    cMillionaire millionaireGame;
    if (millionaireGame.loadData())
        return 1;


    millionaireGame.printStageContent();
    return 0;
}
