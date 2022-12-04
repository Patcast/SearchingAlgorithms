#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "world.h"
class GameWorld

{
public:
    GameWorld()=default;
    void generateWorld(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist);
    int getFlatIndex(const int x, const int y){return rows*y +x;};
    void setRowsAndColumns(int newRows, int newColumns);
    void initializeProtagonist(float startingEnergy);

private:

    std::unique_ptr<Protagonist> protagonist {nullptr};
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::optional<std::unique_ptr<Tile>>> specialFigures;
    int rows,columns;
};

#endif // GAMEWORLD_H
