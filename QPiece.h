#ifndef QPIECE_H
#define QPIECE_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QDebug>
#include "IObserver.h"
#include "CPiece_Model.h"
#include "Common.h"
#include "CGame_Model.h"

class QPiece : public QObject, public QGraphicsPixmapItem, public IObserver {
    Q_OBJECT
public:
    QPiece();
    QPiece(CPiece_Model *piece, int size);
    void SetPixmap(QString &file, int size);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //observer
    void Update();

    void ChangeIconOnSelection();

    bool Move(CCoordinate newCrd);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void isDead();
    void SelectPiece();
    void SendCoordinate(CCoordinate);

private:
    CPiece_Model *m_CPiece;

    int m_iX;
    int m_iY;

    PieceIconStyle_e m_eIconStyle;

    QString m_sIconFile;
    QString m_sIconFile_2;

    bool m_bIsSelected;

};

#endif // QPIECE_H
