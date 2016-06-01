#include "CCoordinate.h"

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
    return (m_iXCoordinate == crd.GetXCoordinate() && m_iYCoordinate == crd.GetYCoordinate());
}

int CCoordinate::GetXCoordinate() {
    return m_iXCoordinate;
}

int CCoordinate::GetXCoordinate() const {
    return m_iXCoordinate;
}

int CCoordinate::GetYCoordinate() {
    return m_iYCoordinate;
}

int CCoordinate::GetYCoordinate() const {
    return m_iYCoordinate;
}

void CCoordinate::Reset(int newX, int newY) {
    m_iXCoordinate = newX;
    m_iYCoordinate = newY;
}
