#include "CPlayer_Model.h"

CPlayer_Model::CPlayer_Model() :
    m_PKing(NULL){
    m_bIsCheckmated = false;
}

CPlayer_Model::CPlayer_Model(PlayerSide_e side) {
    m_eSide = side;
    m_bIsCheckmated = false;
}

CPlayer_Model::~CPlayer_Model() {
    delete m_PKing;
}

CCoordinate CPlayer_Model::GetKingPos() {
    return m_PKing->GetCoordinate();
}

void CPlayer_Model::SetKing(CPiece_Model *king) {
    m_PKing = king;
}

void CPlayer_Model::ComputeAllCheckmateCoordinates() {
    m_vAllCheckmateCoordinates.Clear();
    for (int i = 0; i < m_vPieces.size(); i++) {
        for (int j = 0; j < m_vPieces[i]->GetCheckmateCoordinates().Size(); j++)
            m_vAllCheckmateCoordinates.Add(m_vPieces[i]->GetCheckmateCoordinates().Get(j));
    }
    std::cout << m_eSide << ": ";
    m_vAllCheckmateCoordinates.Print();
}

bool CPlayer_Model::GetIsCheckmated() {
    return m_bIsCheckmated;
}

void CPlayer_Model::SetIsCheckmated(bool checkmate) {
    m_bIsCheckmated = checkmate;
}

CCoordinatesSet CPlayer_Model::GetAllCheckmateCoordinates() {
    return m_vAllCheckmateCoordinates;
}
