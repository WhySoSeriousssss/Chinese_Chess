#ifndef CBOARD_MODEL_H
#define CBOARD_MODEL_H

#include "util.h"
#include "Common.h"
#include "CPiece_Model.h"
#include <vector>

class CPiece_Model;

class CBoard_Model {
public:
    CBoard_Model();
    ~CBoard_Model();

    void Print();

    int m_iBoard[13][14];

private:

};

extern CBoard_Model *pBoard;

#endif // CBoard_Model_H
