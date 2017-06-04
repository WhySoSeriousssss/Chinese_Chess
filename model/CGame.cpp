#include "model/CGame.h"
#include <QDebug>

CGame::CGame() {
    network = NULL;
}

CGame::~CGame() {
    delete players[0];
    delete players[1];
    delete network;
    delete receivedMovement;
}

void CGame::Initialize() {

    players[0] = new CPlayer(RED);
    players[1] = new CPlayer(BLACK);
    receivedMovement = new CMovement();

    pugi::xml_document doc;
    doc.load_file("../Chinese_Chess/initial-board.xml");
    pugi::xml_node root = doc.child("game").child("board");

    for (pugi::xml_node pieceNode = root.first_child(); pieceNode; pieceNode = pieceNode.next_sibling()) {
        int x = XMLParseInt(pieceNode.attribute("x"));
        int y = XMLParseInt(pieceNode.attribute("y"));
        ChessPieceType_e type = ChessPieceType_e(XMLParseInt(pieceNode.attribute("type")));
        int side = XMLParseInt(pieceNode.attribute("side"));

        CPiece *piece = new CPiece(x, y, type, side, XMLParseInt(pieceNode.attribute("index")));

        if (type == KING)
            players[side]->SetKing(piece);

        players[side]->AddPiece(piece);
        pGameInfo->m_board[x][y] = piece->GetID();
    }
    RefreshPiecesData();
}

void CGame::Save() {

}

void CGame::Load() {

}

void CGame::SetPieceStatus(int id, bool alive) {
    int n = (int)(id / 100 - 1);
    for (int i = 0; i < players[n]->GetPieces().size(); i++) {
        if (id == players[n]->GetPieces()[i]->GetID()) {
            players[n]->GetPieces()[i]->SetAlive(alive);
        }
    }
}

void CGame::RefreshPiecesData() {
    for (int i = 0; i < players[0]->GetPieces().size(); i++) {
        if (players[0]->GetPieces()[i]->GetAlive() == true) {
            players[0]->GetPieces()[i]->ComputeEffectiveNextMoves();
            players[0]->GetPieces()[i]->ComputeCheckCoordinates();
        }
    }
    players[0]->ComputeAllCheckCoordinates();

    for (int i = 0; i < players[1]->GetPieces().size(); i++) {
        if (players[1]->GetPieces()[i]->GetAlive() == true) {
            players[1]->GetPieces()[i]->ComputeEffectiveNextMoves();
            players[1]->GetPieces()[i]->ComputeCheckCoordinates();
        }
    }
    players[1]->ComputeAllCheckCoordinates();
}

void CGame::ChangeTurn() {
    pGameInfo->m_CurrentRound = 1 - pGameInfo->m_CurrentRound;
}

//return if the king's coordinate is in the opponent's AllCheckmateCoordinates
bool CGame::PlayerIsInCheck(int player) {
    for (int i = 0; i < players[1 - player]->GetAllCheckCoordinates().size(); i++) {
            if (players[player]->GetKingPos() == players[1 - player]->GetAllCheckCoordinates()[i])
                return true;
        }
    return false;
}

int CGame::DetectInCheck() {
    if (PlayerIsInCheck(0)) {
        return 0;
    }
    if (PlayerIsInCheck(1)) {
        return 1;
    }
    return 2;
}

int CGame::DetectCheckmate() {
    return 0;
}

vector<CPiece *> CGame::GetPiecesRed() {
    return players[0]->GetPieces();
}

vector<CPiece *> CGame::GetPiecesBlack() {
    return players[1]->GetPieces();
}

bool CGame::PieceAttemptsToMove(CMovement* move) {
    int pid = move->GetPieceID();
    int x = move->GetX();
    int y = move->GetY();
    CCoordinate newCrd(x, y);

    vector<CPiece *> pieces;
    CPiece *piece;

    if (pid / 100 == 1) { // red piece
        pieces = GetPiecesRed();
    }
    else { //black piece
        pieces = GetPiecesBlack();
    }
    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetID() == pid) {
            piece = pieces[i];
            break;
        }
    }
    int x0 = piece->GetCoordinate().GetX();
    int y0 = piece->GetCoordinate().GetY();

    bool check;

    for (int i = 0; i < piece->GetNextMoves().size(); i++) {
        if (newCrd == piece->GetNextMoves()[i]) {

            int original = pGameInfo->m_board[x][y];

            // ensure that move won't make the player himself get checkmated
            pGameInfo->m_board[x0][y0] = 0;
            pGameInfo->m_board[x][y] = pid;
            piece->GetCoordinate().Reset(x, y);
            if (original != 0) {
                // kill target piece for now
                SetPieceStatus(original, false);
            }
            RefreshPiecesData();

//            check = PlayerIsInCheck(pGameInfo->m_CurrentRound);
            check = false;
            pGameInfo->m_board[x0][y0] = pid;
            pGameInfo->m_board[x][y] = original;
            piece->GetCoordinate().Reset(x0, y0);
            if (original != 0) {
                // bring back target piece
                SetPieceStatus(original, true);
            }
            RefreshPiecesData();

            if (check) {
                return false;
            }
            else {
                return true;
            }
        }
    }
    return false;

}

void CGame::PieceMove(CMovement* move) {
    int pid = move->GetPieceID();
    int x = move->GetX();
    int y = move->GetY();
    int original = pGameInfo->m_board[x][y];

    vector<CPiece *> pieces;

    if (pid / 100 == 1) { // red piece
        pieces = GetPiecesRed();
    }
    else { //black piece
        pieces = GetPiecesBlack();
    }

    for (int i = 0; i < pieces.size(); i++) {
        if (pieces[i]->GetID() == pid) {
            int x0 = pieces[i]->GetCoordinate().GetX();
            int y0 = pieces[i]->GetCoordinate().GetY();
            pieces[i]->SetCoordinate(x, y);
            pieces[i]->AddMoves();
            pGameInfo->m_board[x0][y0] = 0;
            pGameInfo->m_board[x][y] = pid;
            if (original != 0) {
                SetPieceStatus(original, false);
                emit RemovePiece(original);
            }

            RefreshPiecesData();
            emit ChangePiecePosition(move);
            break;
        }
    }

}

// Game loop
void CGame::RunLoop() {
    while(true) {
        if (pGameInfo->m_side == pGameInfo->m_CurrentRound) {
            do {
                QEventLoop loop;
                connect(this, SIGNAL(MovementReceived()), &loop, SLOT(quit()));
                loop.exec();
            } while(PieceAttemptsToMove(receivedMovement) == false);
            PieceMove(receivedMovement);

            // send
            char movePack[7];
            receivedMovement->Serialize(movePack);
            network->Send(movePack, (int)sizeof(movePack));
       }

        else {
            // receive
            char movePack[7];
            network->Receive(movePack, (int)sizeof(movePack));
            receivedMovement->Deserialize(movePack);
            PieceMove(receivedMovement);
        }

        ChangeTurn();
//        DetectInCheck();
    }
}

void CGame::BindNetwork(NetworkConnect *n) {
    network = n;
    if (network ->GetIsServer())
        pGameInfo->m_side = 0;
    else
        pGameInfo->m_side = 1;
}

void CGame::ReceiveMovement(CMovement *movement) {
    receivedMovement = movement;
    emit MovementReceived();
}

void CGame::process() {
    RunLoop();
    emit finished();
}
