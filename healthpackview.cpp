#include "healthpackview.h"



void healthPackView::place(int x, int y, int size)
{
    StepSize = size;
    setPixmap(QPixmap(":/images/HealthPack.jpg").scaled(StepSize,StepSize));
    xPos = x*StepSize;
    yPos = y*StepSize;
    setPos(xPos,yPos);
    setZValue(0.85);
}

void healthPackView::defeated(int x, int y, int size)
{
    setPixmap(QPixmap(":/images/emptyHealthPack.jpg").scaled(size,size));
    setPos(x*size,y*size);
    setZValue(0.90);
}
