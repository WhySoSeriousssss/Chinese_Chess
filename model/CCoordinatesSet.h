#ifndef CCOORDINATESSET_H
#define CCOORDINATESSET_H

#include "model/CCoordinate.h"
#include <vector>
#include <iostream>

class CCoordinatesSet {
public:
    CCoordinatesSet();
    ~CCoordinatesSet();

    bool Add(CCoordinate crd);
    bool AddInPalace(CCoordinate crd);

    const CCoordinate Get(int i);
    bool Contains(CCoordinate crd);
    void Delete(CCoordinate crd);
    void Clear();
    void Print();

    inline int Size() {return (int)m_vSet.size();}

private:
    std::vector<CCoordinate> m_vSet;
};

#endif // CCOORDINATESSET_H
