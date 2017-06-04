#include "view-controller/QPiece.h"

QPiece::QPiece() {

}

QPiece::QPiece(CPiece *piece, int size) {
    m_sIconFile = QString::number(piece->GetID() / 10 * 10);
    m_sIconFile_2 = m_sIconFile + "_2";

    SetPixmap(m_sIconFile, size);

    m_iID = piece->GetID();
    m_iX = piece->GetCoordinate().GetX();
    m_iY = piece->GetCoordinate().GetY();
    m_iSide = piece->GetSide();

    this->setPos(C_X + (m_iX - 2) * C_DELTA, C_Y + (m_iY - 2) * C_DELTA);

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

int QPiece::GetID() {
    return m_iID;
}

int QPiece::GetX() {
    return m_iX;
}

int QPiece::GetY() {
    return m_iY;
}

void QPiece::SetPosition(int x, int y) {
    m_iX = x;
    m_iY = y;
    this->setPos(C_X + (m_iX - 2) * C_DELTA, C_X + (m_iY - 2) * C_DELTA);
}


void QPiece::ToggleIsSelected() {
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

void QPiece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if ((pGameInfo->m_side == pGameInfo->m_CurrentRound) && (m_iSide == pGameInfo->m_CurrentRound)) {
            emit SelectPiece();
    }
    else {
        emit SendCoordinate(m_iX, m_iY);
    }
}
