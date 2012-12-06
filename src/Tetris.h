#ifndef TETRIS_H
#define TETRIS_H

#include <QObject>
#include <QEvent>
#include <QTimer>
#include <BrickGlass.h>

#include <QDebug>

class Tetris : public QObject
{

    Q_OBJECT

    public:
                            Tetris()
        {

            this->active = false;

            this->timer.setInterval(1000);
            QObject::connect(&this->timer,SIGNAL(timeout()),this,SLOT(tick()));

        }
        QGraphicsScene*     getScene()
        {

            return this->glass.getScene();

        }

    public slots:
        void                gameStart()
        {

            this->glass.brickAdd();
            this->timer.start();
            this->active = true;

        }
        void                brickMoveLeft()
        {

            if (this->active)
                this->glass.brickMoveLeft();

        }
        void                brickMoveRight()
        {

            if (this->active)
                this->glass.brickMoveRight();

        }
        void                brickMoveDown()
        {

            if (this->active)
                this->glass.brickMoveDown();

        }
        void                brickDrop()
        {

            if (this->active)
                this->glass.brickDrop();

        }

    private:
        BrickGlass          glass;
        QTimer              timer;
        bool                active;

    private slots:
        void                tick()
        {

            if (!this->glass.brickMoveDown())
            {

                this->glass.brickAdd();

            }

        }

};

#endif // TETRIS_H
