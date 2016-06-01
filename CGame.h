#ifndef CGAME_H
#define CGAME_H

#include "CPlayer.h"
#include <vector>
#include "include/pugixml.hpp"
#include "util.h"

class CPlayer;
class CPiece;

class CGame {
public:
    CGame();
    ~CGame();

    //the board array
    int m_iaBoard[13][14];

    void Initialize();

    void KillPiece(int id);
    void RefreshPiecesData();
    void ChangeTurn();

    bool PlayerIsCheckmated(PlayerSide_e player);

    void DetectCheckmate();

    std::vector<CPiece *> GetPiecesRed();
    std::vector<CPiece *> GetPiecesBlack();

    PlayerSide_e m_eCurrentRound;

private:
    CPlayer* players[2];

};

extern CGame *pGame;
#endif // CGAME_H
