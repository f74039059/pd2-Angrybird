#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDrag>
#include <QMimeData>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    //Quit Button
    quit = new QPushButton("Quit",this);
    quit->setFont(QFont("Courier New", 25, QFont::Bold));
    quit->setGeometry(10, 0, 100, 70);
    quit->show();
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(QUITSLOT()));


    std::cout<<height()<<std::endl;
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());

    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());


   // itemList.push_back(new Joint(10,5.0f,1.7f,1.7f,&timer,QPixmap(":/box.png").scaled(height()/9.0,height()/9.0),world,scene));


    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/3.0),world,scene));
    //create wall
    itemList.push_back(new Land(32,12,4,18,QPixmap(":/image/wall2.jpeg").scaled(width()/8.0,height()),world,scene));

    //create slingshotd
     slingshot = new Slingshot(5,5.5,1.8f,0.3f,QPixmap(":/image/slingshot.png").scaled(height()/9.0,height()/9.0),world,scene);
    //slingshot = new Slingshot(5,5.5,1.8f,4.3f,QPixmap(":/slingshot.png").scaled(height()/9.0,height()/4.0),world,scene);
    itemList.push_back(slingshot);


    // Create bird (You can edit here)

    itemList.push_back(new Bird(5.0f,6.0f,0.9f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene));

    itemList.push_back(new Bird2(7.0f,6.0f,0.9f,&timer,QPixmap(":/bird2_speedup").scaled(height()/9.0,height()/9.0),world,scene));

    itemList.push_back( new Bird(8.5f,6.0f,0.9f,&timer,QPixmap(":/bird3").scaled(height()/9.0,height()/9.0),world,scene));

    itemList.push_back(new Bird(10.0f,6.0f,0.9f,&timer,QPixmap(":/bird4").scaled(height()/9.0,height()/9.0),world,scene));



    /*Bird *a = new Bird(9.0f,4.0f,0.9f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    // Setting the Velocity
    a->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(a);
*/

   /*Obstacle *obstacle = new Obstacle(0.0f,4.7f,1.7f,0.8f,&timer,QPixmap(":/box").scaled(height()/9.0,height()/9.0),world,scene);
   obstacle->setLinearVelocity(b2Vec2(10,0));
   itemList.push_back(obstacle);*/

   obstacle2 = new Obstacle(obstacle_posx,5.0f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene);
   obstacle2->setLinearVelocity(b2Vec2(0,0));
   itemList.push_back(obstacle2);

   obstacle3 = new Obstacle(obstacle_posx,7.0f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene);
   obstacle3->setLinearVelocity(b2Vec2(0,0));
   itemList.push_back(obstacle3);

   obstacle4 = new Obstacle(obstacle_posx,9.0f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene);
   obstacle4->setLinearVelocity(b2Vec2(0,0));
   itemList.push_back(obstacle4);

   obstacle5 = new Obstacle(obstacle_posx,10.5f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene);
   obstacle5->setLinearVelocity(b2Vec2(0,0));
   itemList.push_back(obstacle5);

    // itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/slingshot.png").scaled(width()/9.0,height()/12.0),world,scene));



    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    //connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

}
//小鳥射出 障礙物不見 換鳥障礙物回來 小鳥彈跳上來
bool MainWindow::eventFilter(QObject *, QEvent *event)
{

    static bool chooseFlag = false;
    QMouseEvent  *mouseEvent = static_cast<QMouseEvent *>(event);
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress )
    {

        if ( mouseEvent->button() == Qt::LeftButton)
        {
            if(needWaitBird == false)
            {
                startPoint = mouseEvent->pos() ;
                movePoint = mouseEvent->pos();

                if ( startPoint.x() > 140 && startPoint.x() < 190 && startPoint.y() >270 && startPoint.y() < 320 && leftBird == true )
                {

                    chooseFlag = true;
                    itemList[bird_index]->shoot ( 0 , 0 );
                }
            }
            else if (needWaitBird == true)
            {
                itemList[bird_index]->effect();
            }

        }

       //std::cout << "Press !" << std::endl ;

    }
    if(event->type() == QEvent::MouseMove && chooseFlag == true )
    {
        movePoint = mouseEvent->pos();

          if ( movePoint.x() > 10 && movePoint.x() < 290 && movePoint.y() >220 && movePoint.y() < 390 )
          {
              itemList[bird_index]->movPos(movePoint.x() , movePoint.y());
          }


           //
            //

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(needWaitBird == false)
        {
            if(chooseFlag == true)
            {
                needWaitBird = true;
                connect(&birdTimer,SIGNAL(timeout()),this,SLOT(stopBirdTimer()));
                birdTimer.start(3000);
                chooseFlag = false;
                distancePoint = movePoint - startPoint;
                itemList[bird_index]->shoot (distancePoint.x(), distancePoint.y() );





            }



        }


        //std::cout << distancePoint.x() << std::endl ;
        //std::cout << distancePoint.y() << std::endl ;

        //movePoint = startPoint;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    this->close();
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::stopBirdTimer()
{
    if(needWaitBird == true)
    {

        if (bird_index == lastBird_index  )
        {
            leftBird = false;
            std::cout << "No birds" << std::endl;
            std::cout << bird_index  << std::endl;
        }
        else if( bird_index < lastBird_index )
        {
            bird_index += 1 ;
            std::cout << bird_index << std::endl;
        }
        needWaitBird = false;
        std::cout << "birdTimer receive !" << std::endl ;
        birdTimer.stop();
    }

}
