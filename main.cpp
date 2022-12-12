//#include "mainwindow.h"
#include "astarcontroller.h"
#include "gameworld.h"
#include <iostream>
#include <QApplication>

//#include "node.h"
GameWorld * GameWorld::instance = 0;
int main()
{

    AStarController controller;
    controller.runDijktra(180,102);
    return 0;
}
