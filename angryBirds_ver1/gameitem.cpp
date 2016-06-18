#include "gameitem.h"

#include <iostream>

GameItem::GameItem(b2World *world):
    g_body(NULL),g_world(world)
{
}

GameItem::~GameItem()
{
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    //std::cout<<worldsize.QSizeF<<std::endl;
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::movPos(float x, float y)
{
    float wordX,wordY;
    wordX = x / 30 ;
    wordY = 18 - y / 30 ;//18 b2wordY size
    g_body->SetTransform(b2Vec2(wordX,wordY),0);

}

void GameItem::shoot(float distanceX, float distanceY)
{
    float word_distanceX, word_distanceY;
    word_distanceX =  - (distanceX / 30);
    word_distanceY = distanceY / 30;
    g_body->SetLinearVelocity (b2Vec2 (5 * word_distanceX, 5 * word_distanceY)  );


}

void GameItem::accelerate()
{
    g_body->SetLinearVelocity(b2Vec2 (100, 5) );
}

void GameItem::still()
{
     g_body->SetLinearVelocity(b2Vec2 (0, 0) );
}





void GameItem::paint()
{

    b2Vec2 pos = g_body->GetPosition();
   //std::cout<<g_windowsize.height()<<std::endl;
  // std::cout<<g_worldsize.height()<<std::endl;
    //std::cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
   // std::cout<<mappedPoint.x()<<std::endl;
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
}

