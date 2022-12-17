#include "controller.h"
#include "ui_mainwindow.h"
#include <vector>
#include <sstream>
#include "gameworld.h"

Controller::Controller(MainWindow *window, std::shared_ptr<Scene> primaryScene) : controllerWindow(window){
    // window.children()
    this->currentSceneState = primaryScene->getDescription();
    this->addView(primaryScene);
    Ui::MainWindow *ui = this->controllerWindow->ui;
    ui->stackedWidget->setCurrentWidget(primaryScene->getQView());
    window->connect(ui->lineEdit, &QLineEdit::returnPressed, this, qOverload<>(&Controller::handleCommand));
    window->connect(ui->pushButton, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton));
    window->connect(ui->pushButton, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton));
    window->connect(ui->pushButton_2, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton2));
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

//void Controller::updateHE(){
//    this->controllerWindow->ui->EnergyBar->setValue(GameWorld::Instance()->protagonist->getEnergy());
//    this->controllerWindow->ui->HealthBar->setValue(GameWorld::Instance()->protagonist->getHealth());
//}

void Controller::move(NextDirection directionOfMovement)
{
    GameWorld::Instance()->moveProtagonist(directionOfMovement);
//    updateHE();
    //We need a way to reference the correct special figure;  Maybe have a map of figures pointer and as the key the index of their tile.
}

void Controller::pushButton()
{
    this->sceneCollection.data()->get()->zoomIn();
}

void Controller::pushButton2()
{
    this->sceneCollection.data()->get()->zoomOut();
}

void Controller::handleCommand(std::string funct, std::vector<std::string> *commands) {
    enum baseCommand result;
    enum moveDirection direction;
    try {
        result = this->commandsProcessor.resolve(funct, this->commandsProcessor.baseMap);
    } catch(std::string query) {
        displayStatus("Unknown command");
    }

    switch(result){
    case vswitch: {
        std::string arg = commands->at(0);
        view_switch(arg);
        break;
    }
    case move: {
        if (commands->size() == 2) {
            std::string xString = commands->at(1);
            std::string yString = commands->at(0);
            int xInt;
            int yInt;
            try {
                xInt = std::stoi(xString);
                yInt = std::stoi(yString);
                ("move: Moving to " + xString + "," + yString);
            } catch (const std::exception &e) {
                displayStatus ("move: A coordinate pair was expected but no correct one was given");
            }
        } else if (commands->size() == 1) {
            try {
                direction = this->commandsProcessor.resolve(commands->at(0), this->commandsProcessor.directionMap);
                ("move: Moving " + commands->at(0));
            } catch(std::string query) {
                displayStatus("move: A direction was expected but no correct one was given");
            }
        } else {
            displayStatus ("move: Incorrect amount of arguments specified");
        }
    }
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
