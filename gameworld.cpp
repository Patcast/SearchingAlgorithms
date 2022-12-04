# include "gameworld.h"
#include <iostream>

//TODO:
//No need to call emplace_back, I belive that no copies are generated when moving the enemies.
//Delete TIle Composition




void GameWorld::generateWorld( QString pathToMap)
{
    World w= {};
    w.createWorld(pathToMap,20,20);
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
    //Make the protagonist
    std::cout<<"tilesCompositionList Size: "<<specialFigures.size()<<std::endl;
}




void GameWorld::setRowsAndColumns(int newRows, int newColumns)
{
    rows=newRows;
    columns=newColumns;
}
















