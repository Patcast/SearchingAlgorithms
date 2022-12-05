#include "astarcontroller.h"


AStarController::AStarController()
{

    g_ptr= GameWorld::Instance();
    g_ptr->loadWorld(":/images/worldmap.png",20,60,100.0);

}


