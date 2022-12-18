#include "textscene.h"
#include "gameworld.h"
#include "xenemy.h"

int DEFAULT_HSIZE = 15;
int DEFAULT_VSIZE = 15;

TextScene::TextScene() : Scene("text")
{
    GameWorld *gameWorld = GameWorld::Instance();

    Protagonist *protagonist = gameWorld->getProtagonist();

    // Setting string to game board

    int hSize = gameWorld->getTotalColumns();
    int vSize = gameWorld->getTotalRows();

    this->_generate(hSize, vSize, DEFAULT_HSIZE, DEFAULT_VSIZE,
                    gameWorld->getSpecialFiguresVector(),
                    std::make_pair(protagonist->getXPos(), protagonist->getYPos()));

    // Adding object to window to display string
    QTextEdit *gameEdit = new QTextEdit;
    QTextDocument *doc = gameEdit->document();
    QFont font = doc->defaultFont();
    font.setFamily("Courier New");
    doc->setDefaultFont(font);
    gameEdit->setReadOnly(true);
    gameEdit->setGeometry(QRect(QPoint(0, 0), QSize(400, 100)));

    // Adding string to object
    gameEdit->setText(this->gameString->getGameString());

    this->widget = gameEdit;
}

void TextScene::drawEnemy(int xPos, int yPos){
    this->drawEnemy(std::make_pair(xPos,yPos));
}
void TextScene::drawEnemy(std::pair<int,int> pos){
    this->gameString->setElement(pos, QChar('E'));
}

void TextScene::drawPEnemy(int xPos, int yPos){
    this->drawPEnemy(std::make_pair(xPos,yPos));
}
void TextScene::drawPEnemy(std::pair<int,int> pos){
    this->gameString->setElement(pos, QChar('F'));
}

void TextScene::drawXEnemy(int xPos, int yPos){
    this->drawXEnemy(std::make_pair(xPos,yPos));
}
void TextScene::drawXEnemy(std::pair<int,int> pos){
    this->gameString->setElement(pos, QChar('X'));
}
void TextScene::drawProtagonist(int xPos, int yPos){
    this->drawProtagonist(std::make_pair(xPos,yPos));
}
void TextScene::drawProtagonist(std::pair<int,int> pos) {
    this->gameString->setElement(pos, QChar('P'));
}
void TextScene::drawTile(){

}
void TextScene::drawHealthPack(int xPos, int yPos){
    this->drawHealthPack(std::make_pair(xPos,yPos));
}
void TextScene::drawHealthPack(std::pair<int,int> pos){
    this->gameString->setElement(pos, QChar('H'));
}
void TextScene::drawMovement(int xPos, int yPos){
    GameWorld *gameWorld = GameWorld::Instance();
    Protagonist *protagonist = gameWorld->getProtagonist();

    int hSize = gameWorld->getTotalColumns();
    int vSize = gameWorld->getTotalRows();

    this->_generate(hSize, vSize, DEFAULT_HSIZE, DEFAULT_VSIZE,
                    gameWorld->getSpecialFiguresVector(),
                    std::make_pair(protagonist->getXPos(), protagonist->getYPos()));

    QTextEdit *gameEdit = dynamic_cast<QTextEdit*>(this->widget);
    gameEdit->setText(this->gameString->getGameString());
}

void TextScene::drawElements(const std::vector<std::shared_ptr<Tile>> &elements) {
    for (auto &element : elements) {
        std::shared_ptr<PEnemy> penemy = std::dynamic_pointer_cast<PEnemy>(element);
        std::shared_ptr<XEnemy> xenemy = std::dynamic_pointer_cast<XEnemy>(element);
        std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(element);
        if (penemy != nullptr) {
            if (!penemy->getDefeated()) {
                this->drawPEnemy(element->getXPos(),element->getYPos());
            }
        } else if (xenemy != nullptr) {
            if (!xenemy->getDefeated()) {
                this->drawXEnemy(element->getXPos(),element->getYPos());
            }
        } else if (enemy != nullptr) {
            if (!enemy->getDefeated()) {
                this->drawEnemy(element->getXPos(),element->getYPos());
            }
        } else if (std::dynamic_pointer_cast<Protagonist>(element) != nullptr) {

        } else if (element->getValue() > 0){
            this->drawHealthPack(element->getXPos(),element->getYPos());
        }
    }
}

void TextScene::_generate(int hSize, int vSize, int DEFAULT_HSIZE, int DEFAULT_VSIZE,
                          const std::vector<std::shared_ptr<Tile>> &elements,
                          std::pair<int,int> protPos) {
    int offsetX = protPos.first - (floor((float) DEFAULT_HSIZE / (float) 2));
    int offsetY = protPos.second - (floor((float) DEFAULT_VSIZE / (float) 2));

    gameString = std::make_shared<GameString>(hSize, vSize, DEFAULT_HSIZE, DEFAULT_VSIZE,offsetX,offsetY);

    this->drawElements(elements);
    this->drawProtagonist(protPos);


}

void TextScene::zoomIn()
{

}

void TextScene::zoomOut()
{

}

void TextScene::drawHighlight(int xPos, int yPos) {

}
void TextScene::removeHighlight(int xPos, int yPos) {

}

void TextScene::drawPoisonous(int xPos, int yPos) {

}

void TextScene::drawExplosive(int xPos, int yPos) {

}

void TextScene::removePoisonous(int xPos, int yPos) {

}
