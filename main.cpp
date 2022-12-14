#include "astarcontroller.h"
#include "gameworld.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

GameWorld * GameWorld::instance = 0;
int main()
{


//    GameWorld * gameWord_ptr= GameWorld::Instance(":/images/worldmap.png",20,60,100.0);

    AStarController aStarController;
    aStarController.runAStar(180,102,0.2);



    return 0;
}
