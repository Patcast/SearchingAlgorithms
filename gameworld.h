#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "world.h"
#include <QVariant>

#define MAX_NEIGHBORS 4
#define NODE_DIMENSION 2
class GameWorld

{
public:
    std::unique_ptr<Protagonist> protagonist {nullptr};
    std::vector<std::optional<std::unique_ptr<Tile>>> specialFigures;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;

    ~GameWorld();// Ue to free memory of all collections.
    static void Create(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist);
    static void Destroy();
    static GameWorld * Instance(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist);


    //Testing methods
    void makeSubsetOfTiles(int rows, int columns);
    void printSubSetOftiles();
    void printTiles(int nrOfTiles);


    const std::vector<std::unique_ptr<Tile> > &getTiles() const;

    int getTotalRows() const;
    int getTotalColumns() const;
    int getIndexFromCoordinates(const int row_index, const int col_index){return totalColumns*row_index +col_index;};
    std::pair<int, int> getCoordinatesFromIndex(int index){return (std::make_pair<int,int>( index/totalColumns,index%totalColumns));};

private:
    GameWorld(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist);
    static GameWorld* instance;
    void initializeProtagonist(float startingEnergy);
    void setRowsAndColumns(int newRows, int newColumns);


//    std::unique_ptr<Protagonist> protagonist {nullptr};
    std::vector<std::unique_ptr<Tile>> tiles;
//    std::vector<std::optional<std::unique_ptr<Tile>>> specialFigures;
    int totalRows,totalColumns;



};

#endif // GAMEWORLD_H
