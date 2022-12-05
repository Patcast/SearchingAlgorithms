//#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include "gameworld.h"
//#include "node.h"

int main()
{

    GameWorld gameWorld;
    gameWorld.generateWorld(":/images/worldmap.png",20,60,100.0);
    gameWorld.makeSubsetOfTiles(3,4);
    gameWorld.printSubSetOftiles();

    std::shared_ptr<Node> n1 = gameWorld.getNode(11);



    return 0;
}
