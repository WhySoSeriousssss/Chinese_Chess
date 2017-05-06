#ifndef CPLAYER_H
#define CPLAYER_H

#include "Common.h"
#include "model/CPiece.h"
#include "model/CCoordinatesSet.h"
#include <vector>

class CPiece;

class CPlayer {
public:
    CPlayer();
    CPlayer(PlayerSide_e side);
    ~CPlayer();

    CCoordinate GetKingPos();
    void SetKing(CPiece *king);

    void ComputeAllCheckCoordinates();
    CCoordinatesSet GetAllCheckCoordinates();

    bool GetIsInCheck();
    void SetIsInCheck(bool check);

    void AddPiece(CPiece *piece);

    std::vector<CPiece *> GetPieces();

private:
    // player's side/color
    PlayerSide_e m_eSide;

    // the collection of all pieces a player owns
    std::vector<CPiece *> m_vPieces;

    // pointer to the "King" piece
    CPiece *m_PKing;

    // whether the player is in check
    bool m_bIsInCheck;

    // the collection all checkmate coordiates
    CCoordinatesSet m_vAllCheckCoordinates;

};

#endif // CPLAYER_H
