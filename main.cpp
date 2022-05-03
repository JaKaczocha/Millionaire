#include "cMillionaire.h"

int main()
{
    system("chcp 65001"); // Encoding utf-8
    system("cls");

    cMillionaire millionaireGame;
    millionaireGame.loadData();
    return 0;
}
