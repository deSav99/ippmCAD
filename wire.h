#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>

class Wire : public QGraphicsLineItem
{
public:
    Wire(QLineF line, QGraphicsItem *parent = nullptr);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // WIRE_H
