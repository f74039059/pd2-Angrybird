#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include "mainwindow.h"
#include <QtCore>
#include <QMediaPlayer>


namespace Ui {
class FirstWindow;
}

class FirstWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    QLabel *bg;
    QPushButton *enterGame;
    QMediaPlayer *music = new QMediaPlayer();

private:
    Ui::FirstWindow *ui;
private slots:
    void open();
};

#endif // FIRSTWINDOW_H
