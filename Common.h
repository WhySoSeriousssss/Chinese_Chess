#ifndef COMMON_H
#define COMMON_H

enum ChessPieceType_e {
    NONE,
    CHARIOT,
    HORSE,
    ELEPHANT,
    MANDARIN,
    KING,
    CANNON,
    PAWN
};

enum PlayerSide_e {
    RED = 1,
    BLACK = 2
};

enum PieceIconStyle_e {
    P_DELICATE,
    P_MOVESKY,
    P_MRSJ,
    P_POLISH,
    P_WOOD,
    P_XQSTUDIO,
    P_ZMBL
};

enum BoardStyle_e {
    B_CANVAS,
    B_CLOUDS,
    B_DROPS,
    B_GREEN,
    B_MOVESKY,
    B_MRSJ,
    B_QIANHONG,
    B_SHEET,
    B_SKELETON,
    B_WHITE,
    B_WOOD,
    B_XQSTUDIO,
    B_ZMBL
};

const int C_DELTA = 40;
const int C_ICONSIZE = 41;
const int C_X = 7;
const int C_Y = 7;

#endif // COMMON_H
