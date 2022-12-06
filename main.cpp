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
      controller.executeBreadthFirstSearch(0,11);

    return 0;
}
