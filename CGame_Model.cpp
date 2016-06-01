#include "CGame_Model.h"

static CGame_Model _game;
CGame_Model *pGame = &_game;

CGame_Model::CGame_Model() {
    m_eCurrentRound = RED;
}

CGame_Model::~CGame_Model() {
    delete players[0];
    delete players[1];
}

void CGame_Model::Initialize() {
    players[0] = new CPlayer_Model(RED);
    players[1] = new CPlayer_Model(BLACK);

    pugi::xml_document doc;
    doc.load_file("../Chinese_Chess/initial-board.xml");
    pugi::xml_node root = doc.child("game").child("board");

    for (pugi::xml_node pieceNode = root.first_child(); pieceNode; pieceNode = pieceNode.next_sibling()) {
        int x = XMLParseInt(pieceNode.attribute("x"));
        int y = XMLParseInt(pieceNode.attribute("y"));
        ChessPieceType_e type = ChessPieceType_e(XMLParseInt(pieceNode.attribute("type")));
        PlayerSide_e side = PlayerSide_e(XMLParseInt(pieceNode.attribute("side")) + 1);

        CPiece_Model *piece = new CPiece_Model(x, y, type, side, XMLParseInt(pieceNode.attribute("index")));

        if (type == KING)
            players[side - 1]->SetKing(piece);

        players[side - 1]->m_vPieces.push_back(piece);
        pBoard->m_iBoard[x][y] = piece->GetID();
    }
    RefreshPiecesData();
}

void CGame_Model::KillPiece(int id) {
    int n = (int)(id / 100 - 1);
    for (int i = 0; i < players[n]->m_vPieces.size(); i++) {
        if (id == players[n]->m_vPieces[i]->GetID()) {
            players[n]->m_vPieces[i]->BeKilled();
            break;
        }
    }
}

void CGame_Model::RefreshPiecesData() {
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

void CGame_Model::ChangeTurn() {
    m_eCurrentRound = PlayerSide_e(3 - m_eCurrentRound);
}

//return if the king's coordinate is in the opponent's AllCheckmateCoordinates
bool CGame_Model::PlayerIsCheckmated(PlayerSide_e player) {
    return (players[2 - player]->GetAllCheckmateCoordinates().Contains(players[player - 1]->GetKingPos()));
}

void CGame_Model::DetectCheckmate() {
    if (PlayerIsCheckmated(RED)) {
        std::cout << "RED is checkmated!\n";
    }
    if (PlayerIsCheckmated(BLACK)) {
        std::cout << "BLACK is checkmated!\n";
    }
}

std::vector<CPiece_Model *> CGame_Model::GetPiecesRed() {
    return players[0]->m_vPieces;
}

std::vector<CPiece_Model *> CGame_Model::GetPiecesBlack() {
    return players[1]->m_vPieces;
}
