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
#include <QLabel>
#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <bird2.h>
#include "bird3.h"
#include <bird4.h>
#include <obstacle.h>
#include <slingshot.h>
#include <QSoundEffect>
#include <QtGui>


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
    void enermyDetectHit();
    //
    void restart();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    float obstacle_posx = 26.0f;
    QPushButton *quit;
    int bird_index = 3 , lastBird_index = 6 , bird4_index=6;
    bool leftBird = true , needWaitBird = false;
    QTimer birdTimer,enermyTimer ;
    int slingshot_index=0;
    QLabel *birdAnime,*Score,*ScorePoint;
    bool birdEffectUsed = false;
    int enermyIndex = 19;
    bool enermy1_die = false ,enermy2_die = false , enermy3_die = false;
    bool gameClear = false;
    void addScore();
    void gameSet();//3enermy dies and add point if there are birds remain
    int birdsUsed = 0 ,allBirds = 4;
    QPushButton *restartButton;
    QLabel *congratsLabel;
    QSoundEffect *congratsMusic = new QSoundEffect();
    QSoundEffect *moveBird = new QSoundEffect();
    QSoundEffect *shootSound = new QSoundEffect();
    bool birdSoundFlag = false,shootSoundFlag = false;
    int allGameItem = 21;
};

#endif // MAINWINDOW_H
