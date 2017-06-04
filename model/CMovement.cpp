#include "model/CMovement.h"
#include <string.h>

CMovement::CMovement() :
    pieceID(0),
    x(0),
    y(0){

}

CMovement::CMovement(int id, int x, int y) :
    pieceID(id),
    x(x),
    y(y){
}

CMovement::~CMovement() {

}

int CMovement::GetPieceID() {
    return pieceID;
}

int CMovement::GetX() {
    return x;
}

int CMovement::GetY() {
    return y;
}

void CMovement::Serialize(char *data) {
    char temp[7];
    temp[0] = (pieceID / 100) + '0';
    temp[1] = ((pieceID % 100) / 10 ) + '0';
    temp[2] = (pieceID % 10) + '0';
    temp[3] = x / 10 + '0';
    temp[4] = x % 10 + '0';
    temp[5] = y / 10 + '0';
    temp[6] = y % 10 + '0';
    memcpy(data, temp, sizeof(temp));
}

void CMovement::Deserialize(char *data) {
    pieceID = (data[0] - '0')* 100 + (data[1] - '0') * 10 + (data[2] - '0');
    x = (data[3] - '0') * 10 + (data[4] - '0');
    y = (data[5] - '0') * 10 + (data[6] - '0');
}
