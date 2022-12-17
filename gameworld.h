#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "node.h"
#include "world.h"
#include <QObject>
#include"game_config.h"




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

    Protagonist*getProtagonist() const;

    const std::vector<std::shared_ptr<Tile> > &getSpecialFiguresVector() const;
    const std::vector<std::unique_ptr<Node> > &getNodes() const;

    int moveProtagonist(NextDirection direction);

    void testing();
    void attack();
signals:
    void healthPackedUsed(int specialFigureIndex);
private slots:
    void poisonousEffect();
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



    void activateSpecialFigure(int specialFigureIndex);
    int getDestinationIndex(NextDirection direction, int row, int column);
};

#endif // GAMEWORLD_H
