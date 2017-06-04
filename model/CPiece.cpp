#include "model/CPiece.h"
#include <cmath>

CPiece::CPiece() :
    m_Coordinate() {
    m_iMoves = 0;
}

CPiece::CPiece(int x, int y, ChessPieceType_e type, int side, int index) :
    m_Coordinate(x, y) {
    m_eType = type;
    m_iSide = side;
    m_iID = (m_iSide + 1) * 100 + m_eType * 10 + index;
    m_iMoves = 0;
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

void CPiece::SetCoordinate(int x, int y) {
    m_Coordinate.Reset(x, y);
}

int CPiece::GetSide() {
    return m_iSide;
}

int CPiece::GetSide() const {
    return m_iSide;
}

ChessPieceType_e CPiece::GetType() {
    return m_eType;
}

ChessPieceType_e CPiece::GetType() const {
    return m_eType;
}

vector<CCoordinate> CPiece::GetCheckCoordinates() {
    return m_vCheckCoordinates;
}

vector<CCoordinate> CPiece::GetCheckCoordinates() const {
    return m_vCheckCoordinates;
}

vector<CCoordinate> CPiece::GetNextMoves() {
    return m_vNextMoves;
}

vector<CCoordinate> CPiece::GetNextMoves() const {
    return m_vNextMoves;
}

void CPiece::SetAlive(bool alive) {
    m_bAlive = alive;
}

bool CPiece::GetAlive() {
    return m_bAlive;
}

bool CPiece::GetAlive() const {
    return m_bAlive;
}

void CPiece::AddMoves() {
    m_iMoves++;
}

void CPiece::ComputeEffectiveNextMoves() {
    int x = m_Coordinate.GetX();
    int y = m_Coordinate.GetY();
    int movement = ((m_iSide == 0)? -1: 1);

    int (*p)[14] = pGameInfo->m_board;

    m_vNextMoves.clear();

    switch (m_eType) {
    case CHARIOT:
        for (int i = x - 1; i >= 2; i--) {
            if (p[i][y] == 0)
                m_vNextMoves.push_back(CCoordinate(i, y));
            else if (p[i][y] / 100 == m_iSide + 1)
                break;
            else {
                m_vNextMoves.push_back(CCoordinate(i, y));
                break;
            }
        }
        for (int i = x + 1; i <= 10; i++) {
            if (p[i][y] == 0)
                m_vNextMoves.push_back(CCoordinate(i, y));
            else if (p[i][y] / 100 == m_iSide + 1)
                break;
            else {
                m_vNextMoves.push_back(CCoordinate(i, y));
                break;
            }
        }
        for (int i = y - 1; i >= 2; i--) {
            if (p[x][i] == 0)
                m_vNextMoves.push_back(CCoordinate(x, i));
            else if (p[x][i] / 100 == m_iSide + 1)
                break;
            else {
                m_vNextMoves.push_back(CCoordinate(x, i));
                break;
            }
        }
        for (int i = y + 1; i <= 11; i++) {
            if (p[x][i] == 0)
                m_vNextMoves.push_back(CCoordinate(x, i));
            else if (p[x][i] / 100 == m_iSide + 1)
                break;
            else {
                m_vNextMoves.push_back(CCoordinate(x, i));
                break;
            }
        }
        break;

    case HORSE:
        if (p[x - 1][y] == 0) {
            if (p[x - 2][y - 1] == 0 || (p[x - 2][y - 1]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 2, y - 1));
            if (p[x - 2][y + 1] == 0 || (p[x - 2][y + 1]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 2, y + 1));
        }
        if (p[x + 1][y] == 0) {
            if (p[x + 2][y - 1] == 0 || (p[x + 2][y - 1]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 2, y - 1));
            if (p[x + 2][y + 1] == 0 || (p[x + 2][y + 1]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 2, y + 1));
        }
        if (p[x][y + 1] == 0) {
            if (p[x - 1][y + 2] == 0 || (p[x - 1][y + 2]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 1, y + 2));
            if (p[x + 1][y + 2] == 0 || (p[x + 1][y + 2]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 1, y + 2));
        }
        if (p[x][y - 1] == 0) {
            if (p[x - 1][y - 2] == 0 || (p[x - 1][y - 2]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 1, y - 2));
            if (p[x + 1][y - 2] == 0 || (p[x + 1][y - 2]) / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 1, y - 2));
        }
        break;

    case ELEPHANT:
        if (p[x - 1][y - 1] == 0)
            if (p[x - 2][y - 2] == 0 || p[x - 2][y - 2] / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 2, y - 2));
        if (p[x - 1][y + 1] == 0)
            if (p[x - 2][y + 2] == 0 || p[x - 2][y + 2] / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 2, y + 2));
        if (p[x + 1][y + 1] == 0)
            if (p[x + 2][y + 2] == 0 || p[x + 2][y + 2] / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 2, y + 2));
        if (p[x + 1][y - 1] == 0)
            if (p[x + 2][y - 2] == 0 || p[x + 2][y - 2] / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 2, y - 2));
        break;

    case MANDARIN:
        if (p[x - 1][y - 1] == 0 || p[x - 1][y - 1] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x - 1, y - 1));
        if (p[x - 1][y + 1] == 0 || p[x - 1][y + 1] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x - 1, y + 1));
        if (p[x + 1][y + 1] == 0 || p[x + 1][y + 1] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x + 1, y + 1));
        if (p[x + 1][y - 1] == 0 || p[x + 1][y - 1] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x + 1, y - 1));
        break;

    case KING:
        if (p[x][y - 1] == 0 || p[x][y - 1] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x, y - 1));
        if (p[x][y + 1] == 0 || p[x][y + 1] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x, y + 1));
        if (p[x - 1][y] == 0 || p[x - 1][y] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x - 1, y));
        if (p[x + 1][y] == 0 || p[x + 1][y] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x + 1, y));
        break;

    case CANNON: {
        bool flag = false;
        for (int i = x - 1; i >= 2; i--) {
            if (p[i][y] == 0) {
                if (flag == false)
                    m_vNextMoves.push_back(CCoordinate(i, y));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[i][y] / 100) == (2 - m_iSide))
                        m_vNextMoves.push_back(CCoordinate(i, y));
                    break;
                }
            }
        }
        flag = false;

        for (int i = x + 1; i <= 10; i++) {
            if (p[i][y] == 0) {
                if (flag == false)
                    m_vNextMoves.push_back(CCoordinate(i, y));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[i][y] / 100) == (2 - m_iSide))
                        m_vNextMoves.push_back(CCoordinate(i, y));
                    break;
                }
            }
        }
        flag = false;

        for (int i = y - 1; i >= 2; i--) {
            if (p[x][i] == 0) {
                if (flag == false)
                    m_vNextMoves.push_back(CCoordinate(x, i));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[x][i] / 100) == (2 - m_iSide))
                        m_vNextMoves.push_back(CCoordinate(x, i));
                    break;
                }
            }
        }
        flag = false;

        for (int i = y + 1; i <= 11; i++) {
            if (p[x][i] == 0) {
                if (flag == false)
                    m_vNextMoves.push_back(CCoordinate(x, i));
            }
            else {
                if (flag == false)
                    flag = true;
                else {
                    if ((p[x][i] / 100) == (2 - m_iSide))
                        m_vNextMoves.push_back(CCoordinate(x, i));
                    break;
                }
            }
        }

        break;
    }
    case PAWN:
        //after the pawn crosses the river, it also can move leftward or rightward
        if (m_iMoves >= 2) {
            if (p[x + 1][y] == 0 || p[x + 1][y] / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x + 1, y));
            if (p[x - 1][y] == 0 || p[x - 1][y] / 100 == (2 - m_iSide))
                m_vNextMoves.push_back(CCoordinate(x - 1, y));
        }
        if (p[x][y + movement] == 0 || p[x][y + movement] / 100 == (2 - m_iSide))
            m_vNextMoves.push_back(CCoordinate(x, y + movement));
        break;

    default:
        break;
    }

}

void CPiece::ComputeCheckCoordinates() {
    m_vCheckCoordinates.clear();
    int temp = (m_iSide == 0? 2: 9);
    int delta = (m_iSide == 0? -1: 1);

    int (*board)[14] = pGameInfo->m_board;

    if (m_eType == CHARIOT || m_eType == HORSE || m_eType == PAWN) {
        for (int i = 0; i < m_vNextMoves.size(); i++) {
            int x = m_vNextMoves[i].GetX();
            int y = m_vNextMoves[i].GetY();

            if (x >= 5 && x <= 7 && y >= temp && y <= temp + 2)
                m_vCheckCoordinates.push_back(CCoordinate(x, y));
        }
    }

    else if (m_eType == CANNON ) {
        int x = m_Coordinate.GetX();
        int y = m_Coordinate.GetY();
        bool flag = false;

        if (x >= 5 && x <= 7) {
            int i = y + delta;
            while (board[x][i] >= 0) {
                if (board[x][i] == 0) {
                    if (flag == true)
                        m_vCheckCoordinates.push_back(CCoordinate(x, i));
                }
                else {
                    if (flag == false)
                        flag = true;
                    else {
                        if ((board[x][i] / 100) == (1 - m_iSide))
                            m_vCheckCoordinates.push_back(CCoordinate(x, i));
                        break;
                    }
                }
                i += delta;
            }
        }

        else if (y >= temp && y <= temp + 2) {
            if (x >= 2 && x <= 5) {
                for (int i = x + 1; i <= 7; i++) {
                    if (board[i][y] == 0) {
                        if (flag == true)
                            m_vCheckCoordinates.push_back(CCoordinate(i, y));
                    }
                    else {
                        if (flag == false)
                            flag = true;
                        else {
                            if ((board[i][y] / 100) == (1 - m_iSide))
                                m_vCheckCoordinates.push_back(CCoordinate(i, y));
                            break;
                        }
                    }
                }
            }
            else if (x >= 7 && x <= 10) {
                for (int i = x - 1; i >= 5; i--) {
                    if (board[i][y] == 0) {
                        if (flag == true)
                            m_vCheckCoordinates.push_back(CCoordinate(i, y));
                    }
                    else {
                        if (flag == false)
                            flag = true;
                        else {
                            if ((board[i][y] / 100) == (1 - m_iSide))
                                m_vCheckCoordinates.push_back(CCoordinate(i, y));
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
        int x = m_Coordinate.GetX();
        int y = m_Coordinate.GetY();
        int i = y + delta;

        if (m_iSide == 0) {
            for (; i >= 5; i--) {
                if (board[x][i] != 0)
                    break;
            }
            if (i == 4) {
                for (; i >= 2; i--) {
                    if (board[x][i] == 0)
                        m_vCheckCoordinates.push_back(CCoordinate(x, i));
                    else {
                        if (board[x][i] / 100 == m_iSide)
                            m_vCheckCoordinates.push_back(CCoordinate(x, i));
                        break;
                    }
                }
            }
        }
        else {
            for (; i <= 8; i++) {
                if (board[x][i] != 0)
                    break;
            }
            if (i == 9) {
                for (; i <= 11; i++) {
                    if (board[x][i] == 0)
                        m_vCheckCoordinates.push_back(CCoordinate(x, i));
                    else {
                        if (board[x][i] / 100 == m_iSide)
                            m_vCheckCoordinates.push_back(CCoordinate(x, i));
                        break;
                    }
                }
            }

        }

    }


    else
        return;
}
