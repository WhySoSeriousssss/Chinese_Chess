#ifndef CPLAYER_MODEL_H
#define CPLAYER_MODEL_H

#include "Common.h"
#include "CPiece_Model.h"
#include "CCoordinatesSet.h"
#include <vector>

class CPiece_Model;

class CPlayer_Model {
public:
    CPlayer_Model();
    CPlayer_Model(PlayerSide_e side);
    ~CPlayer_Model();

    CCoordinate GetKingPos();
    void SetKing(CPiece_Model *king);

    void ComputeAllCheckmateCoordinates();
    CCoordinatesSet GetAllCheckmateCoordinates();

    bool GetIsCheckmated();
    void SetIsCheckmated(bool checkmate);

    std::vector<CPiece_Model *> m_vPieces;

private:
    PlayerSide_e m_eSide;

    CPiece_Model *m_PKing;

    bool m_bIsCheckmated;

    CCoordinatesSet m_vAllCheckmateCoordinates;

};

#endif // CPlayer_Model_H
