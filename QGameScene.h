#ifndef QGAMESCENE_H
#define QGAMESCENE_H

#include <QGraphicsScene>
#include "QPiece.h"
#include "QBoard.h"
#include <vector>
#include "CGame.h"

class QGameScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit QGameScene(QObject *parent = 0);
    ~QGameScene();

protected:


private slots:
    void RemovePieces();
    void RecordSelectedPiece();
    void PieceTriesToMove(CCoordinate crd);

private:
    std::vector<QPiece *> m_vPiecesItemRed;
    std::vector<QPiece *> m_vPiecesItemBlack;

    bool m_bPieceIsSelected;

    QPiece *m_SelectedPiece;

    QBoard* m_GameBoard;
};

#endif // QGAMESCENE_H
