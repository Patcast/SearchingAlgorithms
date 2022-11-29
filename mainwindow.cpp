#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Setting string to game board
    gameText = QString("+---+---+---+---+---+---+\n| p |   |   | x |   |   |\n+---+---+---+---+---+---+\n");

    // Adding object to window to display string
    gameEdit = new QTextEdit(this);
    QTextDocument *doc = gameEdit->document();
    QFont font = doc->defaultFont();
    font.setFamily("Courier New");
    doc->setDefaultFont(font);
    gameEdit->setReadOnly(true);
    gameEdit->setGeometry(QRect(QPoint(0, 0), QSize(400, 100)));

    // Adding string to object
    gameEdit->setText(gameText);

    // Creating button
    m_button = new QPushButton("Move", this);
    m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    // Create signal and assign slot
    connect(m_button, &QPushButton::released, this, &MainWindow::handleButton);
}

void MainWindow::handleButton()
{
    if (gameText[28] == QChar('p')) {
        gameText[28] = QChar(' ');
        gameText[32] = QChar('p');
    } else {
        gameText[32] = QChar(' ');
        gameText[28] = QChar('p');
    }
    // std::cout << gameText.toStdString();
    // std::cout << gameEdit->toPlainText().toStdString();
    gameEdit->setText(gameText);
}

