#include "controller.h"
#include "ui_mainwindow.h"

Controller::Controller(MainWindow &window, AbstractView &primaryView) : controllerWindow(window){
    this->viewList.push_back(primaryView);
    this->currentViewState = primaryView.getDescription();
    this->controllerWindow.ui->stackedWidget->setCurrentWidget(&primaryView.getQView());
}

void Controller::view_switch(std::string newState) {
    this->currentViewState = newState;
}

void Controller::addView(AbstractView &view) {
    this->viewList.push_back(view);
}

