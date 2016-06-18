#ifndef BIRD3_H
#define BIRD3_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BIRD3_DENSITY 10.0f
#define BIRD3_FRICTION 0.2f
#define BIRD3_RESTITUTION 0.5f

class Bird3 : public GameItem
{
public:
    b2BodyDef bodydef;
    Bird3(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void effect(float mouseX, float mouseY);

};

#endif // BIRD_H
