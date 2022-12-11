#include "controller.h"
#include "ui_mainwindow.h"
#include <vector>
#include <sstream>

Controller::Controller(MainWindow *window, std::shared_ptr<Scene> primaryScene) : controllerWindow(window){
    // window.children()
    this->currentSceneState = primaryScene->getDescription();
    this->addView(primaryScene);
    Ui::MainWindow *ui = this->controllerWindow->ui;
    ui->stackedWidget->setCurrentWidget(primaryScene->getQView());

    window->connect(ui->lineEdit, &QLineEdit::returnPressed, this, qOverload<>(&Controller::handleCommand));
}

void Controller::view_switch(std::string newState) {
    this->currentSceneState = newState;

}

void Controller::addView(std::shared_ptr<Scene> scene) {
    this->sceneCollection.push_back(scene);
    this->controllerWindow->ui->stackedWidget->addWidget(scene->getQView());

}

std::shared_ptr<Scene> Controller::getView(std::string searchString) {

}

void Controller::handleCommand() {
    Ui::MainWindow *ui = this->controllerWindow->ui;
    std::string command = ui->lineEdit->text().toStdString();
    std::vector<std::string> commands = Controller::splitString(command, " ");
    std::string funct = commands[commands.size() - 1];
    commands.pop_back();
    ui->lineEdit->setText("");
    if (funct == "switch") {
        if (commands.size() != 1) {
            displayError("switch: Incorrect amount of arguments specified");
        } else {
            view_switch(commands[0]);
        }
    } else {
        displayError("Incorrect command");
    }
}

void Controller::handleCommand(std::string funct, std::vector<std::string> commands) {

}

std::vector<std::string> Controller::splitString(std::string fullString, std::string delimiter) {
    std::stringstream fullStringStream(fullString);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(fullStringStream, segment, delimiter[0]))
    {
       seglist.push_back(segment);
    }
    std::reverse(seglist.begin(), seglist.end());
    return seglist;
}
