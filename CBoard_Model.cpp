#include "CBoard_Model.h"

static CBoard_Model _board;
CBoard_Model *pBoard = &_board;

CBoard_Model::CBoard_Model() {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 14; j++) {
            if  (i <= 1 || i >= 11 || j <= 1 || j >= 12)
                m_iBoard[i][j] = -1;
            else
                m_iBoard[i][j] = 0;
        }
    }
}

CBoard_Model::~CBoard_Model() {

}

void CBoard_Model::Print() {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 13; j++)
            std::cout << m_iBoard[j][i] << "\t";
        std::cout << "\n";
    }
}
