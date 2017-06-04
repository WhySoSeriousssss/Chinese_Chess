#ifndef QBOARD_H
#define QBOARD_H

#include <QGraphicsPixmapItem>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QDebug>
#include "model/CCoordinate.h"

class QBoard : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    QBoard();
    QBoard(QString &file, int width, int height);
    ~QBoard();

    void SetPixmap(QString &file, int width, int height);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void SendCoordinate(int, int);

private:

};
#endif // QBOARD_H
