#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "abstractview.h"
#include "mainwindow.h"
#include <string>

class Controller
{
public:
    Controller(MainWindow &window, AbstractView &primaryView);
    void view_switch(std::string newState);
    void addView(AbstractView &view);

protected:
    MainWindow &controllerWindow;
    std::string currentViewState;
    std::vector<std::reference_wrapper<AbstractView>> viewList;
};

#endif // CONTROLLER_H
