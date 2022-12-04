# include "gameworld.h"
#include <iostream>


std::unique_ptr<TileComposition> GameWorld::generateWorld( QString pathToMap)
{
    World w= {};
    w.createWorld(pathToMap,20,20);
    std::cout<<"World Size: "<<w.getRows()<<"x"<<w.getRows()<<std::endl;

    std::vector<std::unique_ptr<Tile>> tiles= w.getTiles();
    std::vector<std::unique_ptr<Enemy>> enemies = w.getEnemies();

    for(unsigned long i=0; i<tiles.size();i++){

        tilesCompositionList.push_back(std::make_unique<TileComposition> (std::move(tiles[i])));
    }

    std::cout<<"tilesCompositionList Size: "<<tilesCompositionList.size()<<std::endl;

    return NULL;
}



//void GameWorld::setProtagonist(const Protagonist &newProtagonist)
//{
//    protagonist = newProtagonist;
//}
