#ifndef ACELLOBJECT_H
#define ACELLOBJECT_H

#include <QGraphicsObject>
#include <QPainter>
#include <QFile>
#include <QXmlStreamReader>
#include <ACell.h>

#include <QDebug>

class ACellObject : public QGraphicsObject
{

    public:
                                ACellObject(QString xmlCells)
        {

            this->cells = ACellObject::cellsLoad(xmlCells);
            this->GeometryUpdate();

        }
        virtual QRectF          boundingRect() const
        {

            return this->calculatedRect;

        }
        virtual QPainterPath    shape() const
        {

            return this->calculatedShape;

        }
        virtual void            paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
        {

            CellItr cellItr;

            for (cellItr=this->cells.begin() ; cellItr!=this->cells.end() ; cellItr++)
            {

                painter->drawRect((*cellItr).getRect());

            }

    }

    private:
        Cells                   cells;
        QRectF                  calculatedRect;
        QPainterPath            calculatedShape;
        void                    GeometryUpdate()
        {

            CellItr cellItr;
            QPointF pTopLeft;
            QPointF pBottomRight;

            for (cellItr=this->cells.begin() ; cellItr!=this->cells.end() ; cellItr++)
            {

                ACell cell = *cellItr;
                QPointF cellTopLeft(cell.getPoint()*cell.getSize().width());
                QPointF cellBottomRight(cellTopLeft+QPointF(cell.getSize().width(),cell.getSize().width()));

                pTopLeft.rx() = cellTopLeft.x()<pTopLeft.x() ? cellTopLeft.x() : pTopLeft.x();
                pTopLeft.ry() = cellTopLeft.y()<pTopLeft.y() ? cellTopLeft.y() : pTopLeft.y();

                pBottomRight.rx() = cellBottomRight.x()>pBottomRight.x() ? cellBottomRight.x() : pBottomRight.x();
                pBottomRight.ry() = cellBottomRight.y()>pBottomRight.y() ? cellBottomRight.y() : pBottomRight.y();

                this->calculatedShape.addRect(QRectF(cellTopLeft+QPointF(0.1,0.1),cellBottomRight-QPointF(0.1,0.1)));

            }

            this->calculatedRect = QRectF(pTopLeft,pBottomRight);

        }
        static Cells            cellsLoad(QString file)
        {

            Cells cells;
            QFile xmlFile(file);

            if (xmlFile.open(QIODevice::ReadOnly|QIODevice::Text))
            {

                QXmlStreamReader xmlReader(&xmlFile);

                while(!xmlReader.atEnd() && !xmlReader.hasError())
                {

                    QXmlStreamReader::TokenType tokenType = xmlReader.readNext();

                    if(tokenType == QXmlStreamReader::StartElement)
                    {

                        if(xmlReader.name() == "cell")
                        {

                            int cellX = xmlReader.attributes().value("x").toString().toInt();
                            int cellY = xmlReader.attributes().value("y").toString().toInt();
                            int cellSize = xmlReader.attributes().value("size").toString().toInt();

                            cells.push_back(ACell(cellX,cellY,QSizeF(cellSize,cellSize)));

                        }

                    }

                }

                xmlReader.clear();
                xmlFile.close();

            }

            return cells;

        }
};

#endif // ACELLOBJECT_H
