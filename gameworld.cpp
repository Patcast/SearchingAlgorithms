# include "gameworld.h"
#include "game_config.h"
#include "node.h"
#include "xenemy.h"
#include <iostream>


GameWorld *GameWorld::Instance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr)
    {
        instance = new GameWorld();
    }
    return instance;
}


void GameWorld::setGameMap(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist)
{
    World w= {};
    w.createWorld(pathToMap,nrEnemies,nrHeatlhPacks,0.5);
    setRowsAndColumns(w.getRows(),w.getCols());
    createNodes(w);
    loadEnemies(w);
    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.
    imagePath=pathToMap;
}


void GameWorld::loadEnemies(World &w)
{
    std::vector<std::unique_ptr<Enemy>> enemiesList = w.getEnemies();
    std::vector<std::unique_ptr<Tile>> healthPacksList = w.getHealthPacks();
    for(unsigned long i=0; i<enemiesList.size();i++){
        int index =getIndexFromCoordinates(enemiesList[i]->getYPos(),enemiesList[i]->getXPos());
        specialFiguresVector.push_back(std::move(enemiesList[i]));
        nodes[index]->setSpecialFigure_ptr(specialFiguresVector.back());
        if(PEnemy* pEnemyReference =dynamic_cast<PEnemy*>(nodes[index]->getSpecialFigure_ptr().get())){
            connect(pEnemyReference,SIGNAL(poisonLevelUpdated(int)),this,SLOT(poisonousAttack(int)));
        }
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

const QString &GameWorld::getImagePath() const
{
    return imagePath;
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
        if(nodes[destinationIndex]->getSpecialFigure_ptr()!=nullptr){
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
        if(PEnemy* pEnemyReference =dynamic_cast<PEnemy*>(nodes[specialFigureIndex]->getSpecialFigure_ptr().get())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
            pEnemyReference->poison();
        }
        else if(XEnemy* xEnemyReference =dynamic_cast<XEnemy*>(nodes[specialFigureIndex]->getSpecialFigure_ptr().get())){
            xEnemyReference->generateExplosions();
        }
        else emit xEnemyReference->dead();
    }
    else {
        emit healthPackedUsed(specialFigureIndex) ;
    }
}
void GameWorld::poisonousAttack(int poisonValue)
{
//    if(poisonOfAttack!=0){}
//    int numOfAttack = poisonOfAttack%10-poisonValue%10;
    if(PEnemy* pEnemyReference =dynamic_cast<PEnemy*>(sender())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
        std::vector<int> infectedTiles=getNeighboursTileIndex(pEnemyReference->getYPos(),pEnemyReference->getXPos());

        while(!infectedTiles.empty()){
            if((protagonist->getXPos()==pEnemyReference->getXPos())&&(protagonist->getYPos()==pEnemyReference->getYPos()))protagonist->setHealth(protagonist->getHealth()-pEnemyReference->getValue());
            emit poisonTileInScene(infectedTiles.back(),poisonValue);
            infectedTiles.pop_back();
        }
    }
}

void GameWorld::explosiveAttack(int explosiveValue,int row,int col)
{
    if(XEnemy* xEnemyReference =dynamic_cast<XEnemy*>(sender())){//check if it is an enemy. Also, enemyReference is a reference, so specialfigures[i] is only owner of pointer
        if((protagonist->getXPos()==xEnemyReference->getXPos())&&(protagonist->getYPos()==xEnemyReference->getYPos()))protagonist->setHealth(protagonist->getHealth()-xEnemyReference->getValue());
        emit explosionTileInScene(getIndexFromCoordinates(row,col),explosiveValue);
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
//        nodes[155]->setSpecialFigure_ptr(std::make_shared<Tile>(1,2,0.2));
//        nodes[185]->setSpecialFigure_ptr(std::make_shared<Tile>(1,2,0.2));
//        nodes[215]->setSpecialFigure_ptr(std::make_shared<Tile>(1,2,0.2));
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


























