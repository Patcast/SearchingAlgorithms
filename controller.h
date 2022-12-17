#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "commands.h"
#include "scene.h"
#include "mainwindow.h"
#include <string>
#include "game_config.h"



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
signals:
    void playerMoveLeft();
    void playerMoveRight();
    void playerMoveUp();
    void playerMoveDown();
    void playerMove(int x, int y);
    void updateHE();


private slots:
  void handleCommand();
  void move(NextDirection directionOfMovement);
  void pushButton();
  void pushButton2();

protected:
    MainWindow *controllerWindow;
    std::string currentSceneState;
    std::vector<std::shared_ptr<Scene>> sceneCollection;
    GameWorld* gameWord_ptr;
};

#endif // CONTROLLER_H
