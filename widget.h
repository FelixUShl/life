#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "universe.h"
#include "QPainter"
#include "QPushButton"
#include "QMouseEvent"


class Widget : public QWidget
{
    Q_OBJECT

public:
    QTimer *timer;
    Universe *now;
    Universe *next;
    QPushButton *startButton = new QPushButton ("Старт", this);
    QPushButton *stopButton = new QPushButton ("Стоп", this);
    QPushButton *pauseButton = new QPushButton ("Пауза", this);

    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void paintGeneration(QPainter *paint, Universe *universe);
    void mouseReleaseEvent (QMouseEvent *event);
    void setCellCoords(QMouseEvent *event);

public slots:
    void pressedStart();
    void liveCicle();


};

#endif // WIDGET_H
