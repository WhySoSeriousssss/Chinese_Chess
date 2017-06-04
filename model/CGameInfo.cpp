#include "model/CGameInfo.h"

static CGameInfo _gameinfo;
CGameInfo *pGameInfo = &_gameinfo;

CGameInfo::CGameInfo() {
    m_CurrentRound = 0;

    //initialize the board array
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 14; j++) {
            if  (i <= 1 || i >= 11 || j <= 1 || j >= 12)
                m_board[i][j] = -1;
            else
                m_board[i][j] = 0;
        }
    }
}

CGameInfo::~CGameInfo() {

}
