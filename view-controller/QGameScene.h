#ifndef QGAMESCENE_H
#define QGAMESCENE_H

#include <QGraphicsScene>
#include "view-controller/QPiece.h"
#include "view-controller/QBoard.h"
#include <vector>
#include "model/CGame.h"

class QGameScene : public QGraphicsScene, public IObserver {
    Q_OBJECT
public:
    explicit QGameScene(QObject *parent = 0);
    ~QGameScene();

    //observer
    void Update();
protected:


private slots:
    void RemovePieces();
    void RecordSelectedPiece();
    void GenerateMovement(CCoordinate crd);

private:
    std::vector<QPiece *> m_vPiecesItemRed;
    std::vector<QPiece *> m_vPiecesItemBlack;

    bool m_bPieceIsSelected;

    QPiece *m_SelectedPiece;

    QBoard* m_GameBoard;
};

#endif // QGAMESCENE_H
