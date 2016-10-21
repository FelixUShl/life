#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    now = new Universe (this);

    this->setFixedSize(510, 550);
    startButton->setGeometry(300, 510, 60, 30);
    pauseButton->setGeometry(370, 510, 60, 30);
    stopButton->setGeometry(440, 510, 60, 30);

    connect(startButton, SIGNAL (released()),
            this, SLOT (pressedStart()));
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)//в какой момент ты отрабатываешь?????
{
    QPainter paint (this);
   // clear(paint);
    paintGeneration(&paint, now);


}

void Widget::paintGeneration(QPainter *paint, Universe *universe)//отрисовка поколения
{

   for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++ )
        {
            if (universe->generation[i][j])//клетка живая - закрасим черным
            {
                paint->setBrush(QBrush(Qt::black,Qt::SolidPattern));
                paint->setPen(QPen(Qt::black,1, Qt::SolidLine));
            }
            else //клетка мертвый - закрашивать не будем
            {
                paint->setBrush(QBrush(Qt::NoBrush));
                paint->setPen(QPen(Qt::black, Qt::SolidLine));

            };
            paint->drawRect(i*universe->cellSize+5, j*universe->cellSize+5, universe->cellSize, universe->cellSize);
        }
    }
    paint->end();

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    setCellCoords(event);
    update();

}

void Widget::setCellCoords(QMouseEvent *event)
{
    int dx, dy;

    dx = (event->x()-5)/now->cellSize;
    dy = (event->y()-5)/now->cellSize;

    if (dx<=500 && dy<=500)
    {
        this->now->generation[dx][dy] = !this->now->generation[dx][dy];

    };
}

void Widget::liveCicle()
{



}

void Widget::pressedStart()
{
    int x = 1;
    while (x > 0)
        {
            for (int i = 0; i < 100; i++)
             {
                 for (int j = 0; j < 100; j++ )
                 {this->now->generation[i][j] = !this->now->generation[i][j];}
            };
            update();


        }
}

void Widget::pressedStop()
{

}
