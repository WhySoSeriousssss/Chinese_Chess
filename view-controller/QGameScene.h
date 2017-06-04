#ifndef QGAMESCENE_H
#define QGAMESCENE_H

#include <QGraphicsScene>
#include "view-controller/QPiece.h"
#include "view-controller/QBoard.h"
#include <vector>
#include "model/CPiece.h"
#include "model/CMovement.h"

using namespace std;

class QGameScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit QGameScene(QObject *parent = 0);
    ~QGameScene();

    void Initialize();

    void SetPiecesReference(vector<CPiece *> r, vector<CPiece *> b);

public slots:
    void RemovePiece(int id);
    void RecordSelectedPiece();
    void GenerateMovement(int x, int y);
    void ChangePiecePosition(CMovement *move);

signals:
    void SendMovement(CMovement*);

private:
    vector<CPiece *> m_vCPR;
    vector<CPiece *> m_vCPB;

    vector<QPiece *> m_vPiecesItemRed;
    vector<QPiece *> m_vPiecesItemBlack;

    bool m_bPieceIsSelected;

    QPiece *m_SelectedPiece;

    QBoard* m_GameBoard;
};

#endif // QGAMESCENE_H
