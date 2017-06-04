#ifndef CPLAYER_H
#define CPLAYER_H

#include "Common.h"
#include "model/CPiece.h"
#include <vector>

using namespace std;

class CPiece;

class CPlayer {
public:
    CPlayer();
    CPlayer(int side);
    ~CPlayer();

    CCoordinate GetKingPos();
    void SetKing(CPiece *king);

    void ComputeAllCheckCoordinates();
    vector<CCoordinate> GetAllCheckCoordinates();

    bool GetIsInCheck();
    void SetIsInCheck(bool check);

    void AddPiece(CPiece *piece);

    vector<CPiece *> GetPieces();

private:
    // player's side/color
    int m_iSide;

    // the collection of all pieces a player owns
    vector<CPiece *> m_vPieces;

    // pointer to the "King" piece
    CPiece *m_PKing;

    // whether the player is in check
    bool m_bIsInCheck;

    // the collection all checkmate coordiates
    vector<CCoordinate> m_vAllCheckCoordinates;

};

#endif // CPLAYER_H
