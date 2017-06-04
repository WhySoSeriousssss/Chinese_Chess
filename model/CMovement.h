#ifndef CMOVEMENT_H
#define CMOVEMENT_H

class CMovement {
public:
    CMovement();
    CMovement(int id, int x, int y);
    ~CMovement();

    int GetPieceID();
    int GetX();
    int GetY();

    void Serialize(char *data);
    void Deserialize(char *data);

private:
    int pieceID;
    int x;
    int y;
};

#endif // CMOVEMENT_H
