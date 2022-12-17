#include "gamestring.h"

GameString::GameString(int sizeH, int sizeV, int windowSizeH, int windowSizeV, int windowOffsetH, int windowOffsetV){

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
