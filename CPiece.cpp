#include "CPiece.h"
#include <cmath>

CPiece::CPiece() :
    m_Coordinate() {
    m_iID = 0;
    m_iSteps = 0;
}

CPiece::CPiece(int x, int y, ChessPieceType_e type, PlayerSide_e side, int index) :
    m_Coordinate(x, y) {
    m_iSteps = 0;
    m_eSide = side;
    m_eType = type;
    m_iID = m_eSide * 100 + m_eType * 10 + index;
    m_bAlive = true;
}

CPiece::~CPiece() {

}

int CPiece::GetID() {
    return m_iID;
}

int CPiece::GetID() const {
    return m_iID;
}

CCoordinate CPiece::GetCoordinate() {
    return m_Coordinate;
}

CCoordinate CPiece::GetCoordinate() const {
    return m_Coordinate;
}

PlayerSide_e CPiece::GetSide() {
    return m_eSide;
}

PlayerSide_e CPiece::GetSide() const {
    return m_eSide;
}

ChessPieceType_e CPiece::GetType() {
    return m_eType;
}

ChessPieceType_e CPiece::GetType() const {
    return m_eType;
}

CCoordinatesSet CPiece::GetCheckmateCoordinates() {
    return m_vCheckmateCoordinates;
}

CCoordinatesSet CPiece::GetCheckmateCoordinates() const {
    return m_vCheckmateCoordinates;
}

CCoordinatesSet CPiece::GetNextMoves() {
    return m_vNextMoves;
}

CCoordinatesSet CPiece::GetNextMoves() const {
    return m_vNextMoves;
}

bool CPiece::GetAlive() {
    return m_bAlive;
}

bool CPiece::GetAlive() const {
    return m_bAlive;
}

bool CPiece::Move(CCoordinate newCrd) {
    int x = newCrd.GetXCoordinate();
    int y = newCrd.GetYCoordinate();

    if (m_vNextMoves.Contains(newCrd)) {

        if (pGame->m_iaBoard[x][y] != 0) {
            pGame->KillPiece(pGame->m_iaBoard[x][y]);
        }        
        pGame->m_iaBoard[m_Coordinate.GetXCoordinate()][m_Coordinate.GetYCoordinate()] = 0;
        m_Coordinate.Reset(x, y);
        pGame->m_iaBoard[x][y] = m_iID;

        m_iSteps++;
        Notify();
        return true;
    }
    else {
        return false;
    }

}

void CPiece::BeKilled() {
    m_bAlive = false;
    Notify();
}

void CPiece::ComputeEffectiveNextMoves() {
    int x = m_Coordinate.GetXCoordinate();
    int y = m_Coordinate.GetYCoordinate();
    int movement = ((m_eSide == RED)? -1: 1);

    int (*p)[14] = pGame->m_iaBoard;

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

void CPiece::ComputeCheckmateCoordinates() {
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
            while (pGame->m_iaBoard[x][i] >= 0) {
                if (pGame->m_iaBoard[x][i] == 0) {
                    if (flag == true)
                        m_vCheckmateCoordinates.AddInPalace(CCoordinate(x, i));
                }
                else {
                    if (flag == false)
                        flag = true;
                    else {
                        if ((pGame->m_iaBoard[x][i] / 100) == (3 - m_eSide))
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
                    if (pGame->m_iaBoard[i][y] == 0) {
                        if (flag == true)
                            m_vCheckmateCoordinates.AddInPalace(CCoordinate(i, y));
                    }
                    else {
                        if (flag == false)
                            flag = true;
                        else {
                            if ((pGame->m_iaBoard[i][y] / 100) == (3 - m_eSide))
                                m_vCheckmateCoordinates.AddInPalace(CCoordinate(i, y));
                            break;
                        }
                    }
                }
            }
            else if (x >= 7 && x <= 10) {
                for (int i = x - 1; i >= 5; i--) {
                    if (pGame->m_iaBoard[i][y] == 0) {
                        if (flag == true)
                            m_vCheckmateCoordinates.AddInPalace(CCoordinate(i, y));
                    }
                    else {
                        if (flag == false)
                            flag = true;
                        else {
                            if ((pGame->m_iaBoard[i][y] / 100) == (3 - m_eSide))
                                m_vCheckmateCoordinates.AddInPalace(CCoordinate(i, y));
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
                if (pGame->m_iaBoard[x][i] != 0)
                    break;
            }
        }
        else {
            for (; i <= 8; i++) {
                if (pGame->m_iaBoard[x][i] != 0)
                    break;
            }
        }

        if (i == 4 || i == 9) {
            while (pGame->m_iaBoard[x][i] == 0) {
                m_vCheckmateCoordinates.Add(CCoordinate(x, i));
                i = i + delta;
            }
        }
    }


    else
        return;
}
