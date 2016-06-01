#ifndef CGAME_MODEL_H
#define CGAME_MODEL_H

#include "CPlayer_Model.h"
#include "CPiece_Model.h"
#include "CBoard_Model.h"
#include <vector>

class CPlayer_Model;

class CGame_Model {
public:
    CGame_Model();
    ~CGame_Model();

    void Initialize();

    void KillPiece(int id);
    void RefreshPiecesData();
    void ChangeTurn();

    bool PlayerIsCheckmated(PlayerSide_e player);

    void DetectCheckmate();

    std::vector<CPiece_Model *> GetPiecesRed();
    std::vector<CPiece_Model *> GetPiecesBlack();

    PlayerSide_e m_eCurrentRound;

private:

    CPlayer_Model* players[2];
};

extern CGame_Model *pGame;
#endif // CGame_Model_H
