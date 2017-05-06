#ifndef CGAME_H
#define CGAME_H

#include "model/CPlayer.h"
#include "ISubject.h"
#include <vector>
#include "include/pugixml.hpp"
#include "util.h"

class CPlayer;
class CPiece;

class CGame : public ISubject {
public:
/// member functions
    CGame();
    ~CGame();

    void Initialize();

    void Save();
    void Load();

    void SetPieceStatus(int id, bool alive, bool test);
    void RefreshPiecesData();
    void ChangeTurn();

    bool PlayerIsInCheck(PlayerSide_e player);
    int DetectInCheck();
    int DetectCheckmate();

    std::vector<CPiece *> GetPiecesRed();
    std::vector<CPiece *> GetPiecesBlack();

/// member variables
    // the board array
    int m_iaBoard[13][14];
    // current round
    PlayerSide_e m_eCurrentRound;

private:
    CPlayer* players[2];

};

extern CGame *pGame;
#endif // CGAME_H
