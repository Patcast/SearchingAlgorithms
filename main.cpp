#include "astarcontroller.h"
#include "gameworld.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

GameWorld * GameWorld::instance = 0;
int main()
{



    AStarController aStarController;
    aStarController.runAStar(0,5000001,0.2);



    return 0;
}
