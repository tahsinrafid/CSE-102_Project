#ifndef STRUCTS_H
#define STRUCTS_H


#include "constants.h"

// All struct definitions shared between iMain.cpp, level2.cpp, etc.

typedef struct {
    char name[MAX_NAME_LEN];
    int score;
} LboardEntry;

typedef struct {
    int x, y, radius;
    float velx, vely;
    Sprite sprite;
    bool isAlive;
    bool is_col_spike;
    Image img[1];
} Ball;
Ball ball;

typedef struct {
    int x, y, width, height;
    bool isVisible, isGround;
} Brick;

Brick bricks[MAX_BRICKS];

typedef struct {
    int x, y, width, height;
    bool isVisible;
} Spike;

Spike spikes[MAX_SPIKES1];
 Spike spikes2[MAX_SPIKES2];

typedef struct {
    int x, y, width, height;
    bool isRotated, isCollected;
} Ring;

Ring rings[MAX_RINGS1];
Ring rings2[MAX_RINGS2];

typedef struct {
    int x, y, width, height;
    bool isCollected;
} Water;

Water waters[MAX_WATER1];
Water waters2[MAX_WATER2];

typedef struct {
    int x, y, width, height;
    bool isVisible, isCollected;
} Star;

Star stars[MAX_STARS1];
Star stars2[MAX_STARS2];

typedef struct {
    int x, y, width, height;
    bool isVisible, isReversed;
} GravityPerk;

GravityPerk gravity_perks[2];

typedef struct {
    int x, y, width, height;
    bool isVisible;
} thorn;

thorn thornes[6];

typedef struct
{
    int x, y, width, height;
    bool isVisible;
} reverse_key;

reverse_key reverse_keys[2];

// Add any other shared structs here

#endif // STRUCTS_H
