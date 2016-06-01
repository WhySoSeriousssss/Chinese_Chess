#include "QPiece.h"

QPiece::QPiece() {

}

QPiece::QPiece(CPiece_Model *piece, int size) :
    m_CPiece(piece) {
    m_sIconFile = QString::number(m_CPiece->GetID() / 10 * 10);
    m_sIconFile_2 = m_sIconFile + "_2";

    SetPixmap(m_sIconFile, size);

    m_iX = m_CPiece->GetCoordinate().GetXCoordinate() - 2;
    m_iY = m_CPiece->GetCoordinate().GetYCoordinate() - 2;
    this->setPos(C_X + m_iX * C_DELTA, C_Y + m_iY * C_DELTA);

    m_bIsSelected = false;
}

void QPiece::SetPixmap(QString &file, int size) {
    QPixmap pixmap;
    QString path = "../Chinese_Chess/Images/DELICATE/" + file;
    pixmap.load(path);
    pixmap = pixmap.scaled(size, size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);

}

QRectF QPiece::boundingRect() const {
 //   QRect rect = this->pixmap().rect();
    return QRectF(0, 0, C_ICONSIZE, C_ICONSIZE);
}

void QPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap = this->pixmap();
    //QRect rect = pixmap.rect();

    painter->drawPixmap(0, 0, C_ICONSIZE, C_ICONSIZE, pixmap);
}

void QPiece::Update() {
    if (m_CPiece->GetAlive() == false)
        emit isDead();
    m_iX = m_CPiece->GetCoordinate().GetXCoordinate() - 2;
    m_iY = m_CPiece->GetCoordinate().GetYCoordinate() - 2;
    this->setPos(C_X + m_iX * C_DELTA, C_X + m_iY * C_DELTA);

}


void QPiece::ChangeIconOnSelection() {
    m_bIsSelected = !m_bIsSelected;

    QPixmap pixmap;
    if (m_bIsSelected) {
        pixmap.load("../Chinese_Chess/Images/DELICATE/" + m_sIconFile_2);
    }
    else {
        pixmap.load("../Chinese_Chess/Images/DELICATE/" + m_sIconFile);
    }
    pixmap = pixmap.scaled(C_ICONSIZE, C_ICONSIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}

bool QPiece::Move(CCoordinate newCrd) {
    return m_CPiece->Move(newCrd);
}

void QPiece::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    if (m_CPiece->GetSide() == pGame->m_eCurrentRound) {
        emit SelectPiece();
    }
    else {
        emit SendCoordinate(m_CPiece->GetCoordinate());
    }
}
