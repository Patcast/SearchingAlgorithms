#include "controller.h"
#include "gameworld.h"
#include "graphicsscene.h"
#include "mainwindow.h"
#include "textscene.h"
#include "graphicsscene.h"
#include <iostream>
#include <QApplication>
#include <QtGui>

GameWorld* GameWorld::instance{nullptr};
std::mutex GameWorld::mutex_;
int main(int argc, char *argv[])
{
    GameWorld * gameWord_ptr= GameWorld::Instance();
    gameWord_ptr->setGameMap(":/images/maze3.png",20,60,100.0);

    QApplication a(argc, argv);
    MainWindow window;

    TextScene textscene = TextScene();
    std::shared_ptr<TextScene> sharedTextScene = std::make_shared<TextScene>(textscene);

    GraphicsScene twoDScene = GraphicsScene();
    std::shared_ptr<GraphicsScene> sharedGraphScene = std::make_shared<GraphicsScene>(twoDScene);

    Controller controller = Controller(&window,sharedGraphScene);
    controller.addView(sharedTextScene);
    window.show();
    window.setSignalsFromProtagnist();


    return a.exec();
}
