#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <QObject>
//класс описывающий вселенную
class Universe : public QObject
{
    Q_OBJECT

private:


public:
    explicit Universe(QObject *parent = 0);
    void paintGeneration();
    int cellSize = 5; //размер отрисованной клетки
    bool generation [100][100];//100 на 100 клеток с состоянием жив/мертв

signals:

public slots:
};

#endif // UNIVERSE_H
