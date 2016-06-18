#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bird2.h>
#include <obstacle.h>
#include <slingshot.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    QPointF startPoint;
    QPointF movePoint;
    QPointF distancePoint;

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void stopBirdTimer();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Slingshot  *slingshot ;
    Obstacle *obstacle2,*obstacle3,*obstacle4,*obstacle5;
    float obstacle_posx = 26.0f;
    QPushButton *quit;
    int bird_index = 3 , lastBird_index = 6;
    bool leftBird = true , needWaitBird = false;
    QTimer birdTimer ;

};

#endif // MAINWINDOW_H
