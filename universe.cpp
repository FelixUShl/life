#include "universe.h"

Universe::Universe(QObject *parent) : QObject(parent)
{
    for (int i = 0; i<100; i++)
    {
        for (int j = 0; j<100; j++)
        {
            this->generation[i][j] = false;
        }
    }
}
