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
    this->show();
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
    quit->setStyleSheet("background-image:url(:/background);");
    quit->show();
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(QUITSLOT()));

    //restartButton
    restartButton = new QPushButton("Restart",this);
    restartButton->setFont(QFont("Courier New", 25, QFont::Bold));
    restartButton->setGeometry(125, 0, 175, 70);
    restartButton->setStyleSheet("background-image:url(:/background);");
    restartButton->show();
    QObject::connect(restartButton, SIGNAL(clicked()), this, SLOT(restart()));

    //continually check enermy die or not in 0.2s
    connect(&enermyTimer,SIGNAL(timeout()),this,SLOT(enermyDetectHit()));
    enermyTimer.start(200);

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());

    //Score Label
    Score = new QLabel("Score:",this);
    Score->setFont(QFont("Courier New", 25, QFont::Bold));
    Score->setGeometry(700, 0, 175, 70);
    Score->show();
    //ScorePoints Label
    ScorePoint = new QLabel("0",this);
    ScorePoint->setFont(QFont("Courier New", 25, QFont::Bold));
    ScorePoint->setGeometry(825, 0, 100, 70);
    ScorePoint->show();

    //congrats label
    congratsLabel = new QLabel("",this);
    congratsLabel->setGeometry(300, 100, 349, 252);

    //Create slingshot
    itemList.push_back(new Slingshot(5,5.5,1.8f,4.3f,QPixmap(":/image/slingshot.png").scaled(height()/9.0,height()/4.0),world,scene));
    // Create ground
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/3.0),world,scene));
    //create wall
    itemList.push_back(new Land(32,12,4,18,QPixmap(":/image/wall2.jpeg").scaled(width()/8.0,height()),world,scene));
    // Create bird
    itemList.push_back(new Bird(5.0f,8.0f,0.9f,&timer,QPixmap(":/bird").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new Bird2(7.0f,5.0f,0.9f,&timer,QPixmap(":/bird2").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back( new Bird3(8.5f,5.0f,0.9f,&timer,QPixmap(":/bird3").scaled(height()/9.0,height()/9.0),world,scene));
    //bird4
    itemList.push_back(new Bird2(10.0f,5.0f,0.9f,&timer,QPixmap(":/bird4").scaled(height()/9.0,height()/9.0),world,scene));
    //bird4 small top
    itemList.push_back(new Bird4(-2.0f,5.0f,0.6f,&timer,QPixmap(":/bird4").scaled(height()/12.0,height()/12.0),world,scene));
    //bird4 small down
    itemList.push_back(new Bird4(-4.0f,5.0f,0.6f,&timer,QPixmap(":/bird4").scaled(height()/12.0,height()/12.0),world,scene));
   //all obstacles
   itemList.push_back(new Obstacle(obstacle_posx,4.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx,6.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx,8.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-2.0,4.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-4.0,4.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-4.0,6.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-4.0,8.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-2.0,9.6f,5.1f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/3.0,height()/9.0),world,scene));

   //terrain
   itemList.push_back(new Land(29.5,6,2.5,6,QPixmap(":/image/wall2.jpeg").scaled(width()/14.0,height()/3.0),world,scene));
    itemList.push_back(new Land(14,5,2.5,4,QPixmap(":/wall3").scaled(width()/14.0,height()/4.5),world,scene));
   //enermy
   itemList.push_back(new Obstacle(24.0,6.1f,1.7f,1.7f,&timer,QPixmap(":/enermy").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(29,10.0f,2.0f,2.0f,&timer,QPixmap(":/enermy2").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(24.0,7.8f,1.7f,1.7f,&timer,QPixmap(":/enermy3").scaled(height()/9.0,height()/9.0),world,scene));

  // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    //connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

}

//use for event
bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // if click the correct side , the choose flag will be true
    static bool chooseFlag = false;
    QMouseEvent  *mouseEvent = static_cast<QMouseEvent *>(event);
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress )
    {

        if ( mouseEvent->button() == Qt::LeftButton)
        {
            if(needWaitBird == false) //you can shoot birds now
            {
                startPoint = mouseEvent->pos() ;
                movePoint = mouseEvent->pos();

                //the start click area
                if ( startPoint.x() > 140 && startPoint.x() < 190 && startPoint.y() >270 && startPoint.y() < 330 && leftBird == true )
                {
                    chooseFlag = true;
                    itemList[bird_index]->still();
                }
            }
            else if (needWaitBird == true) //wait shooting birds,and can use birds' effect
            {
                float wordX,wordY;//wordX=in box2D's x coordinate position
                wordX = mouseEvent->x() / 30 ;
                wordY = 18 - (mouseEvent->y() / 30);
                if(birdEffectUsed == false)//havent use bird effect
                {
                    if (bird_index == bird4_index)//bird4 need use 3 birds
                    {
                        float bird4_nowX,bird4_nowY;
                        bird4_nowX = itemList[bird_index]->getNowX();//need bird4 x,y to determine the other two birds
                        bird4_nowY = itemList[bird_index]->getNowY();
                        itemList[bird_index]->effect(wordX,wordY);
                        itemList[bird_index+1]->setPos(bird4_nowX+1.5,bird4_nowY+1.5);//top bird
                        itemList[bird_index+2]->setPos(bird4_nowX+1.5,bird4_nowY-1.5);//down bird
                        itemList[bird_index+1]->accelerateBird4Top();
                        itemList[bird_index+2]->accelerateBird4Down();
                    }
                    else
                    {
                        itemList[bird_index]->effect(wordX,wordY);//other birds
                    }
                    birdEffectUsed = true;//after bird effect use , flag set true
                }
            }
        }
    }
    if(event->type() == QEvent::MouseMove && chooseFlag == true )
    {
        movePoint = mouseEvent->pos();
        //where mouse can move after click bird
          if ( movePoint.x() > 0 && movePoint.x() < 280 && movePoint.y() >215 && movePoint.y() < 365 )
          {
              itemList[bird_index]->movPos(movePoint.x() , movePoint.y());
              if(birdSoundFlag == false) //when move birds sound
              {
                  birdSoundFlag = true;
                  moveBird->setSource(QUrl("qrc:/moveBird"));
                  moveBird->setVolume(1.0);
                  moveBird->play();
              }
          }
    }
    if(event->type() == QEvent::MouseButtonRelease)//after release
    {
        if(needWaitBird == false)//after release we will set needWaitBird = true  to wait player use bird effect
        {
            if(chooseFlag == true)
            {
                if(shootSoundFlag == false) //after shoot sound
                {
                    shootSoundFlag = true;
                    shootSound->setSource(QUrl("qrc:/shootSound2"));
                    shootSound->setVolume(1.0);
                    shootSound->play();
                }
                //move slingshot avoid collide
                itemList[slingshot_index]->setPos(-1.0,0.0);
                needWaitBird = true;

                //birdTimer after shoot bird 3S call stopBirdTimer
                connect(&birdTimer,SIGNAL(timeout()),this,SLOT(stopBirdTimer()));
                birdTimer.start(3000);
                chooseFlag = false;

                //determine birds shoot where
                distancePoint = movePoint - startPoint;
                itemList[bird_index]->shoot (distancePoint.x(), distancePoint.y() );
              
            }
        }
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
    this->close();
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

//change to next bird and reset
void MainWindow::stopBirdTimer()
{
    birdEffectUsed = false;
    birdSoundFlag = false;
    shootSoundFlag=false;
    if(needWaitBird == true)
    {
        //move slingshot to original position
        itemList[slingshot_index]->setPos(5,5.5);
        /*move this shooting bird outside,because i dont want to destruct it , and it more convenient
        for me to use "for loop" to  destruct all items after i click RestartButton*/
        itemList[bird_index]->still();
        itemList[bird_index]->moveOutside();

        if (bird_index == lastBird_index  )//lastBird_index = bird4_index
        {
            itemList[bird_index+1]->moveOutside();
            itemList[bird_index+2]->moveOutside();
            birdsUsed++;//count how many birds used to add score after winning

            leftBird = false;
            std::cout << "No birds" << std::endl;
        }
        else if( bird_index < lastBird_index )//remaining birds
        {
            bird_index += 1 ;
            birdsUsed++;
            itemList[bird_index]->setBirdStart();//move onto slingshot
        }
        needWaitBird = false;
        std::cout << "birdTimer receive !" << std::endl ;
        if (gameClear == true ) //all enermy die
        {
            gameSet();//add scores if remaining birds no used
        }
        birdTimer.stop();
    }

}
//detect enermy whether die or not
void MainWindow::enermyDetectHit()
{
    //check enermy's velocity to detemine die
    float enermy1_Vx,enermy1_Vy,enermy2_Vx,enermy2_Vy,enermy3_Vx,enermy3_Vy;
    enermy1_Vx = itemList[enermyIndex]->getVelocityX();
    enermy1_Vy = itemList[enermyIndex]->getVelocityY();
    enermy2_Vx = itemList[enermyIndex+1]->getVelocityX();
    enermy2_Vy = itemList[enermyIndex+1]->getVelocityY();
    enermy3_Vx = itemList[enermyIndex+2]->getVelocityX();
    enermy3_Vy = itemList[enermyIndex+2]->getVelocityY();
    if ( enermy1_die == false )
    {
        if ( enermy1_Vx>1.5 || enermy1_Vy >1.5 )
        {
            itemList[enermyIndex]->moveOutside();
            enermy1_die = true;
            addScore();
        }
    }
    if ( enermy2_die == false )
    {
        if ( enermy2_Vx>0.5 || enermy2_Vy >0.5  )
        {
            itemList[enermyIndex+1]->moveOutside();
            enermy2_die = true;
            addScore();
        }
    }
    if ( enermy3_die == false )
    {
        if ( enermy3_Vx>1.5|| enermy3_Vy >1.5 )
        {
            itemList[enermyIndex+2]->moveOutside();
            enermy3_die = true;
            addScore();
        }
    }

    if ( enermy1_die ==true && enermy2_die == true && enermy3_die == true && gameClear == false)
    {
        gameClear = true;
        std::cout <<"game set" << std::endl;
    }


}

void MainWindow::addScore()
{
    int nowPoint = ScorePoint->text().toInt()+1000;
    ScorePoint->setText(QString::number(nowPoint));
    ScorePoint->show();
}

void MainWindow::gameSet()
{
    congratsMusic->setSource(QUrl("qrc:/congratsMusic"));
    congratsMusic->setVolume(1.0);
    congratsMusic->play();
    std::cout <<"gameset AddScore" << std::endl;
    //one remain birds +2000points
    int nowPoint =  ScorePoint->text().toInt() +(allBirds - birdsUsed)*2000;
    ScorePoint->setText(QString::number(nowPoint));
    ScorePoint->show();
    QPixmap congrats(":/congrats");
    congratsLabel->setPixmap(congrats);
    congratsLabel->show();

}

void MainWindow::restart()
{
    shootSoundFlag = false;
    birdSoundFlag = false;
    congratsLabel->hide();
    bird_index = 3;
    leftBird = true , needWaitBird = false;
    birdEffectUsed = false;
    enermy1_die = false ,enermy2_die = false , enermy3_die = false;
    gameClear = false;
    birdsUsed = 0;

    //Score Label
    Score->setText("Score:");
    //ScorePoints Label
    ScorePoint->setText("0");

    //detruct all items
    int i = 0;
    for(i=0;i<=allGameItem;i++)
    {
        itemList[i]->~GameItem();
    }
    itemList.clear();//clean QList ,let QList from first to pushback

    //Create Slingshot
    itemList.push_back(new Slingshot(5,5.5,1.8f,4.3f,QPixmap(":/image/slingshot.png").scaled(height()/9.0,height()/4.0),world,scene));
    // Create ground
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/3.0),world,scene));
    //create wall
    itemList.push_back(new Land(32,12,4,18,QPixmap(":/image/wall2.jpeg").scaled(width()/8.0,height()),world,scene));
    // Create bird
    itemList.push_back(new Bird(5.0f,8.0f,0.9f,&timer,QPixmap(":/bird").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back(new Bird2(7.0f,5.0f,0.9f,&timer,QPixmap(":/bird2").scaled(height()/9.0,height()/9.0),world,scene));
    itemList.push_back( new Bird3(8.5f,5.0f,0.9f,&timer,QPixmap(":/bird3").scaled(height()/9.0,height()/9.0),world,scene));
    //bird4
    itemList.push_back(new Bird2(10.0f,5.0f,0.9f,&timer,QPixmap(":/bird4").scaled(height()/9.0,height()/9.0),world,scene));
    //bird4 small top
    itemList.push_back(new Bird4(-2.0f,5.0f,0.6f,&timer,QPixmap(":/bird4").scaled(height()/12.0,height()/12.0),world,scene));
    //bird4 small down
    itemList.push_back(new Bird4(-4.0f,5.0f,0.6f,&timer,QPixmap(":/bird4").scaled(height()/12.0,height()/12.0),world,scene));
   //obstacle
    itemList.push_back(new Obstacle(obstacle_posx,4.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx,6.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx,8.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-2.0,4.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-4.0,4.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-4.0,6.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-4.0,8.1f,1.7f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(obstacle_posx-2.0,9.6f,5.1f,1.7f,&timer,QPixmap(":/image/box.png").scaled(height()/3.0,height()/9.0),world,scene));

   //terrain
   itemList.push_back(new Land(29.5,6,2.5,6,QPixmap(":/image/wall2.jpeg").scaled(width()/14.0,height()/3.0),world,scene));
    itemList.push_back(new Land(14,5,2.5,4,QPixmap(":/wall3").scaled(width()/14.0,height()/4.5),world,scene));
   //enermy
   itemList.push_back(new Obstacle(24.0,6.1f,1.7f,1.7f,&timer,QPixmap(":/enermy").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(29,10.0f,2.0f,2.0f,&timer,QPixmap(":/enermy2").scaled(height()/9.0,height()/9.0),world,scene));
   itemList.push_back(new Obstacle(24.0,7.8f,1.7f,1.7f,&timer,QPixmap(":/enermy3").scaled(height()/9.0,height()/9.0),world,scene));
}
