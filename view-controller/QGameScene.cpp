#include "view-controller/QGameScene.h"
#include <iostream>

QGameScene::QGameScene(QObject *parent) :
    QGraphicsScene(parent),
    m_SelectedPiece(NULL),
    m_bPieceIsSelected(false){

}

QGameScene::~QGameScene() {
    for (int i = 0; i < m_vPiecesItemBlack.size(); i++)
        delete m_vPiecesItemBlack[i];
    for (int i = 0; i < m_vPiecesItemRed.size(); i++)
        delete m_vPiecesItemRed[i];
    delete m_GameBoard;
}

void QGameScene::Initialize() {
    QString file = "../Chinese_Chess/Images/CANVAS.GIF";
    m_GameBoard = new QBoard(file, 377, 417);
    m_GameBoard->setPos(0, 0);
    addItem(m_GameBoard);
    connect(m_GameBoard, SIGNAL(SendCoordinate(int, int)), this, SLOT(GenerateMovement(int, int)));

    for (int i = 0; i < m_vCPR.size(); i++) {
        m_vPiecesItemRed.push_back( new QPiece(m_vCPR[i], C_ICONSIZE));
        addItem(m_vPiecesItemRed[i]);

        connect(m_vPiecesItemRed[i], SIGNAL(SelectPiece()), this, SLOT(RecordSelectedPiece()));
        connect(m_vPiecesItemRed[i], SIGNAL(SendCoordinate(int, int)), this, SLOT(GenerateMovement(int, int)));
    }


    for (int i = 0; i < m_vCPB.size(); i++) {
        m_vPiecesItemBlack.push_back( new QPiece(m_vCPB[i], C_ICONSIZE));
        addItem(m_vPiecesItemBlack[i]);

        connect(m_vPiecesItemBlack[i], SIGNAL(SelectPiece()), this, SLOT(RecordSelectedPiece()));
        connect(m_vPiecesItemBlack[i], SIGNAL(SendCoordinate(int, int)), this, SLOT(GenerateMovement(int, int)));
    }

}

void QGameScene::SetPiecesReference(vector<CPiece *> r, vector<CPiece *> b) {
    m_vCPR = r;
    m_vCPB = b;
}

void QGameScene::RemovePiece(int id) {
    vector<QPiece *> pieces;

    if (id / 100 == 1) { // red piece
        pieces = m_vPiecesItemRed;
    }
    else { //black piece
        pieces = m_vPiecesItemBlack;
    }
    vector<QPiece *>::iterator it = pieces.begin();
    while (it != pieces.end()) {
        auto pos = it - pieces.begin();
        if (id == pieces[pos]->GetID()) {
            removeItem(pieces[pos]);
            pieces.erase(it);
            break;
        }
        it++;
    }
}

void QGameScene::RecordSelectedPiece() {
    QPiece *_sender = qobject_cast<QPiece *>(QObject::sender());
    if (m_bPieceIsSelected) {
        m_SelectedPiece->ToggleIsSelected();
        if (m_SelectedPiece == _sender) {
            m_SelectedPiece = NULL;
            m_bPieceIsSelected = false;
        }
        else {
            m_SelectedPiece = _sender;
            _sender->ToggleIsSelected();
        }
    }

    else {
        m_SelectedPiece = _sender;
        m_bPieceIsSelected = true;
        _sender->ToggleIsSelected();
    }
}

void QGameScene::GenerateMovement(int x, int y) {
    if (m_bPieceIsSelected) {
        int pieceid = m_SelectedPiece->GetID();

        CMovement *move = new CMovement(pieceid, x, y);

        m_SelectedPiece->ToggleIsSelected();
        m_SelectedPiece = NULL;
        m_bPieceIsSelected = false;

        emit SendMovement(move);
    }
}

void QGameScene::ChangePiecePosition(CMovement *move) {
    int pid = move->GetPieceID();
    int x = move->GetX();
    int y = move->GetY();

    vector<QPiece *> pieces;

    if (pid / 100 == 1) { // red piece
        pieces = m_vPiecesItemRed;
    }
    else { //black piece
        pieces = m_vPiecesItemBlack;
    }

    for (int i = 0; i < pieces.size(); i++) {
        if (pid == pieces[i]->GetID()) {
            pieces[i]->SetPosition(x, y);
            break;
        }
    }
}
