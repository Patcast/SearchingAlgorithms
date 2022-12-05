#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "node.h"
#include "world.h"
#define MAX_NEIGHBORS 4
#define NODE_DIMENSION 2
class GameWorld        

{
public:
    GameWorld()=default;
    void generateWorld(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist);
    std::shared_ptr<Node> getNode(int index);

    //Testing methods
    void makeSubsetOfTiles(int rows, int columns);
    void printSubSetOftiles();
    void printTiles(int nrOfTiles);


private:
    void initializeProtagonist(float startingEnergy);
    int getIndexFromCoordinates(const int row_index, const int col_index){return totalColumns*row_index +col_index;};
    void setRowsAndColumns(int newRows, int newColumns);
    std::vector<int> getNeighbourTileIndex(int row, int col);

    std::unique_ptr<Protagonist> protagonist {nullptr};
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::optional<std::unique_ptr<Tile>>> specialFigures;
    int totalRows,totalColumns;
    const int tileOffSets [MAX_NEIGHBORS][NODE_DIMENSION] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    // TESTING

    std::vector<std::unique_ptr<Tile>> subSetOfTiles;

};

#endif // GAMEWORLD_H
