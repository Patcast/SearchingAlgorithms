#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "astar.h"
#include "commands.h"
#include "scene.h"
#include "mainwindow.h"
#include <string>



class Controller: public QObject
{
public:
    Controller(MainWindow *window, std::shared_ptr<Scene> primaryScene);
    void view_switch(std::string newState);
    void addView(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getView(std::string searchString);
    void handleCommand(std::string funct, std::vector<std::string> *commands);
    std::vector<std::string> splitString(std::string fullString, std::string delimiter);
    void displayStatus(std::string error);

    Commands commandsProcessor = Commands();
    void move(int row, int col);
    void moveAutomatically();

signals:
    void playerMoveLeft();
    void playerMoveRight();
    void playerMoveUp();
    void playerMoveDown();
    void playerMove(int x, int y);
    void updateHE();
    void algorithNodeturnOn(int specialFigureIndex);//this signa will be sent for every node that is part of the path.
    void algorithNodeturnOFF(int specialFigureIndex);

public slots:
    void move(moveDirection directionOfMovement);

private slots:
    void handleCommand();
    void posChanged(int x, int y);
    void pushButton();
    void pushButton2();

protected:
    MainWindow *controllerWindow;
    std::string currentSceneState;
    std::vector<std::shared_ptr<Scene>> sceneCollection;
    QTimer *movementTimer;
    std::vector<int> listOfIndexes;
    unsigned long currentNodeIndex{0};
    std::unique_ptr<AStar> aStarPtr;

};

#endif // CONTROLLER_H
