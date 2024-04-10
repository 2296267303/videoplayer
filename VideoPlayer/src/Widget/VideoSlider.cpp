
#include "VideoSlider.h"

#include <QDebug>
#include <QTimer>
#include <QResizeEvent>
#include <QStyle>

VideoSlider::VideoSlider(QWidget *parent) :
    QSlider(parent)//将 parent 指针传递给 QSlider 的构造函数，以便正确设置滑块的父对象。
{
    setMouseTracking(true);//鼠标跟踪

    this->setOrientation(Qt::Horizontal);//设置水平方向

    isSliderMoving = false;

    m_timer = new QTimer;
    m_timer->setInterval(100);//定时器的时间间隔为 100 毫秒。
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slotTimerTimeOut()));

    m_timer_mousemove = new QTimer;
    m_timer_mousemove->setInterval(100);
    connect(m_timer_mousemove,SIGNAL(timeout()),this,SLOT(slotMousemoveTimerTimeOut()));
}//构造函数，用于初始化视频滑块控件。在这里，它设置了滑块的方向为水平，并初始化了一些成员变量和定时器。

VideoSlider::~VideoSlider()
{

}

void VideoSlider::resizeEvent(QResizeEvent *event)
{

}

void VideoSlider::mousePressEvent(QMouseEvent *event)
{
//    isSliderMoving = true;

    int posX = event->pos().x();

    int w = this->width();//获取视频滑块控件的宽度。



    int value = QStyle::sliderValueFromPosition(minimum(), maximum(), event->pos().x(), width());//计算出根据鼠标按下位置计算出的滑块的值。

    setValue(value);


    emit sig_valueChanged(value);

}

void VideoSlider::mouseMoveEvent(QMouseEvent *event)
{


    m_posX = event->pos().x();

    m_timer_mousemove->stop();
    m_timer_mousemove->start();

    QSlider::mouseMoveEvent(event);

}

void VideoSlider::mouseReleaseEvent(QMouseEvent *event)
{
    emit sig_valueChanged(this->value());

}

void VideoSlider::enterEvent(QEvent *)
{
    m_timer->stop();
}

void VideoSlider::leaveEvent(QEvent *)
{
    m_timer_mousemove->stop();
    m_timer->start();
}

bool VideoSlider::seek()
{
    return true;
}

void VideoSlider::setValue(int value)
{
    if (!isSliderMoving)
    QSlider::setValue(value);
}


bool VideoSlider::openFile(char*fileName)
{


    return true;
}

bool VideoSlider::closeFile()
{


    return 0;
}



void VideoSlider::slotTimerTimeOut()
{

////        videoThread->hideIn();

}

void VideoSlider::slotMousemoveTimerTimeOut()
{

    m_timer_mousemove->stop();

    int w = this->width();



    QPoint point = this->mapToGlobal(QPoint(0,0));
    int width = this->width();

    if (parent() != NULL)
    {
        QWidget *widget = (QWidget *)this->parent();
        point = widget->mapToGlobal(QPoint(0,0));

        width = widget->width();
    }



////    qDebug()<<value<<videoThread->getTotalTime();


}
