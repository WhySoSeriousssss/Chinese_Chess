#include "model/CCoordinate.h"

CCoordinate::CCoordinate() {
    m_iXCoordinate = 0;
    m_iYCoordinate = 0;
}

CCoordinate::CCoordinate(int x, int y) {
    m_iXCoordinate = x;
    m_iYCoordinate = y;
}

CCoordinate::~CCoordinate() {

}

bool CCoordinate::operator ==(const CCoordinate &crd) {
    return (m_iXCoordinate == crd.GetX() && m_iYCoordinate == crd.GetY());
}

int CCoordinate::GetX() {
    return m_iXCoordinate;
}

int CCoordinate::GetX() const {
    return m_iXCoordinate;
}

int CCoordinate::GetY() {
    return m_iYCoordinate;
}

int CCoordinate::GetY() const {
    return m_iYCoordinate;
}

void CCoordinate::Reset(int newX, int newY) {
    m_iXCoordinate = newX;
    m_iYCoordinate = newY;
}
