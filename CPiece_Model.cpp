#include "CPiece_Model.h"
#include <cmath>

CPiece_Model::CPiece_Model() :
    m_Coordinate() {
    m_iID = 0;
    m_iSteps = 0;
}

CPiece_Model::CPiece_Model(int x, int y, ChessPieceType_e type, PlayerSide_e side, int index) :
    m_Coordinate(x, y) {
    m_iSteps = 0;
    m_eSide = side;
    m_eType = type;
    m_iID = m_eSide * 100 + m_eType * 10 + index;
    m_bAlive = true;
}

CPiece_Model::~CPiece_Model() {

}

int CPiece_Model::GetID() {
    return m_iID;
}

int CPiece_Model::GetID() const {
    return m_iID;
}

CCoordinate CPiece_Model::GetCoordinate() {
    return m_Coordinate;
}

CCoordinate CPiece_Model::GetCoordinate() const {
    return m_Coordinate;
}

PlayerSide_e CPiece_Model::GetSide() {
    return m_eSide;
}

PlayerSide_e CPiece_Model::GetSide() const {
    return m_eSide;
}

ChessPieceType_e CPiece_Model::GetType() {
    return m_eType;
}

ChessPieceType_e CPiece_Model::GetType() const {
    return m_eType;
}

CCoordinatesSet CPiece_Model::GetCheckmateCoordinates() {
    return m_vCheckmateCoordinates;
}

CCoordinatesSet CPiece_Model::GetCheckmateCoordinates() const {
    return m_vCheckmateCoordinates;
}

CCoordinatesSet CPiece_Model::GetNextMoves() {
    return m_vNextMoves;
}

CCoordinatesSet CPiece_Model::GetNextMoves() const {
    return m_vNextMoves;
}

bool CPiece_Model::GetAlive() {
    return m_bAlive;
}

bool CPiece_Model::GetAlive() const {
    return m_bAlive;
}

bool CPiece_Model::Move(CCoordinate newCrd) {
    int x = newCrd.GetXCoordinate();
    int y = newCrd.GetYCoordinate();

    if (m_vNextMoves.Contains(newCrd)) {

        if (pBoard->m_iBoard[x][y] != 0) {
            pGame->KillPiece(pBoard->m_iBoard[x][y]);
        }        
        pBoard->m_iBoard[m_Coordinate.GetXCoordinate()][m_Coordinate.GetYCoordinate()] = 0;
        m_Coordinate.Reset(x, y);
        pBoard->m_iBoard[x][y] = m_iID;

        m_iSteps++;
        Notify();
        return true;
    }
    else {
        return false;
    }

}

void CPiece_Model::BeKilled() {
    m_bAlive = false;
    Notify();
}

void CPiece_Model::ComputeEffectiveNextMoves() {
    int x = m_Coordinate.GetXCoordinate();
    int y = m_Coordinate.GetYCoordinate();
    int movement = ((m_eSide == RED)? -1: 1);

    int (*p)[14] = pBoard->m_iBoard;

    m_vNextMoves.Clear();

    switch (m_eType) {
    case CHARIOT:
        for (int i = x - 1; i >= 2; i--) {
            if (p[i][y] == 0)
                m_vNextMoves.Add(CCoordinate(i, y));
            else if (p[i][y] / 100 == m_eSide)
                break;
            else {
                m_vNextMoves.Add(CCoordinate(i, y));
                break;
            }
        }
        for (int i = x + 1; i <= 10; i++) {
            if (p[i][y] == 0)
                m_vNextMoves.Add(CCoordinate(i, y));
            else if (p[i][y] / 100 == m_eSide)
                break;
            else {
                m_vNextMoves.Add(CCoordinate(i, y));
                break;
            }
        }
        for (int i = y - 1; i >= 2; i--) {
            if (p[x][i] == 0)
                m_vNextMoves.Add(CCoordinate(x, i));
            else if (p[x][i] / 100 == m_eSide)
                break;
            else {
                m_vNextMoves.Add(CCoordinate(x, i));
                break;
            }
        }
        for (int i = y + 1; i <= 11; i++) {
            if (p[x][i] == 0)
                m_vNextMoves.Add(CCoordinate(x, i));
            else if (p[x][i] / 100 == m_eSide)
                break;
            else {
                m_vNextMoves.Add(CCoordinate(x, i));
                break;
            }
        }
        break;

    case HORSE:
        if (p[x - 1][y] == 0) {
            if (p[x - 2][y - 1] == 0 || (p[x - 2][y - 1]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 2, y - 1));
            if (p[x - 2][y + 1] == 0 || (p[x - 2][y + 1]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 2, y + 1));
        }
        if (p[x + 1][y] == 0) {
            if (p[x + 2][y - 1] == 0 || (p[x + 2][y - 1]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 2, y - 1));
            if (p[x + 2][y + 1] == 0 || (p[x + 2][y + 1]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 2, y + 1));
        }
        if (p[x][y + 1] == 0) {
            if (p[x - 1][y + 2] == 0 || (p[x - 1][y + 2]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 1, y + 2));
            if (p[x + 1][y + 2] == 0 || (p[x + 1][y + 2]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 1, y + 2));
        }
        if (p[x][y - 1] == 0) {
            if (p[x - 1][y - 2] == 0 || (p[x - 1][y - 2]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 1, y - 2));
            if (p[x + 1][y - 2] == 0 || (p[x + 1][y - 2]) / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 1, y - 2));
        }
        break;

    case ELEPHANT:
        if (p[x - 1][y - 1] == 0)
            if (p[x - 2][y - 2] == 0 || p[x - 2][y - 2] / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 2, y - 2));
        if (p[x - 1][y + 1] == 0)
            if (p[x - 2][y + 2] == 0 || p[x - 2][y + 2] / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 2, y + 2));
        if (p[x + 1][y + 1] == 0)
            if (p[x + 2][y + 2] == 0 || p[x + 2][y + 2] / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 2, y + 2));
        if (p[x + 1][y - 1] == 0)
            if (p[x + 2][y - 2] == 0 || p[x + 2][y - 2] / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 2, y - 2));
        break;

    case MANDARIN:
        if (p[x - 1][y - 1] == 0 || p[x - 1][y - 1] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x - 1, y - 1));
        if (p[x - 1][y + 1] == 0 || p[x - 1][y + 1] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x - 1, y + 1));
        if (p[x + 1][y + 1] == 0 || p[x + 1][y + 1] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x + 1, y + 1));
        if (p[x + 1][y - 1] == 0 || p[x + 1][y - 1] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x + 1, y - 1));
        break;

    case KING:
        if (p[x][y - 1] == 0 || p[x][y - 1] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x, y - 1));
        if (p[x][y + 1] == 0 || p[x][y + 1] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x, y + 1));
        if (p[x - 1][y] == 0 || p[x - 1][y] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x - 1, y));
        if (p[x + 1][y] == 0 || p[x + 1][y] / 100 == (3 - m_eSide))
            m_vNextMoves.AddInPalace(CCoordinate(x + 1, y));
        break;

    case CANNON: {
        bool flag = false;
        for (int i = x - 1; i >= 2; i--) {
            if (p[i][y] == 0) {
                if (flag == false)
                    m_vNextMoves.Add(CCoordinate(i, y));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[i][y] / 100) == (3 - m_eSide))
                        m_vNextMoves.Add(CCoordinate(i, y));
                    break;
                }
            }
        }
        flag = false;

        for (int i = x + 1; i <= 10; i++) {
            if (p[i][y] == 0) {
                if (flag == false)
                    m_vNextMoves.Add(CCoordinate(i, y));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[i][y] / 100) == (3 - m_eSide))
                        m_vNextMoves.Add(CCoordinate(i, y));
                    break;
                }
            }
        }
        flag = false;

        for (int i = y - 1; i >= 2; i--) {
            if (p[x][i] == 0) {
                if (flag == false)
                    m_vNextMoves.Add(CCoordinate(x, i));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[x][i] / 100) == (3 - m_eSide))
                        m_vNextMoves.Add(CCoordinate(x, i));
                    break;
                }
            }
        }
        flag = false;

        for (int i = y + 1; i <= 11; i++) {
            if (p[x][i] == 0) {
                if (flag == false)
                    m_vNextMoves.Add(CCoordinate(x, i));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[x][i] / 100) == (3 - m_eSide))
                        m_vNextMoves.Add(CCoordinate(x, i));
                    break;
                }
            }
        }

        break;
    }
    case PAWN:
        //after the pawn crosses the river, it also can move leftward or rightward
        if (m_iSteps >= 2) {
            if (p[x + 1][y] == 0 || p[x + 1][y] / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x + 1, y));
            if (p[x - 1][y] == 0 || p[x - 1][y] / 100 == (3 - m_eSide))
                m_vNextMoves.Add(CCoordinate(x - 1, y));
        }
        if (p[x][y + movement] == 0 || p[x][y + movement] / 100 == (3 - m_eSide))
            m_vNextMoves.Add(CCoordinate(x, y + movement));
        break;

    default:
        break;
    }

 //   m_vNextMoves.Print();
}

void CPiece_Model::ComputeCheckmateCoordinates() {
    m_vCheckmateCoordinates.Clear();
    int temp = (m_eSide == RED? 2: 9);
    int delta = (m_eSide == RED? -1: 1);

    if (m_eType == CHARIOT || m_eType == HORSE || m_eType == PAWN) {
        for (int i = 0; i < m_vNextMoves.Size(); i++) {
            int x = m_vNextMoves.Get(i).GetXCoordinate();
            int y = m_vNextMoves.Get(i).GetYCoordinate();

            if (x >= 5 && x <= 7 && y >= temp && y <= temp + 2)
                m_vCheckmateCoordinates.Add(CCoordinate(x, y));
        }
    }

    else if (m_eType == CANNON ) {
        int x = m_Coordinate.GetXCoordinate();
        int y = m_Coordinate.GetYCoordinate();
        bool flag = false;


        if (x >= 5 && x <= 7) {
            int i = y + delta;
            while (pBoard->m_iBoard[x][i] >= 0) {
                if (pBoard->m_iBoard[x][i] == 0) {
                    if (flag == true)
                        m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                }
                else {
                    if (flag == false)
                        flag = true;
                    else {
                        if ((pBoard->m_iBoard[x][i] / 100) == (3 - m_eSide))
                            m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                        break;
                    }
                }
                i += delta;
            }
        }

        else if (y >= temp && y <= temp + 2) {
            if (x >= 2 && x <= 5) {
                for (int i = x + 1; i <= 7; i++) {
                    if (pBoard->m_iBoard[x][i] == 0) {
                        if (flag == true)
                            m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                    }
                    else {
                        if (flag == false)
                            flag = true;
                        else {
                            if ((pBoard->m_iBoard[x][i] / 100) == (3 - m_eSide))
                                m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                            break;
                        }
                    }
                }
            }
            else if (x >= 7 && x <= 10) {
                for (int i = x - 1; i >= 5; i--) {
                    if (pBoard->m_iBoard[x][i] == 0) {
                        if (flag == true)
                            m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                    }
                    else {
                        if (flag == false)
                            flag = true;
                        else {
                            if ((pBoard->m_iBoard[x][i] / 100) == (3 - m_eSide))
                                m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                            break;
                        }
                    }
                }
            }
        }
        else
            return;
    }

    else if (m_eType == KING) {
        int x = m_Coordinate.GetXCoordinate();
        int y = m_Coordinate.GetYCoordinate();
        int i = y + delta;

        if (m_eSide == RED) {           
            for (; i >= 5; i--) {
                if (pBoard->m_iBoard[x][i] != 0)
                    break;
            }
        }
        else {
            for (; i <= 8; i++) {
                if (pBoard->m_iBoard[x][i] != 0)
                    break;
            }
        }

        if (i == 4 || i == 9) {
            while (pBoard->m_iBoard[x][i] == 0) {
                m_vCheckmateCoordinates.Add(CCoordinate(x, i));
                i = i + delta;
            }
        }
    }


    else
        return;
}
