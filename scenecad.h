#ifndef SCENECAD_H
#define SCENECAD_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "itemcad.h"
#include "wire.h"

class SceneCAD : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode{MoveItem, InsertItem, InsertWire};

    SceneCAD(const QRectF &sceneRect, QObject *parent = nullptr);

    int getGridSize(){return gridSize;}
public slots:
    void setMode(Mode mode) {myMode = mode;};
    void setItemType(ItemCAD::TypeItem type) {myTypeItem = type;};

signals:
    void mouseMove(QPointF mouseCoordinates);
    void insertItem();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *moseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *moseEvent);
    void createWire(QPointF mousePos);
    void clearWire();

private:
   Mode myMode;
   QPoint binding(QPointF point);
   ItemCAD::TypeItem myTypeItem;
   QGraphicsTextItem *textItem;
   const int gridSize = 20;
   Wire *wire1, *wire2;
   QPolygon polygonWire;
};

#endif // SCENECAD_H
