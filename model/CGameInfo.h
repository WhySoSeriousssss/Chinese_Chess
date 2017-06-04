#ifndef CGAMEINFO_H
#define CGAMEINFO_H

#include "Common.h"

class CGameInfo {
public:
    CGameInfo();
    ~CGameInfo();

    // The game board
    int m_board[13][14];

    // THE player
    int m_side;

    // current round
    int m_CurrentRound;
};

extern CGameInfo *pGameInfo;

#endif // CGAMEINFO_H
