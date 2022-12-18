#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commands.h"
#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    void setSignalsFromProtagnist();
    bool eventFilter(QObject* obj, QEvent *event);

signals:
    void arrowPress(moveDirection direction);

public slots:
  void ChangeHealth(int health);
  void ChangeEnergy(int energy);
};



#endif // MAINWINDOW_H
