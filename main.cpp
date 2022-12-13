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
    int start = 180;
    int end = 102;
    controller.runDijktra(start,end);
    controller.runAStar(start,end);
    return 0;
}
