#include "view-controller/QBoard.h"

QBoard::QBoard() {

}

QBoard::QBoard(QString &file, int width, int height) {
    SetPixmap(file, width, height);
}

QBoard::~QBoard() {

}

void QBoard::SetPixmap(QString &file, int width, int height) {
    QPixmap pixmap;
    pixmap.load(file);
    pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}

QRectF QBoard::boundingRect() const {
    return QRectF(0, 0, 377, 417);
}

void QBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();
    painter->drawPixmap(rect, pixmap);
}

void QBoard::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    int x = event->pos().x();
    int y = event->pos().y();
    emit SendCoordinate(CCoordinate((int)((x - 7) / 40 + 2), (int)((y - 7) / 40 + 2)));
}
