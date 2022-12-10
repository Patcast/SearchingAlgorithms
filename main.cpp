#include "astarcontroller.h"
#include "gameworld.h"
#include "mainwindow.h"
#include <iostream>
#include <QApplication>

//#include "node.h"
GameWorld * GameWorld::instance = 0;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //GameWorld * gameWord_ptr= GameWorld::Instance(":/images/worldmap.png",20,60,100.0);


      AStarController controller;
      controller.executeBreadthFirstSearch(0,62);



    return a.exec();
}
