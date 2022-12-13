# include "gameworld.h"
#include <iostream>
#include <cstdlib>



// TODO:
// No need to call emplace_back, I belive that no copies are generated when moving the enemies.
// Delete TIle Composition
// Make gameworld an instance and also the protagonist.
// Check random method to initialize protagonist
// Can I use variant for the special characters.
// Check for valid index, can be improved.
// Double check that enemies and hp are placed correctly.
// Maybe I can define my own hashing to use the un_ordered_set without an auxiliary colletion of indexes.





GameWorld::~GameWorld()
{

}
GameWorld::GameWorld(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist)
{
    World w= {};
    w.createWorld(pathToMap,nrEnemies,nrHeatlhPacks);
    setRowsAndColumns(w.getRows(),w.getCols());
    tiles= w.getTiles();
    std::vector<std::unique_ptr<Enemy>> enemiesList = w.getEnemies();
    std::vector<std::unique_ptr<Tile>> healthPacksList = w.getHealthPacks();
    specialFigures.resize(tiles.size());

    for(unsigned long i=0; i<enemiesList.size();i++){
        specialFigures[getIndexFromCoordinates(enemiesList[i]->getYPos(),enemiesList[i]->getXPos())]= (std::move(enemiesList[i]));
    }
    for(unsigned long i=0; i<healthPacksList.size();i++){
        specialFigures[getIndexFromCoordinates(healthPacksList[i]->getYPos(),healthPacksList[i]->getXPos())] = (std::move(healthPacksList[i]));
    }

    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.

}


void GameWorld::Create(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist) //
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

GameWorld *GameWorld::Instance(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist)
{
    GameWorld::Create(pathToMap,  nrEnemies,  nrHeatlhPacks,  startingEnergyProtagonist);
    return instance;
}





void GameWorld::setRowsAndColumns(int newRows, int newColumns)
{
    totalRows=newRows;
    totalColumns=newColumns;
}

const std::vector<std::optional<std::unique_ptr<Tile> > > &GameWorld::getSpecialFigures() const
{
    return specialFigures;
}

int GameWorld::getTotalRows() const
{
    return totalRows;
}

int GameWorld::getTotalColumns() const
{
    return totalColumns;
}

int GameWorld::moveProtagonist(NextDirection direction) //if return value is 1 -> GameOver
{
    int destinationIndex = getDestinationIndex(direction,protagonist->getYPos(),protagonist->getXPos());
    if(destinationIndex>=0){//checks that character is not moving outside of the map.
        std::cout<<"moving"<<std::endl;

        protagonist->setPos(getCoordinatesFromIndex(destinationIndex).second,getCoordinatesFromIndex(destinationIndex).first);//emits signal that protagonist moved.
        if(specialFigures[destinationIndex].has_value()){
            protagonist->setHealth(protagonist->getHealth()-getSpecialFigures()[destinationIndex]->get()->getValue());
        }
        protagonist->setEnergy(protagonist->getEnergy()-getTiles()[destinationIndex]->getValue());
    }
    std::cout<<"END Protagonist (health energy row column) ("<<protagonist->getHealth()<<","<<protagonist->getEnergy()<<","<<protagonist->getYPos()<<","<<protagonist->getXPos()<<")"<<std::endl;
     return (protagonist->getHealth()>0)&&(protagonist->getEnergy()>0)?1:0;
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
    moveProtagonist(UP);
}





const std::vector<std::unique_ptr<Tile> > &GameWorld::getTiles() const
{
    return tiles;
}



void GameWorld::initializeProtagonist(float startingEnergy)
{
    while(protagonist==nullptr){
        int index = rand()%(totalRows*totalColumns);
        if(!specialFigures[index].has_value()&& tiles[index]->getValue()<100){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            std::pair<int,int> coordinatesProtagonist= getCoordinatesFromIndex(index);
            protagonist->setYPos(coordinatesProtagonist.first);
            protagonist->setXPos(coordinatesProtagonist.second);
            std::cout<<"Protagonist("<<protagonist->getYPos()<<","<<protagonist->getXPos()<<")created at Index:"<<index<<std::endl;
        }
    }
}


























