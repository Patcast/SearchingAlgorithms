#ifndef XENEMY_H
#define XENEMY_H
#include "world.h"
#define EXPLOSION_RATE 1
#define MAX_EXPLODED_TILES 49


class XEnemy : public Enemy
{
    Q_OBJECT
public:
    XEnemy(int xPosition, int yPosition, float strength);
    ~XEnemy() override = default;

public slots:
    void generateExplosions();

signals:
    void explode(int value, int row, int col);
private:
    int explosionIndex {0};
    const int tileOffSets3 [49][2] = {{-3,-3},{-3,-2},{-3,-1},{-3,0},{-3,1},{-3,2},{-3,3},{-2,-3},{-2,-2},{-2,-1},{-2,0},{-2,1},{-2,2},{-2,3},{-1,-3},{-1,-2},{-1,-1},{-1,0},{-1,1},{-1,2},{-1,3},{0,-3},{0,-2},{0,-1},{0,0},{0,1},{0,2},{0,3},{1,-3},{1,-2},{1,-1},{1,0},{1,1},{1,2},{1,3},{2,-3},{2,-2},{2,-1},{2,0},{2,1},{2,2},{2,3},{3,-3},{3,-2},{3,-1},{3,0},{3,1},{3,2},{3,3}};
};


#endif // XENEMY_H
