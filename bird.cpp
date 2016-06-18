#include "bird.h"
#include <iostream>


   Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
   {
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
       fixturedef.density = BIRD_DENSITY;
       fixturedef.friction = BIRD_FRICTION;
       fixturedef.restitution = BIRD_RESTITUTION;
       g_body->SetAngularDamping(2);
       g_body->CreateFixture(&fixturedef);





       // Bound timer
       connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

       scene->addItem(&g_pixmap);
   }

   void Bird::setLinearVelocity(b2Vec2 velocity)
   {
       g_body->SetLinearVelocity(velocity);
   }

   void Bird::effect(float mouseX, float mouseY)
   {
   }





