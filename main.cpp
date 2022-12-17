#include "astarcontroller.h"
#include "controller.h"
#include "gameworld.h"
#include "textscene.h"
#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

GameWorld * GameWorld::instance = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    TextScene textscene = TextScene();
    std::shared_ptr<TextScene> sharedTextScene = std::make_shared<TextScene>(textscene);

    GraphicsScene twoDScene = GraphicsScene();
    std::shared_ptr<GraphicsScene> sharedGraphScene = std::make_shared<GraphicsScene>(twoDScene);

    Controller controller = Controller(&window,sharedGraphScene);
    controller.addView(sharedTextScene);
    window.show();

    AStarController aStarController;
    // aStarController.runAStar(10,30,0.2);
    return 0;
}
