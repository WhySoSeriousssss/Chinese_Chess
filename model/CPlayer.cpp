#include "model/CPlayer.h"

CPlayer::CPlayer() :
    m_PKing(NULL) {
    m_bIsInCheck = false;
}

CPlayer::CPlayer(PlayerSide_e side) :
    m_PKing(NULL) {
    m_eSide = side;
    m_bIsInCheck = false;
}

CPlayer::~CPlayer() {
    delete m_PKing;
}

CCoordinate CPlayer::GetKingPos() {
    return m_PKing->GetCoordinate();
}

void CPlayer::SetKing(CPiece *king) {
    m_PKing = king;
}

void CPlayer::ComputeAllCheckCoordinates() {
    m_vAllCheckCoordinates.Clear();
    for (int i = 0; i < m_vPieces.size(); i++) {
        if (m_vPieces[i]->GetAlive() == true) {
            for (int j = 0; j < m_vPieces[i]->GetCheckCoordinates().Size(); j++)
                m_vAllCheckCoordinates.Add(m_vPieces[i]->GetCheckCoordinates().Get(j));
        }
    }

    std::cout << m_eSide << ": ";
    m_vAllCheckCoordinates.Print();
}

bool CPlayer::GetIsInCheck() {
    return m_bIsInCheck;
}

void CPlayer::SetIsInCheck(bool check) {
    m_bIsInCheck = check;
}

CCoordinatesSet CPlayer::GetAllCheckCoordinates() {
    return m_vAllCheckCoordinates;
}

void CPlayer::AddPiece(CPiece *piece) {
    m_vPieces.push_back(piece);
}

std::vector<CPiece *> CPlayer::GetPieces() {
    return m_vPieces;
}
