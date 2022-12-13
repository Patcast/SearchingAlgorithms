#ifndef CONTROLLER_H
#define CONTROLLER_H

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

private slots:
  void handleCommand();
  void move(int directionOfMovement);

protected:
    MainWindow *controllerWindow;
    std::string currentSceneState;
    std::vector<std::shared_ptr<Scene>> sceneCollection;
};

#endif // CONTROLLER_H
