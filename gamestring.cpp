#include "gamestring.h"
#include <iostream>
#include <utility>

GameString::GameString(int sizeH, int sizeV, int windowSizeH, int windowSizeV, int windowOffsetH, int windowOffsetV){
    this->_gameString = _getBoxRaster(windowSizeH, windowSizeV);
    this->_sizeH = sizeH;
    this->_sizeV = sizeV;
    this->_windowSizeH = windowSizeH;
    this->_windowSizeV = windowSizeV;
    this->_windowOffsetH = _cleanOffsetH(windowOffsetH);
    this->_windowOffsetV = _cleanOffsetV(windowOffsetV);
}

bool GameString::isVisible(std::pair<int,int> gameCoord) {
    return (_isVisible(this->_windowOffsetH, gameCoord.first, this->_windowSizeH) &&
            _isVisible(this->_windowOffsetV, gameCoord.second, this->_windowSizeV));
}

bool GameString::_isVisible(int offset, int coord, int viewSize) {
    return (coord >= offset) && (coord < (offset + viewSize));
}

void GameString::removeElement(QChar element) {
    this->_gameString.replace(element, QChar(' '));
}

int GameString::_cleanOffsetH(int potOffset) {
    return _cleanOffset(this->_sizeH, this->_windowSizeH, potOffset);
}

int GameString::_cleanOffsetV(int potOffset) {
    return _cleanOffset(this->_sizeV, this->_windowSizeV, potOffset);
}

int GameString::_cleanOffset(int boardSize, int viewSize, int potOffset) {
    int max = boardSize - viewSize;
    if (potOffset < 0) {
        return 0;
    } else if (potOffset > max) {
        return max;
    } else {
        return potOffset;
    }
}

int GameString::_getLineLength() {
    return 1 + (this->TILE_WIDTH + 1)*this->_windowSizeH + 1;
}

int GameString::_getStartOfLine(int yCoord) {
    int stringLineNumber = 1 + (this->TILE_HEIGHT + 1)*yCoord;
    return stringLineNumber*this->_getLineLength();
}

std::pair<int, int> GameString::_getBoardCoord(std::pair<int,int> gameCoord) {
    int intBoardX = gameCoord.first - this->_windowOffsetH;
    int intBoardY = gameCoord.second - this->_windowOffsetV;

    return std::make_pair(intBoardX, intBoardY);
}

int GameString::_getStringIndex(int xCoord, int yCoord) {
    int result = 0;
    result += this->_getStartOfLine(yCoord);
    result += this->_getBoxCenterInLine(xCoord);
    return result;
}

int GameString::_getBoxCenterInLine(int xCoord) {
    int result = 0;
    result += 1 + (int) floor((float)TILE_WIDTH / (float)2);
    result += xCoord*(TILE_WIDTH + 1);
    return result;
}

void GameString::setElement(std::pair<int,int> gameCoord, QChar element) {
    if (this->isVisible(gameCoord)) {
        std::pair<int, int> boardCoord = this->_getBoardCoord(gameCoord);
        int index = this->_getStringIndex(boardCoord.first, boardCoord.second);
        _gameString[index] = element;
    }
}

QString GameString::_getBoxSegment(bool starter, int line) {
    if(line != 1) {
        if (starter) {
            return QString("+---+");
        } else {
            return QString("---+");
        }
    } else {
        if (starter) {
            return QString("|   |");
        } else {
            return QString("   |");
        }
    }

}

QString GameString::_getBoxLine(bool starter, int line, int amount) {
    QString result = QString("");
    int i = amount;
    if ((i > 0) && starter) {
        result += _getBoxSegment(true, line);
        i--;
    }
    while (i > 0) {
        result += _getBoxSegment(false, line);
        i--;
    }
    return result;
}

QString GameString::_getFullBoxLine(bool starter, int amount) {
    QString result = QString("");
    if (starter) {
        result += _getBoxLine(true, 0, amount) + QString("\n");
    }
    result += _getBoxLine(true, 1, amount) + QString("\n");
    result += _getBoxLine(true, 2, amount) + QString("\n");
    return result;
}

QString GameString::_getBoxRaster(int amountX, int amountY) {
    QString result = QString("");
    int i = amountY;
    if ((i > 0)) {
        result += _getFullBoxLine(true, amountX);
        i--;
    }
    while (i > 0) {
        result += _getFullBoxLine(false, amountX);
        i--;
    }
    return result;
}

