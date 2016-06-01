#include "CPlayer.h"

CPlayer::CPlayer() :
    m_PKing(NULL) {
    m_bIsCheckmated = false;
}

CPlayer::CPlayer(PlayerSide_e side) :
    m_PKing(NULL) {
    m_eSide = side;
    m_bIsCheckmated = false;
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

void CPlayer::ComputeAllCheckmateCoordinates() {
    m_vAllCheckmateCoordinates.Clear();
    for (int i = 0; i < m_vPieces.size(); i++) {
        for (int j = 0; j < m_vPieces[i]->GetCheckmateCoordinates().Size(); j++)
            m_vAllCheckmateCoordinates.Add(m_vPieces[i]->GetCheckmateCoordinates().Get(j));
    }
    std::cout << m_eSide << ": ";
    m_vAllCheckmateCoordinates.Print();
}

bool CPlayer::GetIsCheckmated() {
    return m_bIsCheckmated;
}

void CPlayer::SetIsCheckmated(bool checkmate) {
    m_bIsCheckmated = checkmate;
}

CCoordinatesSet CPlayer::GetAllCheckmateCoordinates() {
    return m_vAllCheckmateCoordinates;
}
