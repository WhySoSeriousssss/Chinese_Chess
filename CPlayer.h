#ifndef CPLAYER_H
#define CPLAYER_H

#include "Common.h"
#include "CPiece.h"
#include "CCoordinatesSet.h"
#include <vector>

class CPiece;

class CPlayer {
public:
    CPlayer();
    CPlayer(PlayerSide_e side);
    ~CPlayer();

    CCoordinate GetKingPos();
    void SetKing(CPiece *king);

    void ComputeAllCheckmateCoordinates();
    CCoordinatesSet GetAllCheckmateCoordinates();

    bool GetIsCheckmated();
    void SetIsCheckmated(bool checkmate);

    std::vector<CPiece *> m_vPieces;

private:
    PlayerSide_e m_eSide;

    CPiece *m_PKing;

    bool m_bIsCheckmated;

    CCoordinatesSet m_vAllCheckmateCoordinates;

};

#endif // CPLAYER_H
