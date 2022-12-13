# include "gameworld.h"
#include <iostream>
#include <cstdlib>


// TODO:
// No need to call emplace_back, I belive that no copies are generated when moving the enemies.
// Delete TIle Composition
// Make gameworld an instance and also the protagonist.
// Check random method to initialize protagonist
// Can I use variant for the special characters.
// Check for valid index, can be improved.
// Double check that enemies and hp are placed correctly.
// Maybe I can define my own hashing to use the un_ordered_set without an auxiliary colletion of indexes.





GameWorld::~GameWorld()
{

}
GameWorld::GameWorld(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist)
{
    World w= {};
    w.createWorld(pathToMap,nrEnemies,nrHeatlhPacks);
    setRowsAndColumns(w.getRows(),w.getCols());
    tiles= w.getTiles();

    enemies = w.getEnemies();
    healthPacks = w.getHealthPacks();
    specialFigures.resize(tiles.size());
    for(unsigned long i=0; i<enemies.size();i++){
        specialFigures[getIndexFromCoordinates(enemies[i]->getYPos(),enemies[i]->getXPos())];//= (std::move(enemies[i]));
    }
    for(unsigned long i=0; i<healthPacks.size();i++){
        specialFigures[getIndexFromCoordinates(healthPacks[i]->getYPos(),healthPacks[i]->getXPos())];//= (std::move(healthPacks[i]));
    }
    initializeProtagonist(startingEnergyProtagonist); // must be called at the end.

}

void GameWorld::Create(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist) //
{
    if(instance != 0)
        return;
    instance = new GameWorld( pathToMap,  nrEnemies,  nrHeatlhPacks,  startingEnergyProtagonist);
}

void GameWorld::Destroy()
{
    delete instance;
    instance = 0;
}

GameWorld *GameWorld::Instance(QString pathToMap, int nrEnemies, int nrHeatlhPacks, float startingEnergyProtagonist)
{
    GameWorld::Create(pathToMap,  nrEnemies,  nrHeatlhPacks,  startingEnergyProtagonist);
    return instance;
}





void GameWorld::setRowsAndColumns(int newRows, int newColumns)
{
    totalRows=newRows;
    totalColumns=newColumns;
}

int GameWorld::getTotalRows() const
{
    return totalRows;
}

int GameWorld::getTotalColumns() const
{
    return totalColumns;
}



const std::vector<std::unique_ptr<Tile> > &GameWorld::getTiles() const
{
    return tiles;
}



void GameWorld::initializeProtagonist(float startingEnergy)
{
    /*
    while(protagonist==nullptr){
        int x = rand()%(totalRows);
        int y = rand()%(totalRows);
        std::cout<<"(X,Y): "<<x<<"x"<<y<<std::endl;
        if(!specialFigures[getIndexFromCoordinates(x,y)].has_value()){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            protagonist->setXPos(x);
            protagonist->setYPos(y);
            std::cout<<"Protagonist created"<<std::endl;
        }
    }
    */
    bool free = true;
    while(protagonist==nullptr){
        free = true;
        int x = rand()%(totalRows);
        int y = rand()%(totalRows);
        std::cout<<"(X,Y): "<<x<<"x"<<y<<std::endl;
        for(std::unique_ptr<Enemy> &t:enemies){
            if((t->getXPos()==x)&&(t->getYPos()==y)){
                std::cout<<"same Pos"<<std::endl;
                free = false;
                break;
            }
        }
        for(std::unique_ptr<Tile> &t:healthPacks){
            if((t->getXPos()==x)&&(t->getYPos()==y)){
                std::cout<<"same Pos"<<std::endl;
                free = false;
                break;
            }
        }
        if(free){
            protagonist= std::make_unique<Protagonist>();
            protagonist->setEnergy(startingEnergy);
            protagonist->setXPos(x);
            protagonist->setYPos(y);
            }
        }

}







//********** TESTING**************//

//void GameWorld::makeSubsetOfTiles(int rows, int columns)
//{
//    std::cout<<"----------- "<<std::endl;

//    for(int i =0 ; i<rows;i++){
//        for(int j =0 ; j<columns;j++){
//            subSetOfTiles.push_back(std::move(tiles[getIndexFromCoordinates(i,j)]));
//        }
//    }
//    setRowsAndColumns(rows,columns);
//    std::cout<<"rows "<<rows<<" cols "<<columns<<std::endl;
//}
//void GameWorld::printTiles(int nrOfTiles)
//{
//   std::cout<<"(x,y)"<<std::endl;
//    for(int i =0;i<nrOfTiles;i++){
//       std::cout<<" ("<<tiles[i]->getYPos()<<","<<tiles[i]->getXPos()<<")"<<std::endl;
//    }
//}


//void GameWorld::printSubSetOftiles()
//{
//    for (unsigned long  i=0; i <subSetOfTiles.size();i++) {
//        int row_index,col_index;
//        row_index =subSetOfTiles[i]->getYPos(); // modify later to tiles.
//        col_index =subSetOfTiles[i]->getXPos();
//        std::cout<<row_index<<" x "<<col_index<<"  index:  " <<getIndexFromCoordinates(row_index,col_index)<<std::endl;
//    }
//}
















