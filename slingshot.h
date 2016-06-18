#ifndef SLINGSHOT_H
#define SLINGSHOT_H

#include <gameitem.h>
#include <QGraphicsScene>

class Slingshot: public GameItem
{
public:
    b2PolygonShape bodyBox;
    Slingshot(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void effect(float mouseX, float mouseY);
};

#endif // SLINGSHOT_H
