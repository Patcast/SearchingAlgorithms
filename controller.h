#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include <string>

class Controller
{
public:
    Controller(MainWindow window, std::string viewState = "text");
    void view_switch(std::string newState);

private:
    MainWindow controllerWindow;
    std::string currentViewState;
};

#endif // CONTROLLER_H
