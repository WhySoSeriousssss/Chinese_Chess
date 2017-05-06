#ifndef CPIECE_H
#define CPIECE_H

#include "Common.h"
#include "model/CCoordinatesSet.h"
#include "model/CGame.h"
#include <vector>
#include "ISubject.h"

class CGame;
class CPlayer;

class CPiece : public ISubject {
public:
    CPiece();
    CPiece(int x, int y, ChessPieceType_e type, PlayerSide_e side, int index);
    ~CPiece();

    int GetID();
    int GetID() const;

    CCoordinate GetCoordinate();
    CCoordinate GetCoordinate() const;

    PlayerSide_e GetSide();
    PlayerSide_e GetSide() const;

    ChessPieceType_e GetType();
    ChessPieceType_e GetType() const;

    CCoordinatesSet GetNextMoves();
    CCoordinatesSet GetNextMoves() const;

    CCoordinatesSet GetCheckCoordinates();
    CCoordinatesSet GetCheckCoordinates() const;

    void SetAlive(bool alive);
    bool GetAlive();
    bool GetAlive() const;

    bool AttemptsToMove(CCoordinate newCrd);
    void Move(CCoordinate newCrd);

    //
    void ComputeEffectiveNextMoves();
    void ComputeCheckCoordinates();

private:
    //unique piece id
    int m_iID;

    //piece's current x, y coordinates
    CCoordinate m_Coordinate;

    //the set of all possible next moves of that piece
    CCoordinatesSet m_vNextMoves;

    //the set of coordinates at which if the enemy's king is, then there will occur a check
    CCoordinatesSet m_vCheckCoordinates;

    //total steps this piece has moved
    int m_iSteps;

    //piece type
    ChessPieceType_e m_eType;

    //which side does this piece belong to
    PlayerSide_e m_eSide;

    //whether this piece is alive
    bool m_bAlive;

};


#endif // CPIECE_H
