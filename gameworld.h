#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "world.h"
#define HEALTH_PACK 0;
#define ENEMY 1;
class GameWorld

{
public:
    GameWorld()=default;
    void generateWorld(QString pathToMap);
    int getFlatIndex(const int x, const int y){return rows*y +x;};
    void setRowsAndColumns(int newRows, int newColumns);

private:
    Protagonist protagonist;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::optional<std::unique_ptr<Tile>>> specialFigures;
    int rows,columns;
};

#endif // GAMEWORLD_H
