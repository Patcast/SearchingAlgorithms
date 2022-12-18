#ifndef XENEMY_H
#define XENEMY_H
#include "world.h"
#define EXPLOSION_RATE 1
#define MAX_EXPLODED_TILES 8


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
    const int explosionOffSets [MAX_EXPLODED_TILES][2] = {{-1, 0},{-1,1}, {0, 1},{1,1}, {1, 0},{1,-1},{-1,-1}, {0, -1}};
};


#endif // XENEMY_H
