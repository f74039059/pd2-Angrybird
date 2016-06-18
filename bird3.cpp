#include "bird3.h"
#include <iostream>


   Bird3::Bird3(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
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
       fixturedef.density = BIRD3_DENSITY;
       fixturedef.friction = BIRD3_FRICTION;
       fixturedef.restitution = BIRD3_RESTITUTION;
       g_body->SetAngularDamping(2);
       g_body->CreateFixture(&fixturedef);





       // Bound timer
       connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

       scene->addItem(&g_pixmap);
   }

   void Bird3::setLinearVelocity(b2Vec2 velocity)
   {
       g_body->SetLinearVelocity(velocity);
   }

   void Bird3::effect(float mouseX, float mouseY)
   {
       float nowX,nowY;
       nowX = g_body->GetPosition().x;
       nowY =g_body->GetPosition().y;
       float distanceX,distanceY;
       distanceX = mouseX - nowX;
       distanceY = mouseY - nowY;
       g_body->SetAngularVelocity(30.0);
       g_body->SetLinearVelocity (b2Vec2 (3 * distanceX, 3 * distanceY)  );
   }
