# include "gameworld.h"
#include "game_config.h"
#include "node.h"
#include <iostream>
#include <unordered_set>


GameWorld::~GameWorld()
{
    //Should clean up memory.
}
GameWorld::GameWorld(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist)
{
    World w= {};
    w.createWorld(pathToMap,nrEnemies,nrHeatlhPacks,1.0);
    setRowsAndColumns(w.getRows(),w.getCols());
    createNodes(w);
    loadEnemies(w);
    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.
}


void GameWorld::loadEnemies(World &w)
{
    std::vector<std::unique_ptr<Enemy>> enemiesList = w.getEnemies();
    std::vector<std::unique_ptr<Tile>> healthPacksList = w.getHealthPacks();
    for(unsigned long i=0; i<enemiesList.size();i++){
        int index =getIndexFromCoordinates(enemiesList[i]->getYPos(),enemiesList[i]->getXPos());
        specialFiguresVector.push_back(std::move(enemiesList[i]));
        nodes[index]->setSpecialFigure_ptr(specialFiguresVector.back());
//        std::cout<<"Enemy: (value, x , y)"<<nodes[index]->getSpecialFigure_ptr()->getValue()<<" , "<<nodes[index]->getSpecialFigure_ptr()->getXPos()<<" , "<<nodes[index]->getSpecialFigure_ptr()->getYPos()<<std::endl;
    }
    for(unsigned long i=0; i<healthPacksList.size();i++){
        int index = getIndexFromCoordinates(healthPacksList[i]->getYPos(),healthPacksList[i]->getXPos());
        specialFiguresVector.push_back(std::move(healthPacksList[i]));
        nodes[index]->setSpecialFigure_ptr(specialFiguresVector.back());
//        std::cout<<"HP: (value, x , y)"<<nodes[index]->getSpecialFigure_ptr()->getValue()<<" , "<<nodes[index]->getSpecialFigure_ptr()->getXPos()<<" , "<<nodes[index]->getSpecialFigure_ptr()->getYPos()<<std::endl;
    }
}

void GameWorld::createNodes(World &w)
{
    std::vector<std::unique_ptr<Tile>> tiles= w.getTiles();
    nodes.reserve(tiles.size());
    for(unsigned long i=0; i<tiles.size();i++){
        nodes.emplace_back(std::make_unique<Node>(i,(1-tiles[i]->getValue()),totalRows,totalColumns));
    }
}




Protagonist*GameWorld::getProtagonist() const
{
    return protagonist.get();
}

const std::vector<std::shared_ptr<Tile> > &GameWorld::getSpecialFiguresVector() const
{
    return specialFiguresVector;
}

const std::vector<std::unique_ptr<Node> > &GameWorld::getNodes() const
{
    return nodes;
}





void GameWorld::Create(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist) //
{
    if(instance != 0)
        return;
    instance = new GameWorld( pathToMap,  nrEnemies,  nrHeatlhPacks,  startingEnergyProtagonist);
}

void GameWorld::Destroy()
{
    delete instance;
    instance = 0;
}

GameWorld *GameWorld::Instance(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist)
{
    GameWorld::Create(pathToMap,  nrEnemies,  nrHeatlhPacks,  startingEnergyProtagonist);
    return instance;
}





void GameWorld::setRowsAndColumns(int newRows, int newColumns)
{
    totalRows=newRows;
    totalColumns=newColumns;
}



int GameWorld::getTotalRows() const
{
    return totalRows;
}

int GameWorld::getTotalColumns() const
{
    return totalColumns;
}

int GameWorld::moveProtagonist(NextDirection direction)
{

    int destinationIndex = getDestinationIndex(direction,protagonist->getYPos(),protagonist->getXPos());
    if(destinationIndex>=0){//checks that character is not moving outside of the map.
        std::cout<<"moving"<<std::endl;
        protagonist->setPos(getCoordinatesFromIndex(destinationIndex).second,getCoordinatesFromIndex(destinationIndex).first);//emits signal that protagonist moved.
        if(specialFiguresVector[destinationIndex]!=nullptr){
            activateSpecialFigure(destinationIndex);
        }
        protagonist->setEnergy(protagonist->getEnergy()-nodes[destinationIndex]->getIncomingCost());
    }
    std::cout<<"END Protagonist (health energy || row column) ("<<protagonist->getHealth()<<","<<protagonist->getEnergy()<<"||"<<protagonist->getYPos()<<","<<protagonist->getXPos()<<")"<<std::endl;
    return (protagonist->getHealth()>0)&&(protagonist->getEnergy()>0)? 0:1;
}

void GameWorld::activateSpecialFigure(int specialFigureIndex){
    protagonist->setHealth(protagonist->getHealth()-nodes[specialFigureIndex]->getSpecialFigure_ptr()->getValue());
    nodes[specialFigureIndex]->getSpecialFigure_ptr()->setValue(0.0);
    if(Enemy* enemyReference =dynamic_cast<Enemy*>(nodes[specialFigureIndex]->getSpecialFigure_ptr().get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
        if(PEnemy* pEnemyReference =dynamic_cast<PEnemy*>(enemyReference)){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
          pEnemyReference->poison();
        }
        else emit enemyReference->dead();
    }
    else {
        emit healthPackedUsed(specialFigureIndex) ;
    }
}



int GameWorld::getDestinationIndex(NextDirection direction, int row, int column){
    int newRow =row,newCol=column;
    switch(direction){
        case UP:
            --newRow;
            break;
        case DOWN:
            ++newRow;
            break;
        case RIGHT:
            ++newCol;
            break;
        case LEFT:
            --newCol;
            break;
    }
    //returns -1 if movement is outside the map.
    return (newRow<totalRows&&column<totalColumns)?getIndexFromCoordinates(newRow,newCol):-1;
}

void GameWorld::testing()
{
     std::cout<<"Testing "<<std::endl;
    if(PEnemy* enemyReference =dynamic_cast<PEnemy*>(getSpecialFiguresVector()[1].get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
        std::cout<<"Testing enemy"<<std::endl;
        connect(enemyReference,SIGNAL(poisonLevelUpdated(int)),this,SLOT(poisonousAttack(int)));
        enemyReference->poison();
    }
}

void GameWorld::poisonousAttack(int poisonValue)
{
    PEnemy* enemyReference =dynamic_cast<PEnemy*>(sender());
    std::unordered_set<int> poisonindexes;
    int originRow =enemyReference->getYPos(), originCol=enemyReference->getXPos();
    int currentPoisonLevel = poisonLevel;
    while(currentPoisonLevel>0){
      std::vector<int> indexes;
//      indexes.emplace_back(getDestinationIndex(UP,originRow,originCol));
//      indexes.emplace_back(getDestinationIndex(DOWN,originRow,originCol));
//      indexes.emplace_back(getDestinationIndex(LEFT,originRow,originCol));
//      indexes.emplace_back(getDestinationIndex(RIGHT,originRow,originCol));
//      for(auto i :indexes){

//          poisonindexes.emplace(getDestinationIndex(UP,originRow,originCol));
//          poisonindexes.emplace(getDestinationIndex(DOWN,originRow,originCol));
//          poisonindexes.emplace(getDestinationIndex(LEFT,originRow,originCol));
//          poisonindexes.emplace(getDestinationIndex(RIGHT,originRow,originCol));
//      }
//      poisonindexes.emplace(getDestinationIndex(UP,originRow+currentPoisonLevel,originCol+currentPoisonLevel));
//      poisonindexes.emplace(getDestinationIndex(DOWN,originRow+currentPoisonLevel,originCol+currentPoisonLevel));
//      poisonindexes.emplace(getDestinationIndex(LEFT,originRow+currentPoisonLevel,originCol+currentPoisonLevel));
//      poisonindexes.emplace(getDestinationIndex(RIGHT,originRow+currentPoisonLevel,originCol+currentPoisonLevel));
//      currentPoisonLevel--;
//    }

    poisonLevel++;

    std::cout<<"PENEMY "<<enemyReference->getPoisonLevel()<<"----"<<poisonValue<<std::endl;
}


void GameWorld::initializeProtagonist(float startingEnergy)
{
    while(protagonist==nullptr){
        int index = rand()%(totalRows*totalColumns);
        if(!(nodes[index]->getSpecialFigure_ptr()==nullptr)&& nodes[index]->getIncomingCost()<10){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            std::pair<int,int> coordinatesProtagonist= getCoordinatesFromIndex(index);
            protagonist->setYPos(coordinatesProtagonist.first);
            protagonist->setXPos(coordinatesProtagonist.second);
            std::cout<<"Protagonist("<<protagonist->getYPos()<<","<<protagonist->getXPos()<<")created at Index:"<<index<<std::endl;
        }
    }
}


























