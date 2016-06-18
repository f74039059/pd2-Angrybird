#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    void movPos (float x, float y);
    void shoot (float distanceX , float distanceY);
    void accelerate();
    void still();
    void setBirdStart();
    void setPos(float posX, float posY);
    void moveOutside();
    virtual void effect(float mouseX, float mouseY) = 0;//bird effect using pure virtual poly
    float getNowX();
    float getNowY();
    void accelerateBird4Top();
    void accelerateBird4Down();
    float getVelocityX();
    float getVelocityY();
    bool des=false;


public slots:
    void paint();
    // TODO virtual void collide();
protected:
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
};

#endif // GAMEITEM_H
