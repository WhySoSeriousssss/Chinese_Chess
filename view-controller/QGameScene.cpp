#include "view-controller/QGameScene.h"
#include "model/CMovement.h"

QGameScene::QGameScene(QObject *parent) :
    QGraphicsScene(parent),
    m_SelectedPiece(NULL),
    m_bPieceIsSelected(false){
    QString file = "../Chinese_Chess/Images/CANVAS.GIF";
    m_GameBoard = new QBoard(file, 377, 417);
    m_GameBoard->setPos(0, 0);
    addItem(m_GameBoard);
    connect(m_GameBoard, SIGNAL(SendCoordinate(CCoordinate)), this, SLOT(GenerateMovement(CCoordinate)));

    pGame->Initialize();

    std::vector<CPiece *> tempRed = pGame->GetPiecesRed();
    for (int i = 0; i < pGame->GetPiecesRed().size(); i++) {
        m_vPiecesItemRed.push_back( new QPiece(tempRed[i], C_ICONSIZE));
        addItem(m_vPiecesItemRed[i]);
        tempRed[i]->Attach(m_vPiecesItemRed[i]);

        connect(m_vPiecesItemRed[i], SIGNAL(SelectPiece()), this, SLOT(RecordSelectedPiece()));
        connect(m_vPiecesItemRed[i], SIGNAL(isDead()), this, SLOT(RemovePieces()));
        connect(m_vPiecesItemRed[i], SIGNAL(SendCoordinate(CCoordinate)), this, SLOT(GenerateMovement(CCoordinate)));
    }


    std::vector<CPiece *> tempBlack = pGame->GetPiecesBlack();
    for (int i = 0; i < tempRed.size(); i++) {
        m_vPiecesItemBlack.push_back( new QPiece(tempBlack[i], C_ICONSIZE));
        addItem(m_vPiecesItemBlack[i]);
        tempBlack[i]->Attach(m_vPiecesItemBlack[i]);

        connect(m_vPiecesItemBlack[i], SIGNAL(SelectPiece()), this, SLOT(RecordSelectedPiece()));
        connect(m_vPiecesItemBlack[i], SIGNAL(isDead()), this, SLOT(RemovePieces()));
        connect(m_vPiecesItemBlack[i], SIGNAL(SendCoordinate(CCoordinate)), this, SLOT(GenerateMovement(CCoordinate)));
    }

}

QGameScene::~QGameScene() {
    for (int i = 0; i < m_vPiecesItemBlack.size(); i++)
        delete m_vPiecesItemBlack[i];
    for (int i = 0; i < m_vPiecesItemRed.size(); i++)
        delete m_vPiecesItemRed[i];
    delete m_GameBoard;
}

void QGameScene::Update() {

}

void QGameScene::RemovePieces() {
    QPiece *_sender = qobject_cast<QPiece *>(QObject::sender());
    removeItem(_sender);
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

void QGameScene::GenerateMovement(CCoordinate crd) {
    if (m_bPieceIsSelected) {
        if (m_SelectedPiece->GetPiece()->AttemptsToMove(crd)) {
            int pieceid = m_SelectedPiece->GetPiece()->GetID();
            int x = crd.GetXCoordinate();
            int y = crd.GetYCoordinate();

            CMovement *move = new CMovement(pieceid, x, y);

            m_SelectedPiece->GetPiece()->Move(crd);
            m_SelectedPiece->ToggleIsSelected();
            m_SelectedPiece = NULL;
            m_bPieceIsSelected = false;
            pGame->ChangeTurn();
            pGame->DetectInCheck();
        }
    }
}
