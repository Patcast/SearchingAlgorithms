//#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include "gameworld.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    GameWorld gameWorld;
    gameWorld.generateWorld(":/images/worldmap.png",100.0,600,0);

    //return a.exec();
    return 0;
}
