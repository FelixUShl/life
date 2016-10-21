#include "widget.h"
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    now = new Universe (this);
    timer = new QTimer(this);
    this->setFixedSize(510, 550);
    startButton->setGeometry(300, 510, 60, 30);
    pauseButton->setGeometry(370, 510, 60, 30);
    stopButton->setGeometry(440, 510, 60, 30);

    connect(startButton, SIGNAL (released()),
            this, SLOT (liveCicle()));

    connect(stopButton, SIGNAL (released()),
                timer, SLOT (stop()));



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

void Widget::mouseReleaseEvent(QMouseEvent *event)//реакция на клик мыши
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

void Widget::liveCicle()//включается таймер и перерисовка поколений
{
    connect(timer, SIGNAL(timeout()), this, SLOT(pressedStart()));
    timer->start(500);
}

void Widget::pressedStart()
{
    next = new Universe ();

    for (int i = 0; i < 100; i++) // создание нового поколения
    {
        for (int j = 0; j < 100; j++ )
        {
            int checkNeighbor = 0; //ключ отслеживания соседей

            for (int i1 = -1; i1 <= 1; i1++) //ищем живых соседей, считаем их
            {
                for (int j1 = -1; j1 <= 1; j1++)
                {
                    if (i1!= 0 && j1 != 0)
                    {
                        if (this->now->generation[i+i1][j+j1]) checkNeighbor++; //
                    }
                }
            }
            if (checkNeighbor < 2 || checkNeighbor > 3) this->next->generation[i][j] = false;
        }
    }
    for (int i = 0; i < 100; i++) // копирование нового поколения в старое
    {
        for (int j = 0; j < 100; j++ )
        {
           this->now->generation[i][j]=this->next->generation[i][j];
        }
    }
    this->update();
}

