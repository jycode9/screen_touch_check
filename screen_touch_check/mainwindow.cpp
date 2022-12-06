#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>
#include <QScreen>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //界面设为无边框
    setWindowFlags(Qt::FramelessWindowHint);
    //获取设备屏幕，覆盖系统任务栏
    QScreen *screen=qApp->primaryScreen();
    this->resize(screen->size());

    this->setWindowTitle(QString("ScreenTouchCheck"));

    //所有信号和槽连接的函数
    connectControl();

    qDebug() <<"MainWindow Done";
}

MainWindow::~MainWindow()
{
    //释放指针
    for(auto iter=labelvec.begin(); iter!=labelvec.end(); iter++){
        if(*iter!=nullptr){
            delete *iter;
        }
    }
    labelvec.clear();
    qDebug() <<"~MainWindow Done";
    delete ui;
}

void MainWindow::connectControl(){
    connect(this, &MainWindow::clickMouse, [=](QPoint curpos){
        clickNums++;
        setLog(curpos);
        setMark(curpos);
    });

    connect(this, &MainWindow::programClose, [=](){
        qDebug() <<"Program Quite";
        qApp->quit();
    });
}


void MainWindow::setLog(const QPoint& curpos)
{
    //当被点击时，输出当前的日期
    QString message = QString("Check Screen Touched:") + "\n";
    message = message + "Times: " + QString::number(clickNums) + "\n";
    message = message + QString("Time: ");
    message += QDate::currentDate().toString();
    message += ", ";
    message += QTime::currentTime().toString();

    //添加点击位置
    message = message + ";" + "\n" + "Pos(X,Y): (";
    message += QString::number(curpos.x());
    message += ", ";
    message += QString::number(curpos.y());
    message = message + ");" + "\n";

    qDebug()<<message;

    //将内容保存到文件中
    QFile file("./check_info.txt");
    //以文本方式打开
    if( file.open(QIODevice::Append | QIODevice::Text) )
    {
        QTextStream write(&file);
        write<<message<<Qt::endl;
        file.close();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->type()==QEvent::MouseButtonPress){
        QPoint curpos = event->pos();
        //鼠标的左中右键都可以触发这个信号
        emit clickMouse(curpos);
    }
}


void MainWindow::setMark(const QPoint& curpos){
    //在被点击的区域做标记（在该坐标添加空间）
    label = new QLabel(this);
    label->resize(QSize(20,20));
    label->setPixmap(QPixmap(":/mark/error.png"));
    label->setScaledContents(true);
    label->move(QPoint(curpos.x()-10, curpos.y()-10));
    label->show();
    qDebug() <<"Set A Mark Sucess";
    //将label压入vec
    labelvec.push_back(label);
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
    //ESC键
    case Qt::Key_Escape:
        qDebug() <<"Click ESC";
        emit programClose();
        break;
    default:
        break;
    }

}
