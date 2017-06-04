#ifndef QPIECE_H
#define QPIECE_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include "model/CPiece.h"
#include "Common.h"

class CPiece;

class QPiece : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    QPiece();
    QPiece(CPiece *piece, int size);

    void SetPixmap(QString &file, int size);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int GetID();
    int GetX();
    int GetY();

    //observer
    void SetPosition(int x, int y);

    void ToggleIsSelected();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void SelectPiece();
    void SendCoordinate(int, int);

private:

    int m_iID;
    int m_iX;
    int m_iY;
    int m_iSide;

    PieceIconStyle_e m_eIconStyle;

    QString m_sIconFile;
    QString m_sIconFile_2;

    bool m_bIsSelected;

};

#endif // QPIECE_H
