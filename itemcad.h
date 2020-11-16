#ifndef ITEMCAD_H
#define ITEMCAD_H

#include <QGraphicsItem>
#include <QPolygonF>
#include <QPixmap>
#include <QPainter>
#include <QApplication>


class ItemCAD : public QGraphicsPolygonItem
{
public:
    enum TypeItem{Element, In};

    ItemCAD(TypeItem typeItem, QGraphicsItem *parent = nullptr);

    TypeItem typeItem() const { return myTypeItem; }
    QPolygonF polygon() const { return myPolygon; }
    QPixmap image();
    QString nameItem(TypeItem typeItem);
    QGraphicsTextItem* setTextItem ();

private:
    TypeItem myTypeItem;
    QPolygonF myPolygon;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // ITEMCAD_H
