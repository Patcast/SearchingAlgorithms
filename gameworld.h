#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "tilecomposition.h"
#include "world.h"

class GameWorld

{
public:
    GameWorld()=default;
    void setVectorOfTilesComposition(std::unique_ptr<TileComposition> newVectorOfTilesComposition);
    void setProtagonist(const Protagonist &newProtagonist);
    std::unique_ptr<TileComposition> generateWorld(QString pathToMap);

private:
    std::vector<std::unique_ptr<TileComposition>> tilesCompositionList;
    Protagonist protagonist;

};

#endif // GAMEWORLD_H
