# include "gameworld.h"
#include <iostream>
#include <cstdlib>

// TODO:
// No need to call emplace_back, I belive that no copies are generated when moving the enemies.
// Delete TIle Composition
// Make gameworld an instance and also the protagonist.
// Check random method to initialize protagonist
// Can I use variant for the special characters.




void GameWorld::generateWorld(QString pathToMap,int nrEnemies,int nrHeatlhPacks ,float startingEnergyProtagonist)
{
    World w= {};
    w.createWorld(pathToMap,nrEnemies,nrHeatlhPacks);
    setRowsAndColumns(w.getRows(),w.getCols());
    tiles= w.getTiles();
    std::vector<std::unique_ptr<Enemy>> enemies = w.getEnemies();
    std::vector<std::unique_ptr<Tile>> healthPacks = w.getHealthPacks();
    specialFigures.resize(tiles.size());
    for(unsigned long i=0; i<enemies.size();i++){
        specialFigures[getFlatIndex(enemies[i]->getXPos(),enemies[i]->getYPos())]= (std::move(enemies[i]));
    }
    for(unsigned long i=0; i<healthPacks.size();i++){
        specialFigures[getFlatIndex(healthPacks[i]->getXPos(),healthPacks[i]->getYPos())]= (std::move(healthPacks[i]));
    }
    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.
    //Make the protagonist
    std::cout<<"tilesCompositionList Size: "<<specialFigures.size()<<std::endl;
}




void GameWorld::setRowsAndColumns(int newRows, int newColumns)
{
    rows=newRows;
    columns=newColumns;
}

void GameWorld::initializeProtagonist(float startingEnergy)
{
    while(protagonist==nullptr){
        int x = rand()%(columns);
        int y = rand()%(rows);
        std::cout<<"(X,Y): "<<x<<"x"<<y<<std::endl;
        if(!specialFigures[getFlatIndex(x,y)].has_value()){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            protagonist->setXPos(x);
            protagonist->setYPos(y);
            std::cout<<"Protagonist created"<<std::endl;
        }
    }
}
















