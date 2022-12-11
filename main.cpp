#include "controller.h"
#include "graphicsscene.h"
//#include "astarcontroller.h"
//#include "gameworld.h"
#include "mainwindow.h"
#include "textscene.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

//#include "node.h"
//GameWorld * GameWorld::instance = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    // GameWorld * gameWord_ptr= GameWorld::Instance(":/images/worldmap.png",20,60,100.0);

    TextScene textscene = TextScene();
    std::shared_ptr<TextScene> sharedTextScene = std::make_shared<TextScene>(textscene);

    GraphicsScene twoDScene = GraphicsScene();
    std::shared_ptr<GraphicsScene> sharedGraphScene = std::make_shared<GraphicsScene>(twoDScene);

    Controller controller = Controller(&window,sharedGraphScene);
    controller.addView(sharedTextScene);
    window.show();

    //AStarController aStarController;
    //aStarController.executeBreadthFirstSearch(0, 62);

    return a.exec();
}
