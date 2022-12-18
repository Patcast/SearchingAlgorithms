#include "controller.h"
#include "qtimer.h"
#include "ui_mainwindow.h"
#include <iostream>
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

    window->connect(ui->lineEdit, &QLineEdit::returnPressed, this, qOverload<>(&Controller::handleCommand));
    window->connect(ui->pushButton, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton));
    window->connect(ui->pushButton, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton));
    window->connect(ui->pushButton_2, &QPushButton::pressed, this, qOverload<>(&Controller::pushButton2));
    window->connect( GameWorld::Instance()->getProtagonist(), &Protagonist::posChanged, this,&Controller::posChanged);
    window->connect(this->controllerWindow, &MainWindow::arrowPress, this,qOverload<moveDirection>(&Controller::move));
    window->connect(movementTimer, &QTimer::timeout, this, qOverload<>(&Controller::moveAutomatically));

  
    window->connect(ui->HeuristicsInput, &QSpinBox::valueChanged, this, &Controller::setHeuristic);
    window->connect(ui->SpeedInput, &QSpinBox::valueChanged, this, &Controller::setAnimationSpeed);
    window->connect(GameWorld::Instance(), &GameWorld::poisonTileInScene, this, &Controller::poisonousTile);
    window->connect(GameWorld::Instance(), &GameWorld::explosionTileInScene, this, &Controller::explosiveTile);
    aStarPtr=std::make_unique<AStar>( GameWorld::Instance()->getTotalRows(), GameWorld::Instance()->totalColumns);

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

void Controller::autoplay()
{

}

void Controller::move(int row, int col)
{
    std::cout<<row<<"//"<<col<<std::endl;

    std::cout<<GameWorld::Instance()->getIndexFromCoordinates(row,col)<<std::endl;
    if(GameWorld::Instance()->getIndexFromCoordinates(row,col)<GameWorld::Instance()->totalColumns*GameWorld::Instance()->totalRows&&GameWorld::Instance()->getIndexFromCoordinates(row,col)>=0){
        if(GameWorld::Instance()->getNodes()[GameWorld::Instance()->getIndexFromCoordinates(row,col)]->getIncomingCost()<10000){
            listOfIndexes= aStarPtr->getShortestPath(GameWorld::Instance()->getIndexFromCoordinates(GameWorld::Instance()->getProtagonist()->getYPos(),GameWorld::Instance()->getProtagonist()->getXPos()),GameWorld::Instance()->getIndexFromCoordinates(row,col));
            // the tiles are highlighted
            for (int ind: listOfIndexes){
                std::pair<int,int> coords = GameWorld::Instance()->getCoordinatesFromIndex(ind);

                this->highlightPath(std::make_pair(coords.second, coords.first));
            }
            currentNodeIndex=listOfIndexes.size()-2;
            this->moveAutomatically();
            movementTimer->start(timerSpeed);

        }
        else  std::cout<<"index of a wall"<<std::endl;

    }
    else std::cout<<"index out of bounds "<<std::endl;




}

void Controller::moveAutomatically() {
    GameWorld::Instance()->moveAdjacent(listOfIndexes[currentNodeIndex]);
    currentNodeIndex--;
    if(currentNodeIndex >=listOfIndexes.size()){
        movementTimer->stop();
    }
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
                this->setAnimationSpeed(speedAmount);
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

    float inputHeuristic= (float)heuristic/60;
    aStarPtr->setHeuristicFactor(inputHeuristic);

    this->controllerWindow->ui->HeuristicsInput->setValue(heuristic);
}

void Controller::setAnimationSpeed(int speed) {
    if (speed < 0) {
        speed = 0;
    } else if (speed > 100) {
        speed = 100;
    }
    timerSpeed = 1000-(speed*10);
    this->controllerWindow->ui->SpeedInput->setValue(speed);
}

void Controller::highlightPath(std::pair<int,int> coord) {
    for (auto &scene : this->sceneCollection) {
        scene->drawHighlight(coord.first, coord.second);
    }
    highlightTiles.push_back(coord);

    QTimer::singleShot(10000, this, &Controller::removeHighlightPath);
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
