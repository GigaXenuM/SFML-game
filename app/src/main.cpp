#include "mainwindow.h"

int main()
{
    MainWindow window{ 800, 600, "Game" };
    return window.gameLoop();
}
