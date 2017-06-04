#ifndef CPIECE_H
#define CPIECE_H

#include "Common.h"
#include "model/CGameInfo.h"
#include "model/CCoordinate.h"
#include <vector>

class CGame;
class CPlayer;

using namespace std;

class CPiece {
public:
    CPiece();
    CPiece(int x, int y, ChessPieceType_e type, int side, int index);
    ~CPiece();

    int GetID();
    int GetID() const;

    CCoordinate GetCoordinate();
    CCoordinate GetCoordinate() const;

    void SetCoordinate(int x, int y);

    int GetSide();
    int GetSide() const;

    ChessPieceType_e GetType();
    ChessPieceType_e GetType() const;

    vector<CCoordinate> GetNextMoves();
    vector<CCoordinate> GetNextMoves() const;

    vector<CCoordinate> GetCheckCoordinates();
    vector<CCoordinate> GetCheckCoordinates() const;

    void SetAlive(bool alive);
    bool GetAlive();
    bool GetAlive() const;

    void AddMoves();

    //
    void ComputeEffectiveNextMoves();
    void ComputeCheckCoordinates();

private:
    //unique piece id
    int m_iID;

    //piece's current x, y coordinates
    CCoordinate m_Coordinate;

    //the set of all possible next moves of that piece
    vector<CCoordinate> m_vNextMoves;

    //the set of coordinates at which if the enemy's king is, then there will occur a check
    vector<CCoordinate> m_vCheckCoordinates;

    //piece type
    ChessPieceType_e m_eType;

    // side of the piece
    int m_iSide;

    int m_iMoves;

    //whether this piece is alive
    bool m_bAlive;

};


#endif // CPIECE_H
