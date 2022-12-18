#include "penemyview.h"

void PEnemyView::place(int x, int y, int size)
{
    StepSize = size;
    setPixmap(QPixmap(":/images/PEnemy.png").scaled(StepSize,StepSize));
    xPos = x*StepSize;
    yPos = y*StepSize;
    setPos(xPos,yPos);
    setZValue(0.85);
}

void PEnemyView::defeated(int x, int y, int size)
{
    setPixmap(QPixmap(":/images/toadDead.png").scaled(size,size));
    setPos(x*size,y*size);
    setZValue(0.95);
}
