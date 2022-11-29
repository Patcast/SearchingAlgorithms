#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QString>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class TextWindow; }
QT_END_NAMESPACE
namespace visual_text{
    class TextWindow : public QMainWindow
    {
        Q_OBJECT

    public:
      explicit TextWindow(QWidget *parent = nullptr);
    private slots:
      void handleButton();
    private:
      QPushButton *m_button;
      QString gameText;
      QTextEdit *gameEdit;
    };
}
#endif // MAINWINDOW_H
