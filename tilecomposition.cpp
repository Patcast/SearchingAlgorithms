#include "tilecomposition.h"


TileComposition::TileComposition(std::unique_ptr<Tile>normalTileInput):
    normalTile{std::move(normalTileInput)}
{

}

void TileComposition::setSpecialTile(std::unique_ptr<Tile> newSpecialTile)
{
    specialTile = std::move(newSpecialTile);
}
