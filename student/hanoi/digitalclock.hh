#ifndef DIGITALCLOCK_HH
#define DIGITALCLOCK_HH

#include <QObject>
#include <QLCDNumber>
#include <QTimer>

class DigitalClock : public QObject
{
    Q_OBJECT
public:
    DigitalClock(QWidget* parent = nullptr);

    QTime* getElapsedTime() const;
    void stop();


public slots:
    void showTime();
    void restart();


signals:
    void valueChanged();
    void onRestart();


private:
    QWidget* parent_;
    QTimer* timer;
    QTime* time;
};

#endif // DIGITALCLOCK_HH
