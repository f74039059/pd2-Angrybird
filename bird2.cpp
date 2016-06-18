#include "bird2.h"
#include <iostream>



Bird2::Bird2(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    bird2_world = world ;
    bird2_scene = scene;
    bird2_timer = timer;
    bird2_radius = radius ;
    bird2_pixmap = pixmap;

    // Set pixmap

    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    // Create Body

    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    //bodyshape.m_p.Set(0, 0);
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD2_DENSITY;
    fixturedef.friction = BIRD2_FRICTION;
    fixturedef.restitution = BIRD2_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird2::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}



void Bird2::effect(float mouseX, float mouseY)
{
    g_body->SetLinearVelocity(b2Vec2(40,0));
}
