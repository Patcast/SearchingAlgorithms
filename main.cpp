#include "astarcontroller.h"
#include "gameworld.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

GameWorld * GameWorld::instance = 0;
int main()
{
    AStarController aStarController;
    aStarController.runAStar(90,432,0);
    return 0;
}
