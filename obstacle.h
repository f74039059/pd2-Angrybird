#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define OBSTACLE_DENSITY 1.0f
#define OBSTACLE_FRICTION 0.1f
#define OBSTACLE_RESTITUTION 0.5f


class Obstacle : public GameItem
{
public:
    Obstacle(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    virtual void effect(float mouseX, float mouseY);
};

#endif // OBSTACLE_H
