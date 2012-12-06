#ifndef GLASS_H
#define GLASS_H

#include <QGraphicsScene>
#include <QList>
#include <Brick_O.h>

#include <QDebug>

typedef QList<Brick*> Bricks;
typedef Bricks::iterator BrickItr;

class BrickGlass
{

    public:
                            BrickGlass()
        {

            this->scene.setSceneRect(0,0,300,600);

        }
        QGraphicsScene*     getScene(void)
                            {

                                return &this->scene;

                            }
        void                brickAdd(void)
        {

            Brick_O* brick = new Brick_O;
            this->scene.addItem(brick);
            this->bricks.push_back(brick);

        }
        bool                brickMoveLeft(void)
        {

            return this->brickMoveBy(QPointF(-30,0));

        }
        bool                brickMoveRight(void)
        {

            return this->brickMoveBy(QPointF(30,0));

        }
        bool                brickMoveDown(void)
        {

            return this->brickMoveBy(QPointF(0,30));

        }
        void                brickDrop(void)
        {

            while (this->brickMoveDown())
            {


            }

        }

    private:
        QGraphicsScene      scene;
        Bricks              bricks;
        bool                brickMoveBy(QPointF delta)
        {

            Brick* brick = this->bricks.last();

            brick->moveBy(delta.x(),delta.y());

            if  (

                    !this->scene.collidingItems(brick).empty()
                        ||
                    brick->sceneBoundingRect().bottom() > this->scene.sceneRect().bottom()
                        ||
                    brick->sceneBoundingRect().left() < this->scene.sceneRect().left()
                        ||
                    brick->sceneBoundingRect().right() > this->scene.sceneRect().right()

                 )
            {

                brick->moveBy(-1*delta.x(),-1*delta.y());
                return false;

            }

            return true;

        }

};

#endif // GLASS_H
