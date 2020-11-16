#include "wire.h"
#include "scenecad.h"

Wire::Wire(QLineF line, QGraphicsItem *parent) :QGraphicsLineItem(line, parent)
{
    setFlags(QGraphicsItem ::ItemIsMovable |
             QGraphicsItem ::ItemIsSelectable |
             QGraphicsItem ::ItemSendsGeometryChanges);
    setPen(QPen(Qt::black, 1, Qt::SolidLine ,Qt::RoundCap, Qt::MiterJoin));
}

QVariant Wire::itemChange(GraphicsItemChange change, const QVariant &value)
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


