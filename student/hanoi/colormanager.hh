#ifndef COLORMANAGER_HH
#define COLORMANAGER_HH

#include <QObject>

class colorManager
{
public:
    colorManager();
    static QColor getRandomColor();
};

#endif // COLORMANAGER_HH
