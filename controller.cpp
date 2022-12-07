#include "controller.h"
#include "ui_mainwindow.h"

Controller::Controller(std::shared_ptr<MainWindow> window, std::shared_ptr<Scene> primaryScene) : controllerWindow(window){
    // window.children()
    this->currentSceneState = primaryScene->getDescription();
    this->sceneCollection.push_back(primaryScene);
    this->controllerWindow->ui->stackedWidget->setCurrentWidget(primaryScene->getQView().get());
}

void Controller::view_switch(std::string newState) {
    this->currentSceneState = newState;

}

void Controller::addView(std::shared_ptr<Scene> scene) {

}

std::shared_ptr<Scene> Controller::getView(std::string searchString) {

}

