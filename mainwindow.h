#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
private slots:
  void handleButton();
private:
  QPushButton *m_button;
  QString gameText;
  QTextEdit *gameEdit;
};
#endif // MAINWINDOW_H
