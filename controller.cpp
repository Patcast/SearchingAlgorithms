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
    try {
        std::shared_ptr<Scene> destination = getView(newState);
        this->currentSceneState = newState;
        this->controllerWindow->ui->stackedWidget->setCurrentWidget(destination->getQView());
        displayStatus("switch: scene '" + newState + "' set");
    }
    catch (std::string errorScene) {
        displayStatus("switch: scene '" + errorScene + "' not found");
    }


}

void Controller::addView(std::shared_ptr<Scene> scene) {
    this->sceneCollection.push_back(scene);
    this->controllerWindow->ui->stackedWidget->addWidget(scene->getQView());

}

std::shared_ptr<Scene> Controller::getView(std::string searchString) {
    auto ptr = std::find_if(begin(this->sceneCollection), end(this->sceneCollection), [&](std::shared_ptr<Scene> const& current)
    {
      return *current == searchString;
    });
    if (ptr != end(this->sceneCollection)) {
        std::shared_ptr<Scene> foundScene = *ptr;
        return foundScene;
    } else {
        throw(searchString);
    }
}

void Controller::handleCommand() {
    Ui::MainWindow *ui = this->controllerWindow->ui;
    std::string commandString = ui->lineEdit->text().toStdString();
    std::vector<std::string> commands = Controller::splitString(commandString, " ");
    std::string funct = commands[commands.size() - 1];
    commands.pop_back();
    ui->lineEdit->setText("");
    handleCommand(funct, &commands);
}

void Controller::move(int directionOfMovement)
{

}



void Controller::handleCommand(std::string funct, std::vector<std::string> *commands) {
    if (funct == "switch") {
        if (commands->size() != 1) {
            displayStatus("switch: Incorrect amount of arguments specified");
        } else {
            std::string result = commands->at(0);
            view_switch(result);
        }
    } else {
        displayStatus("Incorrect command");
    }
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

void Controller::displayStatus(std::string error) {
    this->controllerWindow->ui->label->setText(QString::fromStdString(error));
}
