#include "colormanager.hh"
#include <QColor>

#include <cstdlib>


colorManager::colorManager()
{


}

QColor colorManager::getRandomColor()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    return QColor(r, g, b);
}



