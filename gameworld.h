#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "node.h"
#include "world.h"
#include "game_config.h"
#include <QObject>




class GameWorld : public QObject
{
    Q_OBJECT
public:

    ~GameWorld();// Ue to free memory of all collections.
    static void Create(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist);
    static void Destroy();
    static GameWorld * Instance(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist);



    int getTotalRows() const;
    int getTotalColumns() const;
    int getIndexFromCoordinates(const int row_index, const int col_index){return totalColumns*row_index +col_index;};
    //return: <row,column>
    std::pair<int, int> getCoordinatesFromIndex(int index){return (std::make_pair<int,int>( index/totalColumns,index%totalColumns));};
    //return: 1 if game is over or 0 is game continues
    int moveProtagonist(NextDirection direction);
    void activateSpecialFigure(int specialFigureIndex);
    int getDestinationIndex(NextDirection direction, int row, int column);
    const std::vector<std::unique_ptr<Node> > &getNodes() const;
    const std::vector<std::shared_ptr<Tile> > &getSpecialFiguresVector() const;
    Protagonist*getProtagonist() const;
    // TESTING
    void testing();

signals:
    void healthPackedUsed(int specialFigureIndex);




private:
    GameWorld(QString pathToMap, unsigned long nrEnemies, unsigned long nrHeatlhPacks, float startingEnergyProtagonist);
    static GameWorld* instance;
    void initializeProtagonist(float startingEnergy);
    void setRowsAndColumns(int newRows, int newColumns);
    void loadEnemies(World &world);
    void createNodes(World &w);
    std::vector<int> getNeighboursTileIndex(int row, int col);
    std::unique_ptr<Protagonist> protagonist {nullptr};
    std::vector<std::shared_ptr<Tile>> specialFiguresVector;
    std::vector<std::unique_ptr<Node>> nodes;


    int totalRows,totalColumns;
    bool gameOver{false};



};

#endif // GAMEWORLD_H
