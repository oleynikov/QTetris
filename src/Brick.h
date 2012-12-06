#ifndef BRICK_H
#define BRICK_H

#include <ACellObject.h>

class Brick : public ACellObject
{

    public:
        Brick(QString xmlCells) : ACellObject(xmlCells)
        {

        }

};

#endif // BRICK_H
