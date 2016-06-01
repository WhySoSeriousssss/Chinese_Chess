#ifndef CPIECE_H
#define CPIECE_H

#include "Common.h"
#include "CCoordinatesSet.h"
#include "CGame.h"
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

    CCoordinatesSet GetCheckmateCoordinates();
    CCoordinatesSet GetCheckmateCoordinates() const;

    bool GetAlive();
    bool GetAlive() const;

    //piece moves to the specific coordinate, kill any enemy piece on it if exists.
    bool Move(CCoordinate newCrd);

    void BeKilled();

    //
    void ComputeEffectiveNextMoves();
    void ComputeCheckmateCoordinates();

private:
    //piece's sole id
    int m_iID;

    //piece's current x, y coordinates
    CCoordinate m_Coordinate;

    //the set of all of this piece's next possible moves
    CCoordinatesSet m_vNextMoves;

    CCoordinatesSet m_vCheckmateCoordinates;

    //total steps this piece has moved
    int m_iSteps;

    //piece's type
    ChessPieceType_e m_eType;

    //which side does this piece belong to
    PlayerSide_e m_eSide;

    bool m_bAlive;

};


#endif // CPIECE_H
