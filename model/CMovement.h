#ifndef CMOVEMENT_H
#define CMOVEMENT_H

class CMovement {
public:
    CMovement();
    CMovement(int id, int x, int y);
    ~CMovement();

private:
    int pieceID;
    int x;
    int y;
};

#endif // CMOVEMENT_H
