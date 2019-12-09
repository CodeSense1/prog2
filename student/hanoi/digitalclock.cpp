#include "digitalclock.hh"

#include <QTime>
#include <iostream>


DigitalClock::DigitalClock(QWidget *parent)
    : parent_(parent)
{

    timer = new QTimer(this);
    time = new QTime(0,0,0);

    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);

    showTime();

}

QTime* DigitalClock::getElapsedTime() const
{
    return time;
}

void DigitalClock::stop()
{
    timer->stop();
}

void DigitalClock::restart()
{
    time = new QTime(0,0,0);
    emit(onRestart());
}

void DigitalClock::showTime()
{
    *time = time->addSecs(1);
    emit(valueChanged());

}
