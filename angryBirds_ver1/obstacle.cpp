#include "obstacle.h"
#include <iostream>
Obstacle::Obstacle(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
   // std::cout<<g_pixmap.boundingRect().width()<<std::endl;
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(w,h);//

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
   // bodydef.bullet = true;
    bodydef.position.Set(x,y);
   // bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = OBSTACLE_DENSITY;
    fixturedef.friction = OBSTACLE_FRICTION;
    fixturedef.restitution = OBSTACLE_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);



    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);

}

void Obstacle::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);

}

void Obstacle::effect()
{
    std::cout<<"success"<<std::endl;
}
