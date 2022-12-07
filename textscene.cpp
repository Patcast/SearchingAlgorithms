#include "textscene.h"

TextScene::TextScene() : Scene("text")
{
    // Setting string to game board
    gameText = QString("+---+---+---+---+---+---+\n| p |   |   | x |   |   |\n+---+---+---+---+---+---+\n");

    // Adding object to window to display string
    QTextEdit gameEdit = QTextEdit();
    QTextDocument *doc = gameEdit.document();
    QFont font = doc->defaultFont();
    font.setFamily("Courier New");
    doc->setDefaultFont(font);
    gameEdit.setReadOnly(true);
    gameEdit.setGeometry(QRect(QPoint(0, 0), QSize(400, 100)));

    // Adding string to object
    gameEdit.setText(gameText);

    widget = std::make_shared<QTextEdit>(gameEdit);
}
