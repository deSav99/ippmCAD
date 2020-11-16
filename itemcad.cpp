#include "itemcad.h"
#include "scenecad.h"

ItemCAD::ItemCAD(TypeItem typeItem, QGraphicsItem *parent)
    :QGraphicsPolygonItem(parent)
{
    switch(typeItem)
    {
    case Element:
        myPolygon << QPoint(-40,-80) << QPoint(-40,-40)
                  << QPoint(-80,-40) << QPoint(-40,-40)
                  << QPoint(-40,40)<< QPoint(-80,40)
                  << QPoint(-40,40) << QPoint(-40,80)
                  << QPoint(40,80) << QPoint(40,0)
                  << QPoint(80,0) << QPoint(40,0)
                  << QPoint(40,-80) << QPoint(-40,-80);
        break;
    case In:
        myPolygon << QPoint(-40,-20) << QPoint(20,-20)
                  << QPoint(40,0) << QPoint(20,20)
                  << QPoint(-40,20) << QPoint(-40,-20);
        break;
    default:
        break;
    }
    setFlags(QGraphicsItem ::ItemIsMovable |
             QGraphicsItem ::ItemIsSelectable |
             QGraphicsItem ::ItemSendsGeometryChanges);

    setPen(QPen(Qt::black, 2));
    setPolygon(myPolygon);
}

QPixmap ItemCAD::image()
{
    QPixmap pixmap(250,250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 5));
    painter.translate(125,125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}


QString ItemCAD::nameItem(TypeItem typeItem)
{
    switch(typeItem)
    {
    case Element: return "Element";
    case In: return "In";
    default: return nullptr;
    }
}

QVariant ItemCAD::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene())
    {
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                qobject_cast<SceneCAD*>(scene()))
        {
            SceneCAD* customScene = qobject_cast<SceneCAD*>(scene());
            int gridSize = customScene->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}
