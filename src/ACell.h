#ifndef ACELL_H
#define ACELL_H

#include <QPointF>
#include <QSizeF>
#include <QRectF>
#include <QList>

class ACell : public QPointF
{

    public:
                            ACell(qreal x, qreal y, QSizeF size)
                                :   QPointF(x,y),
                                    size(size)
        {

        }
        inline QPointF      getPoint() const
        {

            return QPointF(this->x(),this->y());

        }
        inline QSizeF       getSize() const
        {

            return this->size;

        }
        inline QRectF       getRect() const
        {

            return QRectF(QPointF(this->x(),this->y())*this->size.width(),this->size);

        }

    private:
        QSizeF  size;

};

typedef QList<ACell>        Cells;
typedef Cells::iterator     CellItr;

#endif // ACELL_H
