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

//    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.

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

int GameWorld::getTotalRows() const
{
    return totalRows;
}

int GameWorld::getTotalColumns() const
{
    return totalColumns;
}





const std::vector<std::unique_ptr<Tile> > &GameWorld::getTiles() const
{
    return tiles;
}



void GameWorld::initializeProtagonist(float startingEnergy)
{
    /*
    while(protagonist==nullptr){
        int x = rand()%(totalRows);
        int y = rand()%(totalRows);
        std::cout<<"(X,Y): "<<x<<"x"<<y<<std::endl;
        if(!specialFigures[getIndexFromCoordinates(x,y)].has_value()){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            protagonist->setXPos(x);
            protagonist->setYPos(y);
            std::cout<<"Protagonist created"<<std::endl;
        }
    }
    */
    bool free = true;
    while(protagonist==nullptr){
        free = true;
        int x = rand()%(totalRows);
        int y = rand()%(totalRows);
        std::cout<<"(X,Y): "<<x<<"x"<<y<<std::endl;
        for(std::unique_ptr<Enemy> &t:enemies){
            if((t->getXPos()==x)&&(t->getYPos()==y)){
                std::cout<<"same Pos"<<std::endl;
                free = false;
                break;
            }
        }
        for(std::unique_ptr<Tile> &t:healthPacks){
            if((t->getXPos()==x)&&(t->getYPos()==y)){
                std::cout<<"same Pos"<<std::endl;
                free = false;
                break;
            }
        }
        if(free){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            protagonist->setXPos(x);
            protagonist->setYPos(y);
            }
        }

}


























