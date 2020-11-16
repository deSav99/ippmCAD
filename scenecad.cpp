#include "scenecad.h"

SceneCAD::SceneCAD(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{
    myMode = MoveItem;
    wire1 = nullptr;
    wire2 = nullptr;
}

void SceneCAD::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen(Qt::gray, 2);
    painter->setPen(pen);

    for(int i = gridSize; i < rect.right(); i += gridSize)
        for(int j = gridSize; j < rect.bottom(); j += gridSize)
            painter->drawPoint(i, j);

}

QPoint SceneCAD::binding(QPointF point)
{
    qreal xV = round(point.x()/gridSize)*gridSize;
    qreal yV = round(point.y()/gridSize)*gridSize;
    return QPoint(xV, yV);
//    return point.toPoint();
}

void SceneCAD::createWire(QPointF mousePos)
{
    if(!wire1)
    {
            wire1 = new Wire (QLineF(binding(mousePos),
                                     binding(mousePos)));
            wire2 = new Wire (QLineF(binding(mousePos),
                                     binding(mousePos)));

            wire1->setPen(QPen(QColor(0,0,0,80), 2, Qt::SolidLine ,
                               Qt::RoundCap, Qt::MiterJoin));
            wire2->setPen(QPen(QColor(0,0,0,80), 2, Qt::SolidLine ,
                               Qt::RoundCap, Qt::MiterJoin));

            addItem(wire1);
            addItem(wire2);
    }
    else
    {
        if(wire1->line().length() < gridSize &&
                wire1->line().length() < gridSize)
        {
            clearWire();
        }
        else
        {
            wire1->setPen(QPen(Qt::blue, 2, Qt::SolidLine ,
                               Qt::RoundCap, Qt::MiterJoin));
            wire1 = wire2;
            removeItem(wire2);
            wire2 = new Wire (QLineF(wire1->line().p2(),
                                     mousePos));
            wire2->setPen(QPen(QColor(0,0,0,80), 2, Qt::SolidLine ,
                               Qt::RoundCap, Qt::MiterJoin));

            addItem(wire1);
            addItem(wire2);
        }
    }

}

void SceneCAD::clearWire()
{
    removeItem(wire1);
    removeItem(wire2);
    delete [] wire1;
    delete [] wire2;
    wire1 = nullptr;
    wire2 = nullptr;
}

void SceneCAD::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
    {
        clearWire();
        return;
    }
    ItemCAD *item;
    switch(myMode)
    {
    case InsertItem:
        item = new ItemCAD(myTypeItem);
        textItem = new QGraphicsTextItem(item->nameItem(myTypeItem), item);

        textItem->setPos(item->boundingRect().bottomLeft());
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);

        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit insertItem();
        break;

    case InsertWire:
        createWire(mouseEvent->scenePos());

           break;
    default:
        break;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void SceneCAD::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(myMode == MoveItem)
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    else
        if(myMode == InsertWire )
        {
            if(wire1)
            {
                if(abs(binding(mouseEvent->scenePos()).x() - wire1->line().p1().x()) <=
                        abs(binding(mouseEvent->scenePos()).y() - wire1->line().p1().y()))
                {
                    QLineF newWire1(wire1->line().p1().x(), wire1->line().p1().y(),
                                    wire1->line().p1().x(), binding(mouseEvent->scenePos()).y());
                    wire1->setLine(newWire1);

                    QLineF newWire2(wire1->line().p2().x(), wire1->line().p2().y(),
                                    binding(mouseEvent->scenePos()).x(),wire1->line().p2().y());
                    wire2->setLine(newWire2);
                }
                else
                {
                    QLineF newWire1(wire1->line().p1().x(), wire1->line().p1().y(),
                                    binding(mouseEvent->scenePos()).x(), wire1->line().p1().y());
                    wire1->setLine(newWire1);

                    QLineF newWire2(wire1->line().p2().x(), wire1->line().p2().y(),
                                    wire1->line().p2().x(), binding(mouseEvent->scenePos()).y());
                    wire2->setLine(newWire2);
                }
            }
        }

    emit mouseMove(mouseEvent->scenePos());
}
