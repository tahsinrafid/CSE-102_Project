
#ifndef GLOBALS_H
#define GLOBALS_H

#include "structs.h"


// Extern declarations for all global variables used in both iMain.cpp and level2.cpp
extern int brick_count, spike_count, water_count, star_count, ring_count;
extern int cameraX;
extern int lives, ringsCollected, checkpoints, score;
extern int checkPointX, checkPointY;
extern int popX, popY;
extern int ground;
extern int channel = -1;
extern int channel2 = -1 , channel3 = -1, channel4 = -1;
extern int save_message_timer;
extern float gravity;
extern int deathTimerIndex;
extern int deathDelayCounter;
extern int checkPointIndex, ringIndex, current_level,saved_level;
extern bool onBrick, isJump, foundsupport, moveleft, moveright, sound_on, checkPointReached, isdead, nameEntered, scoresaved, save_button_pressed, upmove, normal;


//rafid
extern Image menu, bg,bg2, brick_img, spike_img, water_img, star_img, ring_img, ring_rotated_img, pop_img, restart_icon, menu_icon, resume_icon, sound_on_icon, sound_off_icon;
extern Image life_icon, ring_icon, pause_icon, checkpoint_catched_img, ring_collected_img, ring_rotated_col_img, name_inp_img;
extern Image ok_icon, back_icon, save_icon;
extern Image leaderboard_img;
extern Image yes_img, no_img, box_img, portal;
//auntor
extern Image checkpoint_img, thorn_img;
extern Image checkpoint_reached, pause, life_img, gameover_img, leaderboard, congo_img, next_level_img, complete_star;
extern Image restart_button, menu_button;
extern Image reverse_gravity_img, reverse_gravity_2_img, reverse_key_img;
extern Image sad_img, game_win_star;
extern Image congo_bg_img;

extern char str[10];
extern char str2[10];
extern char currPlayerName[];
extern Ball ball;
extern Brick bricks[];
//auntor
extern Spike spikes2[];
extern Ring rings2[];
extern Water waters2[];
extern Star stars2[];
extern thorn thornes[];
extern GravityPerk gravity_perks[];
extern reverse_key reverse_keys[];
// Add any other global variables you need to share
// #define screenWidth 1100
// #define screenHeight 600
// #define platformWidth2 140 * 50
// #define platformHeight 50
// #define brickW 50
// #define spikeW 42
// #define spikeH 80
// #define ringW 30
// #define ringH 90
// #define starW 55
// #define starH 55
// #define waterW 62
// #define waterH 62
// #define MAX_BRICKS 1000
// //auntor
// #define MAX_SPIKES2 40
// #define MAX_WATER2 5
// #define MAX_STARS2 5
// #define MAX_RINGS2 15

// #define MAX_NAME_LEN 30
// #define MAX_LEADERS 10

#endif // GLOBALS_H
