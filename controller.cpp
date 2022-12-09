#include "controller.h"
#include "ui_mainwindow.h"

Controller::Controller(MainWindow *window, std::shared_ptr<Scene> primaryScene) : controllerWindow(window){
    // window.children()
    this->currentSceneState = primaryScene->getDescription();
    this->sceneCollection.push_back(primaryScene);
    QWidget *firstPageWidget = new QWidget;
    this->controllerWindow->ui->stackedWidget->addWidget(firstPageWidget);
    this->controllerWindow->ui->stackedWidget->addWidget(primaryScene->getQView());
    this->controllerWindow->ui->stackedWidget->setCurrentWidget(primaryScene->getQView());
}

void Controller::view_switch(std::string newState) {
    this->currentSceneState = newState;

}

void Controller::addView(std::shared_ptr<Scene> scene) {

}

std::shared_ptr<Scene> Controller::getView(std::string searchString) {

}

