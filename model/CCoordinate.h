#ifndef CCOORDINATE_H
#define CCOORDINATE_H

class CCoordinate {
public:
    CCoordinate();
    CCoordinate(int x, int y);
    ~CCoordinate();

    bool operator ==(const CCoordinate &crd);

    int GetXCoordinate();
    int GetXCoordinate() const;

    int GetYCoordinate();
    int GetYCoordinate() const;

    void Reset(int newX, int newY);

private:
    int m_iXCoordinate;
    int m_iYCoordinate;
};

#endif // CCOORDINATE_H
