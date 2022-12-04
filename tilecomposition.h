#ifndef TILECOMPOSITION_H
#define TILECOMPOSITION_H
#include "world.h"

class TileComposition
{
public:
    TileComposition(std::unique_ptr<Tile> normalTile);



    void setSpecialTile(std::unique_ptr<Tile> newSpecialTile);

private:
    std::unique_ptr<Tile> normalTile;
    std::unique_ptr<Tile>  specialTile = nullptr;

};

#endif // TILECOMPOSITION_H
