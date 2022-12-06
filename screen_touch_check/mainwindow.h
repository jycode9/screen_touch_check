#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void setLog(const QPoint& curpos);
    void setMark(const QPoint& curpos);

signals:
    void clickMouse(QPoint& curpos);
    void programClose();

public:
    void connectControl();
    //获取点击的位置
    void mousePressEvent(QMouseEvent *event);
    //键盘点击事件
    void keyPressEvent(QKeyEvent *event);

    //标记
    QLabel *label=nullptr;
    //存储label指针
    std::vector<QLabel*> labelvec;
    int clickNums=0;
};
#endif // MAINWINDOW_H
