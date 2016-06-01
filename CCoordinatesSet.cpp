#include "CCoordinatesSet.h"

CCoordinatesSet::CCoordinatesSet() {

}

CCoordinatesSet::~CCoordinatesSet() {

}

bool CCoordinatesSet::Add(CCoordinate crd) {
    int x = crd.GetXCoordinate();
    int y = crd.GetYCoordinate();

    if (x > 10 || x < 2 || y > 11 || y < 2)
        return false;

    else {
        if (Contains(crd)) {
            return false;
        }
        else {
            m_vSet.push_back(crd);
            return true;
        }
    }
}

bool CCoordinatesSet::AddInPalace(CCoordinate crd) {
    int x = crd.GetXCoordinate();
    int y = crd.GetYCoordinate();

    if (x <= 7 && x >= 5 && ( (y >= 2 && y <= 4) || (y >= 9 && y <= 11) )) {
        if (Contains(crd)) {
            return false;
        }
        else {
            m_vSet.push_back(crd);
            return true;
        }
    }

    return false;
}


const CCoordinate CCoordinatesSet::Get(int i) {
    return m_vSet[i];
}


bool CCoordinatesSet::Contains(CCoordinate crd) {
    for (int i = 0; i < m_vSet.size(); i++) {
        if (crd == m_vSet[i])
            return true;
    }
    return false;
}

void CCoordinatesSet::Delete(CCoordinate crd) {

}

void CCoordinatesSet::Clear() {
    m_vSet.clear();
}

void CCoordinatesSet::Print() {
    for (int i = 0; i < m_vSet.size(); i++)
        std::cout << "(" << m_vSet[i].GetXCoordinate() << ", " << m_vSet[i].GetYCoordinate() << ")  ";
    std::cout << std::endl;
}

