#include "controller.h"
#include "qtimer.h"
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
    movementTimer = new QTimer();
    aStarController = std::make_unique<AStarController>(AStarController());

    GameWorld *gameWorld = GameWorld::Instance();
    window->connect(ui->lineEdit, &QLineEdit::returnPressed, this, qOverload<>(&Controller::handleCommand));
    window->connect(ui->pushButton, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton));
    window->connect(ui->pushButton, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton));
    window->connect(ui->pushButton_2, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton2));
    window->connect(gameWorld->getProtagonist(), &Protagonist::posChanged, this,&Controller::posChanged);
    window->connect(this->controllerWindow, &MainWindow::arrowPress, this,qOverload<moveDirection>(&Controller::move));
    window->connect(movementTimer, &QTimer::timeout, this, qOverload<>(&Controller::moveAutomatically));
    window->connect(ui->HeuristicsInput, &QSpinBox::valueChanged, this, &Controller::setHeuristic);
    //window->connect(ui->SpeedInput, &QSpinBox::valueChanged, this, &Controller::setAnimationSpeed);

    window->connect(gameWorld, &GameWorld::poisonTileInScene, this, &Controller::poisonousTile);
    window->connect(gameWorld, &GameWorld::explosionTileInScene, this, &Controller::explosiveTile);
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

void Controller::posChanged(int x, int y) {
    for (auto &scene : this->sceneCollection) {
        scene->drawMovement(x, y);
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

void Controller::move(moveDirection directionOfMovement)
{
    GameWorld::Instance()->moveProtagonist(directionOfMovement);
}

void Controller::move(int x, int y)
{
    GameWorld *gameWorld = GameWorld::Instance();

    int start = gameWorld->getIndexFromCoordinates(gameWorld->getProtagonist()->getYPos(),gameWorld->getProtagonist()->getXPos());
    int goal = gameWorld->getIndexFromCoordinates(y,x);

    // aStarController.runAStar(start, goal, ###)
    // this vector should contain all indexes that lead to the goal
    // starting at the goal, and moving to the start
    //this->listOfIndexes.push_back()
    this->moveAutomatically();
}

void Controller::moveAutomatically() {
    int destination = listOfIndexes.at(0);
    GameWorld::Instance()->moveAdjacent(destination);

    listOfIndexes.pop_back();
    movementTimer->start(1000);
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
    baseCommand result;
    moveDirection direction;

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
    case pmove: {
        if (commands->size() == 2) {
            std::string xString = commands->at(1);
            std::string yString = commands->at(0);
            int xInt;
            int yInt;
            try {
                xInt = std::stoi(xString);
                yInt = std::stoi(yString);
                ("move: Moving to " + xString + "," + yString);
                this->move(xInt, yInt);
                break;
            } catch (const std::exception &e) {
                displayStatus ("move: A coordinate pair was expected but no correct one was given");
            }
        } else if (commands->size() == 1) {
            try {
                direction = this->commandsProcessor.resolve(commands->at(0), this->commandsProcessor.directionMap);
                ("move: Moving " + commands->at(0));
                this->move(direction);
            } catch(std::string query) {
                displayStatus("move: A direction was expected but no correct one was given");
            }
        } else {
            displayStatus ("move: Incorrect amount of arguments specified");
        }        
        break;
    }
    case heuristic: {
        if (commands->size() == 1) {
            std::string heuristicAmountString = commands->at(0);
            int heuristicAmount;
            try {
                heuristicAmount = std::stoi(heuristicAmountString);
                ("Setting heuristic to " + heuristicAmountString);
                this->setHeuristic(heuristicAmount);
            } catch(std::string query) {
                displayStatus("heuristic: An amount was expected, but none given");
            }
        } else {
            displayStatus("heuristic: An amount was expected, but none given");
        }        
        break;
    }
    case speed: {
        if (commands->size() == 1) {
            std::string speedAmountString = commands->at(0);
            int speedAmount;
            try {
                speedAmount = std::stoi(speedAmountString);
                ("Setting animation speed to " + speedAmountString);
                this->setHeuristic(speedAmount);
            } catch(std::string query) {
                displayStatus("speed: An amount was expected, but none given");
            }
        } else {
            displayStatus("speed: An amount was expected, but none given");
        }        
        break;
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

void Controller::setHeuristic(int heuristic) {
    if (heuristic < 0) {
        heuristic = 0;
    } else if (heuristic > 100) {
        heuristic = 100;
    }
    float inputHeuristic= heuristic/100;
    aStarController->setHeuristic(inputHeuristic);

    this->controllerWindow->ui->HeuristicsInput->setValue(heuristic);
}

void Controller::setAnimationSpeed(int speed) {
    if (speed < 0) {
        speed = 0;
    } else if (speed > 100) {
        speed = 100;
    }
    timerSpeed = speed*10;
    this->controllerWindow->ui->SpeedInput->setValue(speed);
}

void Controller::highlightPath(std::vector<std::pair<int,int>> coords) {
    for (auto &coord : coords) {
        for (auto &scene : this->sceneCollection) {
            scene->drawHighlight(coord.first, coord.second);
        }
        highlightTiles.push_back(coord);
    }

    QTimer::singleShot(1000, this, &Controller::removeHighlightPath);
}

void Controller::removeHighlightPath() {
    std::pair<int,int> coord = highlightTiles.at(highlightTiles.size() - 1);
    highlightTiles.pop_back();

    for (auto &scene : this->sceneCollection) {
        scene->removeHighlight(coord.first, coord.second);
    }
}

void Controller::poisonousTile(std::pair<int,int> coord, int poisonValue){
    for (auto &scene : this->sceneCollection) {
        scene->drawPoisonous(coord.first, coord.second);
    }
    poisonousTiles.push_back(coord);
    QTimer::singleShot(2000,this,&Controller::removePoisonTile);
}

void Controller::explosiveTile(std::pair<int,int> coord, int explosiveValue){
    for (auto &scene : this->sceneCollection) {
        scene->drawExplosive(coord.first, coord.second);
    }
}

void Controller::removePoisonTile(){
    std::pair<int,int> coord = poisonousTiles.at(poisonousTiles.size() - 1);
    poisonousTiles.pop_back();

    for (auto &scene : this->sceneCollection) {
        scene->removePoisonous(coord.first, coord.second);
    }
}
