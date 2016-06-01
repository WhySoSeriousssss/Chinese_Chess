#include "CGame.h"

static CGame _game;
CGame *pGame = &_game;

CGame::CGame() {
    m_eCurrentRound = RED;

    //initialize the board array
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 14; j++) {
            if  (i <= 1 || i >= 11 || j <= 1 || j >= 12)
                m_iaBoard[i][j] = -1;
            else
                m_iaBoard[i][j] = 0;
        }
    }
}

CGame::~CGame() {
    delete players[0];
    delete players[1];
}

void CGame::Initialize() {
    players[0] = new CPlayer(RED);
    players[1] = new CPlayer(BLACK);

    pugi::xml_document doc;
    doc.load_file("../Chinese_Chess/initial-board.xml");
    pugi::xml_node root = doc.child("game").child("board");

    for (pugi::xml_node pieceNode = root.first_child(); pieceNode; pieceNode = pieceNode.next_sibling()) {
        int x = XMLParseInt(pieceNode.attribute("x"));
        int y = XMLParseInt(pieceNode.attribute("y"));
        ChessPieceType_e type = ChessPieceType_e(XMLParseInt(pieceNode.attribute("type")));
        PlayerSide_e side = PlayerSide_e(XMLParseInt(pieceNode.attribute("side")) + 1);

        CPiece *piece = new CPiece(x, y, type, side, XMLParseInt(pieceNode.attribute("index")));

        if (type == KING)
            players[side - 1]->SetKing(piece);

        players[side - 1]->m_vPieces.push_back(piece);
        m_iaBoard[x][y] = piece->GetID();
    }
    RefreshPiecesData();
}

void CGame::KillPiece(int id) {
    int n = (int)(id / 100 - 1);
    for (int i = 0; i < players[n]->m_vPieces.size(); i++) {
        if (id == players[n]->m_vPieces[i]->GetID()) {
            players[n]->m_vPieces[i]->BeKilled();
            break;
        }
    }
}

void CGame::RefreshPiecesData() {
    for (int i = 0; i < players[0]->m_vPieces.size(); i++) {
        players[0]->m_vPieces[i]->ComputeEffectiveNextMoves();
        players[0]->m_vPieces[i]->ComputeCheckmateCoordinates();
    }
    players[0]->ComputeAllCheckmateCoordinates();

    for (int i = 0; i < players[1]->m_vPieces.size(); i++) {
        players[1]->m_vPieces[i]->ComputeEffectiveNextMoves();
        players[1]->m_vPieces[i]->ComputeCheckmateCoordinates();
    }
    players[1]->ComputeAllCheckmateCoordinates();
}

void CGame::ChangeTurn() {
    m_eCurrentRound = PlayerSide_e(3 - m_eCurrentRound);
}

//return if the king's coordinate is in the opponent's AllCheckmateCoordinates
bool CGame::PlayerIsCheckmated(PlayerSide_e player) {
    return (players[2 - player]->GetAllCheckmateCoordinates().Contains(players[player - 1]->GetKingPos()));
}

void CGame::DetectCheckmate() {
    if (PlayerIsCheckmated(RED)) {
        std::cout << "RED is checkmated!\n";
    }
    if (PlayerIsCheckmated(BLACK)) {
        std::cout << "BLACK is checkmated!\n";
    }
}

std::vector<CPiece *> CGame::GetPiecesRed() {
    return players[0]->m_vPieces;
}

std::vector<CPiece *> CGame::GetPiecesBlack() {
    return players[1]->m_vPieces;
}
