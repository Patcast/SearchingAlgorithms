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

void healthPackView::defeated()
{
    setPixmap(QPixmap(":/images/HealthPackEmpty.jpg").scaled(StepSize,StepSize));
    setPos(xPos,yPos);
}
