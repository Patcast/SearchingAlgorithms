#include "mainwindow.h"
#include "qtextedit.h"
#include "qpushbutton.h"

#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.showMaximized();
    return app.exec();

//    QApplication app(argc,argv);
//    QTextEdit monoEdit;
//    QTextDocument *doc = monoEdit.document();
//    QFont font = doc->defaultFont();
//    font.setFamily("Courier New");
//    doc->setDefaultFont(font);
//    monoEdit.setReadOnly(true);

//    QString PTText = "+---+---+---+---+---+---+\n| g |   |   | x |   |   |\n+---+---+---+---+---+---+";

//    monoEdit.setPlainText(PTText);

//    monoEdit.show();
//    return app.exec();
}
