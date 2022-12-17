#include "enemyview.h"

void enemyView::place(int x, int y, int size)
{
    StepSize = size;
    setPixmap(QPixmap(":/images/Goomba.png").scaled(StepSize,StepSize));
    xPos = x*StepSize;
    yPos = y*StepSize;
    setPos(xPos,yPos);
    setZValue(0.85);
}

void enemyView::defeated(int x, int y)
{
    setPixmap(QPixmap(":/images/deadGoomba.png").scaled(StepSize,StepSize));
    setPos(x*StepSize,y*StepSize);
    setZValue(0.9);
}
