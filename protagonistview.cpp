#include "protagonistview.h"



void ProtagonistView::place(int x, int y, int size)
{
    StepSize = size;
    setPixmap(QPixmap(":/images/mario03.png").scaled(StepSize,StepSize));
    xPos = x*StepSize;
    yPos = y*StepSize;
    setPos(xPos,yPos);
    setZValue(1);
    setFlag(QGraphicsItem::ItemIsFocusable);
    focusItem();
}

void ProtagonistView::defeated()
{
    setPixmap(QPixmap(":/images/marioDead.jpg").scaled(StepSize,StepSize));
    setPos(xPos,yPos);
}

void ProtagonistView::move(int x, int y)
{
    xPos = x * StepSize;
    yPos = y * StepSize;
    setPos(xPos,yPos);
}

void ProtagonistView::attack(int x, int y)
{
    xPos = x * StepSize;
    yPos = y * StepSize;
    setPixmap(QPixmap(":/images/marioDead.jpg").scaled(StepSize,StepSize));
    setPos(xPos,yPos);
}
