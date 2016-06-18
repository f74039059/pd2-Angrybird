#include "firstwindow.h"
#include "ui_firstwindow.h"
#include "iostream"
FirstWindow::FirstWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Hello, Qt!");
    this->setMinimumSize(960, 540);
    this->setMaximumSize(960, 540);
    this->show();

    QPixmap bgmap(":/main");
    bg = new QLabel("Start",this);
    bg->setGeometry(0, 0, 960, 540);
    bg->setPixmap(bgmap);
    bg->show();

    QPixmap buttonMap(":/startButton");
    buttonMap = buttonMap.scaled( 120 , 70);
    enterGame = new QPushButton("",this);
    enterGame->setGeometry(420, 260, 120, 70);
    enterGame->setStyleSheet("background-image:url(:/startButton);");
    enterGame->show();

    music->setMedia(QUrl("qrc:/startMusic"));
    music->setVolume(50);
    music->play();

    QObject::connect(enterGame, SIGNAL(clicked()), this, SLOT(open()));


}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::open()
{
    this->close();
    MainWindow *good = new MainWindow;
}
