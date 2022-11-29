#include "mainwindow.h"
<<<<<<< HEAD
#include <iostream>
=======
#include "qtextedit.h"
#include "qpushbutton.h"

>>>>>>> 2-basic-text-widget
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    std::cout<<"hello Patt"<<std::endl;

    return a.exec();
=======
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
>>>>>>> 2-basic-text-widget
}
