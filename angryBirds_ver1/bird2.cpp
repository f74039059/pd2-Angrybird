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
    //std::cout<<g_pixmap.transformOriginPoint().x()<<std::endl;
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
   //std::cout<<g_pixmap.transformOriginPoint().x()<<std::endl;
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

void Bird2::effect()
{
    g_body->SetLinearVelocity(b2Vec2(100,0));
    /*
    g_pixmap.setPixmap(bird2_pixmap);
    //std::cout<<g_pixmap.transformOriginPoint().x()<<std::endl;
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
   //std::cout<<g_pixmap.transformOriginPoint().x()<<std::endl;
    g_size = QSize(bird2_radius*2,bird2_radius*2);
    // Create Body
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(15,15);
    bodydef.userData = this;
    g_body = bird2_world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    //bodyshape.m_p.Set(0, 0);
    bodyshape.m_radius = bird2_radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD2_DENSITY;
    fixturedef.friction = BIRD2_FRICTION;
    fixturedef.restitution = BIRD2_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetLinearVelocity(b2Vec2(100,0));
    // Bound timer
    connect(bird2_timer, SIGNAL(timeout()), this,SLOT(paint()));
    bird2_scene->addItem(&g_pixmap);
    */

    std::cout<<"bird2 effect"<<std::endl;
}
