
#include "level2.h"
#include <stdbool.h>
#include <string.h>
#define screenWidth 1100
#define screenHeight 600
#define platformWidth1 104 * 50
#define platformWidth2 140 * 50
#define platformHeight 50
#define brickW 50
#define spikeW 42
#define spikeH 80
#define ringW 30
#define ringH 90
#define starW 55
#define starH 55
#define waterW 62
#define waterH 62
#define MAX_BRICKS 1000
#define MAX_SPIKES1 10
#define MAX_WATER1 1
#define MAX_STARS1 2
#define MAX_RINGS1 6
#define MAX_SPIKES2 40
#define MAX_WATER2 5
#define MAX_STARS2 5
#define MAX_RINGS2 15
#define MAX_NAME_LEN 30
#define MAX_LEADERS 10

int brick_count = 0, spike_count = 0, water_count = 0, star_count = 0, ring_count = 0;
int cameraX = 0;
int lives = 2, ringsCollected = 0, checkpoints = 0, score = 0;
int checkPointX = 0, checkPointY = 0;
int popX, popY;
int ground = brickW + 30;
float gravity = -0.9;
int deathTimerIndex;
int deathDelayCounter = 0;
int checkPointIndex = -1;
int ringIndex = -1;
int current_level = 1;
int saved_level = 1;
int save_message_timer = 0;
// int channel = -1;
// int channel2 = -1 , channel3 = -1;
bool onBrick = true;
bool isJump = false;
bool foundsupport;
bool moveleft = false, moveright = false;
bool sound_on = true;
bool checkPointReached = false;
bool isdead = false;
bool nameEntered = false;
bool scoresaved = false;
bool save_button_pressed = false;
bool upmove = true;
bool normal = true;

Image menu, bg, brick_img, spike_img, water_img, star_img, ring_img, ring_rotated_img, pop_img, restart_icon, menu_icon, resume_icon, sound_on_icon, sound_off_icon;
Image life_icon, ring_icon, pause_icon, checkpoint_catched_img, ring_collected_img, ring_rotated_col_img, name_inp_img;
Image ok_icon, back_icon, save_icon;
Image leaderboard_img, bg2, about_us_img;
Image yes_img, no_img, box_img, portal;
Image checkpoint_img, thorn_img, instruction_img;
Image checkpoint_reached, pause, life_img, gameover_img, leaderboard, congo_img, next_level_img, complete_star;
Image restart_button, menu_button;
Image reverse_gravity_img, reverse_gravity_2_img, reverse_key_img, sad_img, game_win_star, congo_bg_img, back_img_2;

char str[10];
char str2[10];
char currPlayerName[MAX_NAME_LEN] = {'\0'};

void balljump1();
void moveball1();
void midairmovement1();
void reset();
void partial_reset();
void deathDelayHandler();
void input_Name();
void saveToLeaderboard();
void drawLeaderboard();
void lev1Complete();
void loadGame();
void saveGame();
void initlevel1();
void drawlevel1();
void checkBrickCollision1();
void checkSpikeCollision1();
void checkWaterCollision1();
void checkRingCollision1();
void checkStarCollision1();
void draw_bg();
void drawball();
void drawlevel1();
void moveball();
void balljump();
void lev2Complete();

typedef enum
{
    MENU,
    LEADERBOARD,
    SETTINGS,
    CREDITS,
    NAME_INPUT,
    LEVEL_1,
    PAUSE,
    GAME_OVER,
    LEVEL_1_COMPLETE,
    LEVEL_2,
    LEVEL_2_COMPLETE,
    HELP

} Gamestate;

Gamestate gamestate = MENU;
Gamestate previousState = MENU;

void input_Name()
{
    iShowLoadedImage(0, 0, &bg);
    int boxW = 600, boxH = 300;
    int boxX = (screenWidth - boxW) / 2;
    int boxY = (screenHeight - boxH) / 2;
    iShowLoadedImage(boxX, boxY, &name_inp_img);
    iShowLoadedImage(boxX + 70, boxY + 30, &back_icon);
    iShowLoadedImage(boxX + 360, boxY + 30, &ok_icon);
    int fontSize = 40;
    int charWidth = fontSize * 0.6;
    int textLen = strlen(currPlayerName);
    int textPixelWidth = (int)(charWidth * textLen);
    int nameBoxX = boxX + (boxW - textPixelWidth) / 2 + 10;
    int nameBoxY = boxY + (boxH - fontSize) / 2 + 20;
    iSetColor(0, 0, 0);
    iShowText(nameBoxX, nameBoxY, currPlayerName, "assets/fonts/arial.ttf", fontSize);
}

// typedef struct
// {
//     char name[MAX_NAME_LEN];
//     int score;
// } LboardEntry;

// typedef struct
// {
//     int x, y, radius;
//     float velx, vely;
//     Sprite sprite;
//     bool isAlive;
//     bool is_col_spike;
//     Image img[1];
// } Ball;

//  Ball ball;

void loadresources()
{
    iLoadImage(&menu, "assets/images/menu.png");
    iLoadImage(&brick_img, "assets/images/brick.png");
    iResizeImage(&brick_img, brickW, brickW);
    iLoadImage(&bg, "assets/images/levelbg1.png");
    iLoadImage(&spike_img, "assets/images/spike.png");
    iLoadImage(&water_img, "assets/images/life@2x.png");
    iResizeImage(&water_img, 62, 62);
    iLoadImage(&star_img, "assets/images/checkpoint@2x.png");
    iResizeImage(&star_img, 55, 55);
    iLoadImage(&ring_img, "assets/images/ring_small_top@2x.png");
    iResizeImage(&ring_img, 30, 90);
    iLoadImage(&ring_rotated_img, "assets/images/ring_rotated.png");
    iResizeImage(&ring_rotated_img, 90, 30);

    iLoadFramesFromFolder(ball.img, "assets/images/sprites/BallFrames/Moving");
    iChangeSpriteFrames(&ball.sprite, ball.img, 1);
    iResizeSprite(&ball.sprite, 60, 60);

    iLoadImage(&pop_img, "assets/images/sprites/BallFrames/Moving/ball_pop.png");
    iLoadImage(&restart_icon, "assets/images/restart_icon.png");
    iLoadImage(&menu_icon, "assets/images/menu_icon.png");
    iLoadImage(&resume_icon, "assets/images/resume_icon.png");
    iLoadImage(&sound_on_icon, "assets/images/sound_on_icon.png");
    iLoadImage(&sound_off_icon, "assets/images/sound_off_icon.png");
    iLoadImage(&life_icon, "assets/images/gbar_life@2x.png");
    iLoadImage(&ring_icon, "assets/images/gbar_ring@2x.png");
    iLoadImage(&checkpoint_catched_img, "assets/images/checkpoint_catched@2x.png");
    iLoadImage(&ring_collected_img, "assets/images/ring_col.png");
    iLoadImage(&ring_rotated_col_img, "assets/images/ring_col_rotate.png");
    iLoadImage(&ring_icon, "assets/images/gbar_ring@2x.png");
    iLoadImage(&pause_icon, "assets/images/gbar_pause@2x.png");
    iLoadImage(&name_inp_img, "assets/images/INPUT_NAME.png");
    iLoadImage(&ok_icon, "assets/images/1.png");
    iLoadImage(&back_icon, "assets/images/2.png");
    iLoadImage(&leaderboard_img, "assets/images/Leaderboard.jpg");
    iResizeImage(&leaderboard_img, screenWidth, screenHeight);
    iLoadImage(&yes_img, "assets/images/yes.png");
    iLoadImage(&no_img, "assets/images/no.png");
    iLoadImage(&box_img, "assets/images/box.png");
    iLoadImage(&save_icon, "assets/images/save_icon.png");
    iLoadImage(&portal, "assets/images/portal.png");

    iLoadImage(&gameover_img, "assets/images/gameover.png");
    iLoadImage(&thorn_img, "assets/images/dyn_thorn@2x.png");
    iResizeImage(&thorn_img, 50, 50);
    iLoadImage(&congo_img, "assets/images/congo_img.png");
    iLoadImage(&next_level_img, "assets/images/next_level.png");
    iLoadImage(&reverse_gravity_img, "assets/images/reverse_gravity.png");
    iResizeImage(&reverse_gravity_img, 50, 50);
    iLoadImage(&reverse_gravity_2_img, "assets/images/reverse_gravity_2.png");
    iResizeImage(&reverse_gravity_2_img, 50, 50);
    iLoadImage(&reverse_key_img, "assets/images/reverse_key.png");
    iResizeImage(&reverse_key_img, 50, 50);
    iLoadImage(&bg2, "assets/images/bg2.jpg");
    iResizeImage(&bg2, screenWidth, screenHeight);
    iLoadImage(&about_us_img, "assets/images/CREDITS_img.png");
    //iResizeImage(&about_us_img, screenWidth, screenHeight);
    iLoadImage(&instruction_img, "assets/images/Instructions...png");
    iResizeImage(&instruction_img, screenWidth, screenHeight);
    iLoadImage(&menu_button, "assets/images/menu_button.png");
    iLoadImage(&sad_img, "assets/images/sad.jpeg");
    iResizeImage(&sad_img, screenWidth, screenHeight);
    iLoadImage(&game_win_star, "assets/images/game_win_star.png");
    iResizeImage(&game_win_star, 150, 150);
    // iResizeImage(&menu_button, 150, 50);
    iLoadImage(&congo_bg_img, "assets/images/congo_bg_img.png");
}

void initball()
{
    ball.x = 150;
    ball.radius = 30;
    ball.y = brickW + ball.radius;
    ball.velx = 0;
    ball.vely = 0;
    ball.isAlive = true;
}

void drawball()
{
    if (ball.isAlive)
    {
        iSetSpritePosition(&ball.sprite, ball.x - cameraX - ball.radius, ball.y - ball.radius);
        iShowSprite(&ball.sprite);
    }
    else
    {
        iShowLoadedImage(popX - cameraX, popY, &pop_img);
    }
}

void initlevel1()
{
    printf("%d\n", current_level);
    printf("%d\n", saved_level);
    for (int i = 0; i < 112; i++)
    {
        bricks[brick_count].x = i * brickW;
        bricks[brick_count].y = 0;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = true;
        // printf("Brick %d: x=%d, y=%d, w=%d, h=%d, visible=%d, ground=%d\n", brick_count, bricks[brick_count].x, bricks[brick_count].y, bricks[brick_count].width, bricks[brick_count].height, bricks[brick_count].isVisible, bricks[brick_count].isGround);
        brick_count++;
    }
    // draw upper platform
    for (int i = 0; i < 112; i++)
    {
        bricks[brick_count].x = i * brickW;
        bricks[brick_count].y = screenHeight - brickW;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = true;
        brick_count++;
    }
    int k = 0;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            bricks[brick_count].x = k;
            bricks[brick_count].y = brickW + i * brickW;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            // printf("Brick %d: x=%d, y=%d, w=%d, h=%d, visible=%d, ground=%d\n", brick_count, bricks[brick_count].x, bricks[brick_count].y, bricks[brick_count].width, bricks[brick_count].height, bricks[brick_count].isVisible, bricks[brick_count].isGround);
            brick_count++;
        }
        k = brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 6; i++)
        {
            bricks[brick_count].x = 5 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 14 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            bricks[brick_count].x = 21 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = brickW;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 26 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = 5 * brickW;
    for (int i = 0; i < 2; i++)
    {
        bricks[brick_count].x = 28 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            bricks[brick_count].x = 32 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    for (int i = 0; i < 2; i++)
    {
        bricks[brick_count].x = 33 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = 5 * brickW;
    for (int i = 0; i < 2; i++)
    {
        bricks[brick_count].x = 38 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 40 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int i = 0; i < 2; i++)
    {
        bricks[brick_count].x = 33 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            bricks[brick_count].x = 44 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 44 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            bricks[brick_count].x = 64 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 66 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 70 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 74 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 78 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = brickW;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            bricks[brick_count].x = 84 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    for (int i = 0; i < 2; i++)
    {
        bricks[brick_count].x = 84 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 87 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = brickW;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            bricks[brick_count].x = 95 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 95 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = 3 * brickW;
    for (int i = 0; i < 2; i++)
    {
        bricks[brick_count].x = 98 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 91 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 102.2 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    // initialize spikes
    spikes[spike_count] = (Spike){.x = 17 + 17 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 17 + 30 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 17 + 36 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 10 + 51 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 10 + 54 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 10 + 58 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 10 + 62 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 86 * brickW, .y = 3 * brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes[spike_count] = (Spike){.x = 97 * brickW, .y = 3 * brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;

    // initialize rings
    rings[ring_count] = (Ring){.x = 5 + 9 * brickW, .y = brickW + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings[ring_count] = (Ring){.x = 34 * brickW - 5, .y = 6 * brickW + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings[ring_count] = (Ring){.x = 5 + 74 * brickW, .y = brickW + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings[ring_count] = (Ring){.x = 5 + 82 * brickW, .y = brickW + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings[ring_count] = (Ring){.x = 5 + 89 * brickW, .y = brickW * 4 + 5, .width = ringW, .height = ringH, .isRotated = true, .isCollected = false};
    ring_count++;
    rings[ring_count] = (Ring){.x = 5 + 93 * brickW, .y = brickW * 4 + 5, .width = ringW, .height = ringH, .isRotated = true, .isCollected = false};
    ring_count++;

    // initialize stars
    stars[star_count] = (Star){.x = 5 + 56 * brickW, .y = screenHeight - 5 * brickW, .width = starW, .height = starH, .isVisible = true, .isCollected = false};
    star_count++;
    stars[star_count] = (Star){.x = 5 + 91 * brickW, .y = screenHeight - 9 * brickW - 4, .width = starW, .height = starH, .isVisible = true, .isCollected = false};
    star_count++;

    // initialize water
    waters[water_count] = (Water){.x = 5 + 78 * brickW, .y = screenHeight - 2 * brickW - 10, .width = waterW, .height = waterH, .isCollected = false};
    water_count++;
    // printf("%d %d %d", spike_count, ring_count, water_count);
    // reverse_gravity = {35 * brickW, platformHeight + 10, 40, 40, true};
    // reverse_gravity_2 = {reverse_gravity.x + 55 * brickW, screenHeight - brickW - 50, 40, 40, true};
}
void drawlevel1()
{
    for (int i = 0; i < brick_count; i++)
    {
        if (bricks[i].isVisible)
        {
            iShowLoadedImage2(bricks[i].x - cameraX, bricks[i].y, &brick_img);
        }
    }
    for (int i = 0; i < spike_count; i++)
    {
        if (spikes[i].isVisible)
        {
            iShowLoadedImage(spikes[i].x - cameraX, spikes[i].y, &spike_img);
        }
    }
    for (int i = 0; i < ring_count; i++)
    {
        if (!rings[i].isRotated)
        {
            if (!rings[i].isCollected)
                iShowLoadedImage(rings[i].x - cameraX, rings[i].y, &ring_img);
            else
                iShowLoadedImage(rings[i].x - cameraX, rings[i].y, &ring_collected_img);
        }
        else
        {
            if (!rings[i].isCollected)
                iShowLoadedImage(rings[i].x - cameraX, rings[i].y, &ring_rotated_img);
            else
                iShowLoadedImage(rings[i].x - cameraX, rings[i].y, &ring_rotated_col_img);
        }
    }
    for (int i = 0; i < star_count; i++)
    {
        if (!stars[i].isCollected)
        {
            iShowLoadedImage(stars[i].x - cameraX, stars[i].y, &star_img);
        }
    }
    for (int i = 0; i < star_count; i++)
    {
        if (stars[i].isCollected)
        {
            iShowLoadedImage(stars[i].x - cameraX, stars[i].y, &checkpoint_catched_img);
        }
    }

    for (int i = 0; i < water_count; i++)
    {
        if (!waters[i].isCollected)
        {
            iShowLoadedImage(waters[i].x - cameraX, waters[i].y, &water_img);
        }
    }
    iShowLoadedImage(102.2 * 50 - cameraX, 50, &portal);
    iShowLoadedImage(45, 550, &life_icon);
    sprintf(str, "X%d", lives);
    iSetColor(255, 255, 255);
    iShowText(101, 555, str, "assets/fonts/Antonio-Bold.ttf", 42);

    iShowLoadedImage(190, 552, &ring_icon);
    sprintf(str, "X%d", (ringsCollected));
    iShowText(220, 555, str, "assets/fonts/Antonio-Bold.ttf", 42);
    iShowLoadedImage(1018, 530, &pause_icon);
    sprintf(str2, "Score: %d", score);
    iShowText(700, 555, str2, "assets/fonts/Antonio-Bold.ttf", 42);
}
void checkBrickCollision1()
{
    foundsupport = false;
    for (int i = 0; i < brick_count; i++)
    {
        Brick b = bricks[i];

        // check if the ball is directly above this brick
        if (ball.x + ball.radius > b.x &&
            ball.x - ball.radius < b.x + b.width &&
            ball.y >= b.y + b.height &&
            ball.y + ball.vely <= b.y + b.height)
        {
            ball.y = b.y + b.height + ball.radius;
            ball.vely = 0;
            isJump = false;
            onBrick = true;
        }
        // check hitting the brick from down
        if (ball.x + ball.radius > b.x &&
            ball.x - ball.radius < b.x + b.width &&
            ball.y <= b.y &&
            ball.y + ball.vely >= b.y)
        {
            ball.y = b.y - ball.radius;
            ball.vely = 0;
            onBrick = false;
            isJump = true;
        }
        // check hitting from the left
        if (ball.x < b.x &&
            ball.x + ball.radius >= b.x &&
            ball.y + ball.radius > b.y &&
            ball.y - ball.radius < b.y + b.height &&
            !b.isGround)
        {
            ball.x = b.x - ball.radius;
        }
        // check hitting from the right
        if (ball.x > b.x + b.width &&
            ball.x - ball.radius <= b.x + b.width &&
            ball.y + ball.radius > b.y &&
            ball.y - ball.radius < b.y + b.height &&
            !b.isGround)
        {
            ball.x = b.x + b.width + ball.radius;
        }
    }
}
void checklanding()
{
    foundsupport = false;
    if (onBrick)
    {
        for (int i = 0; i < brick_count; i++)
        {
            Brick b = bricks[i];
            if (ball.x + ball.radius > b.x &&
                ball.x - ball.radius < b.x + b.width &&
                ball.y == b.y + b.height + ball.radius)
            {
                foundsupport = true;
                break;
            }
        }
    }
    if (!foundsupport)
    {
        onBrick = false;
        isJump = true;
    }
}
void checkSpikeCollision1()
{
    if (isdead || !ball.isAlive)
        return;
    for (int i = 0; i < spike_count; i++)
    {
        Spike s = spikes[i];
        // check hitting from up
        bool hittop = (ball.x + ball.radius > s.x &&
                       ball.x - ball.radius < s.x + s.width &&
                       ball.y >= s.y + s.height &&
                       ball.y + ball.vely <= s.y + s.height);
        // check hitting from down
        bool hitdown = (ball.x + ball.radius > s.x &&
                        ball.x - ball.radius < s.x + s.width &&
                        ball.y <= s.y &&
                        ball.y + ball.vely >= s.y);
        // check hitting from left
        bool hitleft = (ball.x < s.x &&
                        ball.x + ball.radius >= s.x &&
                        ball.y + ball.radius > s.y &&
                        ball.y - ball.radius < s.y + s.height);
        // check hitting from right
        bool hitright = (ball.x > s.x + s.width &&
                         ball.x - ball.radius <= s.x + s.width &&
                         ball.y + ball.radius > s.y &&
                         ball.y - ball.radius < s.y + s.height);

        if (hittop || hitdown || hitleft || hitright)
        {
            // if (hittop)
            //     popY = s.y + s.height + ball.radius, popX = ball.x;
            // if (hitdown)
            //     popY = s.y - ball.radius, popX = ball.x;
            // if (hitleft)
            //     popY = ball.y, popX = s.x - ball.radius;
            // if (hitright)
            //     popY = ball.y, popX = s.x + s.width + ball.radius;
            popX = ball.x;
            popY = ball.y;
            channel3= iPlaySound("assets/Sounds/ball_pop_sound.mp3",false, 50);
            //score -= 50;
            ball.isAlive = false;
            isdead = true;
            iResumeTimer(deathTimerIndex);
            deathDelayCounter = 0;
        }
    }
}
void checkStarCollision1()
{
    for (int i = 0; i < star_count; i++)
    {
        Star s = stars[i];
        if (ball.isAlive && stars[i].isVisible)
        {
            // check hitting from up
            bool hitup = (ball.x + ball.radius > s.x &&
                          ball.x - ball.radius < s.x + s.width &&
                          ball.y >= s.y + s.height &&
                          ball.y + ball.vely <= s.y + s.height);
            // check hitting from down
            bool hitdown = (ball.x + ball.radius > s.x &&
                            ball.x - ball.radius < s.x + s.width &&
                            ball.y <= s.y &&
                            ball.y + ball.vely >= s.y);
            // check hitting from left
            bool hitleft = (ball.x < s.x &&
                            ball.x + ball.radius >= s.x &&
                            ball.y + ball.radius > s.y &&
                            ball.y - ball.radius < s.y + s.height);
            // check hitting from right
            bool hitright = (ball.x > s.x + s.width &&
                             ball.x - ball.radius <= s.x + s.width &&
                             ball.y + ball.radius > s.y &&
                             ball.y - ball.radius < s.y + s.height);

            if (hitup || hitdown || hitleft || hitright)
            {
                stars[i].isVisible = false;
                stars[i].isCollected = true;
                checkPointX = stars[i].x;
                checkPointY = ball.y;
                checkPointIndex = i;
                checkPointReached = true;
                checkpoints++;
            }
        }
    }
}
void checkWaterCollision1()
{
    for (int i = 0; i < water_count; i++)
    {
        Water s = waters[i];
        if (ball.isAlive && !s.isCollected)
        {
            // check hitting from up
            bool hitup = (ball.x + ball.radius > s.x &&
                          ball.x - ball.radius < s.x + s.width &&
                          ball.y >= s.y + s.height &&
                          ball.y + ball.vely <= s.y + s.height);
            // check hitting from down
            bool hitdown = (ball.x + ball.radius > s.x &&
                            ball.x - ball.radius < s.x + s.width &&
                            ball.y <= s.y &&
                            ball.y + ball.vely >= s.y);
            // check hitting from left
            bool hitleft = (ball.x < s.x &&
                            ball.x + ball.radius >= s.x &&
                            ball.y + ball.radius > s.y &&
                            ball.y - ball.radius < s.y + s.height);
            // check hitting from right
            bool hitright = (ball.x > s.x + s.width &&
                             ball.x - ball.radius <= s.x + s.width &&
                             ball.y + ball.radius > s.y &&
                             ball.y - ball.radius < s.y + s.height);

            if (hitup || hitdown || hitleft || hitright)
            {
                waters[i].isCollected = true;
                lives++;
            }
        }
    }
}
void checkRingCollision1()
{
    for (int i = 0; i < ring_count; i++)
    {
        Ring s = rings[i];
        if (ball.isAlive && !s.isCollected)
        {
            // check hitting from top
            bool hitup = (ball.x + ball.radius > s.x &&
                          ball.x - ball.radius < s.x + s.width &&
                          ball.y >= s.y + s.height &&
                          ball.y + ball.vely <= s.y + s.height);
            // check hitting from down
            bool hitdown = (ball.x + ball.radius > s.x &&
                            ball.x - ball.radius < s.x + s.width &&
                            ball.y <= s.y &&
                            ball.y + ball.vely >= s.y);
            // check hitting from left
            bool hitleft = (ball.x < s.x &&
                            ball.x + ball.radius >= s.x &&
                            ball.y + ball.radius > s.y &&
                            ball.y - ball.radius < s.y + s.height);
            // check hitting from right
            bool hitright = (ball.x > s.x + s.width &&
                             ball.x - ball.radius <= s.x + s.width &&
                             ball.y + ball.radius > s.y &&
                             ball.y - ball.radius < s.y + s.height);

            if (hitup || hitdown || hitleft || hitright)
            {
                rings[i].isCollected = true;
                ringsCollected++;
                score += 50;
            }
        }
    }
}
void draw_bg()
{
    if (current_level == 1)
    {
        int bg_x = 0;
        while (bg_x < platformWidth1)
        {
            iShowLoadedImage(bg_x - cameraX, 0, &bg);
            bg_x += screenWidth;
        }
    }
    else if (current_level == 2)
    {
        int bg_x = 0;
        while (bg_x < platformWidth2)
        {
            iShowLoadedImage(bg_x - cameraX, 0, &bg);
            bg_x += screenWidth;
        }
    }
}
void draw_pause_menu()
{
    int boxWidth = 516, boxHeight = 260;
    int boxX = (screenWidth - boxWidth) / 2;
    int boxY = (screenHeight - boxHeight) / 2;
    iSetTransparentColor(255, 255, 255, 180);
    iFilledRectangle(boxX, boxY, boxWidth, boxHeight);

    iShowLoadedImage(boxX + 20, boxY + 20, &menu_icon);
    iShowLoadedImage(boxX + 20, boxY + 140, &restart_icon);
    iShowLoadedImage(boxX + 140, boxY + 20, &save_icon);
    iShowLoadedImage(boxX + 140, boxY + 140, &resume_icon);
}
void iDraw()
{
    iClear();
    if (gamestate == MENU)
    {
        iShowLoadedImage(0, 0, &menu);
        nameEntered = false;
        memset(currPlayerName, 0, sizeof(currPlayerName));
    }
    else if (gamestate == NAME_INPUT)
    {
        input_Name();
    }
    else if (gamestate == LEADERBOARD)
    {
        iShowLoadedImage(0, 0, &bg);
        drawLeaderboard();
    }
    else if (gamestate == LEVEL_1)
    {
        draw_bg();
        drawball();
        drawlevel1();
        iShowLoadedImage(0 - cameraX, 0, &brick_img);
    }
    else if (gamestate == LEVEL_2)
    {
        draw_bg();
        drawball();
        drawlevel2();
        iShowLoadedImage(0 - cameraX, 50, &portal);
        // if (ball.x >= 136 * 50)
        // {
        //     gamestate = LEVEL_2_COMPLETE;
        //     iPauseTimer(0);
        // }
    }
    else if (gamestate == PAUSE)
    {
        // Draw gameplay as background
        draw_bg();
        drawball();
        if (current_level == 1)
        {
            drawlevel1();
            iShowLoadedImage(0 - cameraX, 0, &brick_img);
        }
        else if (current_level == 2)
        {
            drawlevel2();
        }
        draw_pause_menu();
        if (save_button_pressed)
        {
            iSetColor(2,89,15);
            iShowText(345, 108, "Game Saved Successfully!", "assets/fonts/Viga-Regular.ttf", 40);
            save_message_timer--;
            if (save_message_timer <= 0)
                save_button_pressed = false;
        }
    }
    else if (gamestate == GAME_OVER)
    {
        // Score already saved in deathDelayHandler //
        GameOver();
        //iResumeSound(channel);
    }
    else if (gamestate == LEVEL_1_COMPLETE)
    {
        // Score already saved in lev1Complete
        gamestate = LEVEL_2;
        // current_level = 2;
    }
    else if (gamestate == LEVEL_2_COMPLETE)
    {
        draw_bg();
        //drawball();
        drawlevel2();
        iShowLoadedImage(0 - cameraX, 50, &portal);
        iShowLoadedImage(300, 150, &congo_bg_img);
        iPauseTimer(0);
    }
    else if (gamestate == SETTINGS)
    {
        iShowLoadedImage(0, 0, &bg2);
        iShowLoadedImage(30, 530, &back_icon);
        if (sound_on)
        {
            iShowLoadedImage(400, 300, &sound_on_icon);
            // iText();
        }
        else
        {
            iShowLoadedImage(400, 300, &sound_off_icon);
        }
    }
    else if (gamestate == CREDITS)
    {
        iShowLoadedImage(0, 0, &about_us_img);
        //iShowLoadedImage(30, 530, &back_icon);
    }
    else if (gamestate == HELP)
    {
        iShowLoadedImage(0, 0, &instruction_img);
        //iShowLoadedImage(30, 530, &back_icon);
    }
}
void deathDelayHandler()
{
    if (!isdead)
        return;
    deathDelayCounter++;
    if (deathDelayCounter >= 60)
    {
        iPauseTimer(deathTimerIndex);
        lives--;
        isdead = false;
        deathDelayCounter = 0;
        if (lives <= 0)
        {
            if (!scoresaved)
            {
                saveToLeaderboard();
                scoresaved = true;
            }
            iPauseSound(channel);
            channel4 = iPlaySound("assets/Sounds/game_over_sound.wav",false,80);
            gamestate = GAME_OVER;
            //iResumeSound(channel);
        }
        else if (checkPointReached)
        {
            partial_reset();
        }
        else
        {
            initball();
            cameraX = 0;
        }
        ball.isAlive = true;
    }
}
void partial_reset()
{
    ball.x = checkPointX;
    ball.y = checkPointY;
    isJump = true;
    ball.isAlive = true;
    ball.velx = 0;
    ball.vely = 0;
    cameraX = checkPointX - screenWidth / 2;
    if (cameraX < 0)
        cameraX = 0;
    if (current_level == 1)
    {
        if (cameraX > (platformWidth1 - screenWidth))
            cameraX = platformWidth1 - screenWidth;
    }
    else if (current_level == 2)
    {
        if (cameraX > (platformWidth2 - screenWidth))
            cameraX = platformWidth2 - screenWidth;
    }
}
void reset()
{
    brick_count = 0, spike_count = 0, ring_count = 0, star_count = 0, water_count = 0;
    cameraX = 0;
    gravity = -0.9;
    checkPointX = 0;
    checkPointY = 0;
    checkPointReached = false;
    onBrick = true;
    isJump = false;
    isdead = false;
    deathDelayCounter = 0;
    scoresaved = false;
    normal = true;
    ringsCollected = 0;
    iPauseTimer(deathTimerIndex);
    if (current_level == 1)
    {
        initlevel1();
        score = 0;
        lives = 2;
    }
    else if (current_level == 2)
    {
        initlevel2();
        lives = 3;
    }
    initball();
}

// int loadLeaderboard(LboardEntry entries[])
// {
//     FILE *file = fopen("leaderboard.txt", "r");
//     LboardEntry temp[100]; // support up to 100 entries in file
//     int tempCount = 0;
//     int count = 0;

//     if (file != NULL)
//     {
//         while (fscanf(file, "%29s %d", temp[tempCount].name, &temp[tempCount].score) == 2)
//         {
//             tempCount++;
//             if (tempCount >= 100)
//                 break;
//         }
//         fclose(file);
//     }

//     // Keep only highest score for each name
//     for (int i = 0; i < tempCount; i++)
//     {
//         int found = -1;
//         for (int j = 0; j < count; j++)
//         {
//             if (strcmp(entries[j].name, temp[i].name) == 0)
//             {
//                 found = j;
//                 break;
//             }
//         }
//         if (found == -1)
//         {
//             // New name, add
//             entries[count] = temp[i];
//             count++;
//         }
//         else
//         {
//             // Existing name, keep higher score
//             if (temp[i].score > entries[found].score)
//             {
//                 entries[found].score = temp[i].score;
//             }
//         }
//     }

//     // Sort descending by score
//     for (int i = 0; i < count - 1; i++)
//     {
//         for (int j = i + 1; j < count; j++)
//         {
//             if (entries[j].score > entries[i].score)
//             {
//                 LboardEntry tempEntry = entries[i];
//                 entries[i] = entries[j];
//                 entries[j] = tempEntry;
//             }
//         }
//     }

//     // Only show top MAX_LEADERS
//     if (count > MAX_LEADERS)
//         count = MAX_LEADERS;
//     return count;
// }

int loadLeaderboard(LboardEntry entries[])
{
    FILE *file = fopen("leaderboard.txt", "r");
    LboardEntry temp[100];
    int tempCount = 0;

    // Read all entries from file
    if (file != NULL)
    {
        while (fscanf(file, "%29s %d", temp[tempCount].name, &temp[tempCount].score) == 2)
        {
            tempCount++;
            if (tempCount >= 100)
                break;
        }
        fclose(file);
    }

    // Sort all entries by score first (highest to lowest)
    for (int i = 0; i < tempCount - 1; i++)
    {
        for (int j = i + 1; j < tempCount; j++)
        {
            if (temp[j].score > temp[i].score)
            {
                LboardEntry tempEntry = temp[i];
                temp[i] = temp[j];
                temp[j] = tempEntry;
            }
        }
    }

    // Now pick top unique names, but stop at MAX_LEADERS
    int count = 0;
    for (int i = 0; i < tempCount && count < MAX_LEADERS; i++)
    {
        int found = -1;
        for (int j = 0; j < count; j++)
        {
            if (strcmp(entries[j].name, temp[i].name) == 0)
            {
                found = j;
                break;
            }
        }

        if (found == -1)
        {
            // New unique name, add it
            entries[count] = temp[i];
            count++;
        }
        else
        {
            // Name already exists, keep higher score (temp is already sorted)
            if (temp[i].score > entries[found].score)
            {
                entries[found].score = temp[i].score;
            }
        }
    }

    return count;
}
void drawLeaderboard()
{
    iShowLoadedImage(0, 0, &leaderboard_img);
    iSetColor(17, 18, 17);
    iFilledRectangle(1000, 530, 80, 50);
    iSetColor(255, 255, 255);
    iShowText(1010, 550, "BACK", "assets/fonts/Super Greatly.ttf", 25);
    LboardEntry leaders[MAX_LEADERS];
    int count = loadLeaderboard(leaders);

    int nameX = 220;
    int scoreX = 730;
    int startY = 369;
    int lineHeight = 40;
    int fontSize = 36;

    for (int i = 0; i < count; i++)
    {
        char nameline[100], scoreline[100];
        sprintf(nameline, "%d. %s", i + 1, leaders[i].name);
        sprintf(scoreline, "%d", leaders[i].score);
        iSetColor(0, 0, 0);
        iShowText(nameX, startY - i * lineHeight, nameline, "assets/fonts/Super Greatly.ttf", fontSize);
        iShowText(scoreX, startY - i * lineHeight, scoreline, "assets/fonts/Super Greatly.ttf", fontSize);
    }
}

void iMouseMove(int mx, int my)
{
    printf("mx=%d, my=%d\n", mx, my);
}

void iMouseDrag(int mx, int my)
{
    // place your codes here
}

void iMouseWheel(int dir, int mx, int my)
{
    // place your codes here
}

void iMouseClick(int button, int state, int mx, int my)
{
    if (gamestate == MENU)
    {
        if (mx >= 785 && mx <= 1075 && my >= 500 && my <= 570 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // NEWGAME
        {
            current_level = 1;
            reset();
            gamestate = NAME_INPUT;
        }
        else if (mx >= 785 && mx <= 1075 && my >= 402 && my <= 468 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // LOADGAME
        {
            loadGame();
        }
        else if (mx >= 785 && mx <= 1075 && my >= 302 && my <= 368 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // LEADERBOARD
        {
            gamestate = LEADERBOARD;
        }
        else if (mx >= 785 && mx <= 1075 && my >= 202 && my <= 268 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // help
        {
            gamestate = HELP;
        }
        else if (mx >= 29 && mx <= 88 && my >= 96 && my <= 150 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // setiings
        {
            gamestate = SETTINGS;
        }
        else if (mx >= 1012 && mx <= 1070 && my >= 96 && my <= 150 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // credits
        {
            gamestate = CREDITS;
        }
        else if (mx >= 520 && mx <= 575 && my >= 100 && my <= 155 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            exit(0);
        }
    }
    else if (gamestate == SETTINGS)
    {
        if (mx >= 400 && mx <= 600 && my >= 300 && my < 400 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && sound_on)
        {
            sound_on = false;
            iPauseSound(channel);
        }
        else if (mx >= 400 && mx <= 600 && my >= 300 && my < 400 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !sound_on)
        {
            sound_on = true;
            iResumeSound(channel);
        }
        else if (mx >= 50 && mx <= 150 && my >= 530 && my <= 580 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gamestate = MENU;
        }
    }
    else if ((mx >= 250 + 70 && mx <= 250 + 70 + 168) && (my >= 150 + 30 && my <= 150 + 30 + 55) && gamestate == NAME_INPUT)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            nameEntered = false;
            memset(currPlayerName, 0, sizeof(currPlayerName));
            gamestate = MENU;
        }
    }
    else if (gamestate == NAME_INPUT && (mx >= 610 && mx <= 610 + 168) && (my >= 150 + 30 && my <= 150 + 30 + 55))
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (strlen(currPlayerName) > 0)
            {
                nameEntered = true;
                gamestate = LEVEL_1;
                current_level = 1;
                reset();
                iResumeTimer(0);
            }
        }
    }
    else if (gamestate == LEADERBOARD)
    {
        if (mx >= 1000 && mx <= 1100 && my >= 530 && my <= 600 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gamestate = MENU;
        }
    }
    // else if ((mx >= 312 && mx <= 412) && (my >= 10 && my <= 110) && (gamestate == LEVEL_1 || gamestate == LEVEL_2)) //pause
    // {
    //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    //     {
    //         previousState = gamestate;
    //         gamestate = PAUSE;
    //         iPauseTimer(0);
    //     }
    // }
    // else if ((mx >= 312 && mx <= 412) && (my >= 70 && my <= 170) && gamestate == PAUSE) // resume
    // {
    //     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    //     {
    //         gamestate = previousState;
    //         iResumeTimer(0);
    //     }
    // }
    else if (gamestate == LEVEL_1 || gamestate == LEVEL_2)//pause
    {
        if (mx >= 1040 && mx <= 1080 && my >= 550 && my <= 590 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            previousState = gamestate;
            gamestate = PAUSE;
            iPauseTimer(0);
        }
    }
    else if ((mx >= 312 && mx <= 412) && (my >= 322 && my <= 400) && gamestate == PAUSE) // restart
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            reset();
            gamestate = previousState;
            iResumeTimer(0);
        }
    }
    else if ((mx >= 312 && mx <= 412) && (my >= 190 && my <= 290) && gamestate == PAUSE) // goto menu
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (!scoresaved)
            {
                saveToLeaderboard();
                scoresaved = true;
            }
            gamestate = MENU;
            iResumeTimer(0);
            reset();
        }
    }
    else if ((mx >= 432 && mx <= 788) && (my >= 204 && my <= 280) && gamestate == PAUSE)//save game
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            saveGame();
            save_button_pressed = true;
            save_message_timer = 200;
        }
    }
    else if ((mx >= 440 && mx <= 775) && (my >= 315 && my <= 405) && gamestate == PAUSE)//resume
    {
        gamestate = previousState;
        iResumeTimer(0);
    }
    else if (gamestate == CREDITS)
    {
        if (mx >= 42 && mx <= 102 && my >= 503 && my <= 568 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gamestate = MENU;
        }
    }
    else if (gamestate == HELP)
    {
        if (mx >= 33 && mx <= 83 && my >= 530 && my <= 580 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gamestate = MENU;
        }
    }
    else if(gamestate == GAME_OVER)
    {
        if (mx >= 388 && mx <= 715 && my >= 115 && my <= 188 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            iResumeSound(channel);
            gamestate = MENU;
        }
    }
    else if (gamestate == LEVEL_2_COMPLETE)
    {
        if (mx >= 580 && mx <= 761 && my >= 150 && my <= 230 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gamestate = MENU;
            //iResumeTimer(0);
        }
        if (mx >= 380 && mx <= 580 && my >= 150 && my <= 230 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            gamestate = LEADERBOARD;
            //iResumeTimer(0);
        }
}
    printf("%d %d\n", mx, my);
}

void iKeyPress(unsigned char key)
{
    if (gamestate == NAME_INPUT && !nameEntered)
    {
        int len = strlen(currPlayerName);
        if (key == '\b')
        {
            if (len > 0)
                currPlayerName[len - 1] = '\0';
        }
        else if (key == '\r' || key == '\n')
        {
            nameEntered = true;
        }
        else if (len < MAX_NAME_LEN - 1 && key >= 32 && key <= 126) // Printable ASCII
        {
            currPlayerName[len] = key;
            currPlayerName[len + 1] = '\0';
        }
        return;
    }

    if (key == 'p')
    {
        if (gamestate != PAUSE)
        {
            previousState = gamestate;
            gamestate = PAUSE;
            iPauseTimer(0);
            // printf("%d %d %d", ball.x, ball.y, lives);
        }
    }
    if (key == 'r')
    {
        if (gamestate == PAUSE)
        {
            gamestate = previousState;
            iResumeTimer(0);
        }
    }
}

void iSpecialKeyPress(unsigned char key)
{
    if (gamestate == PAUSE)
        return; // Ignore key presses when paused

    if (normal)
    {
        switch (key)
        {
        case GLUT_KEY_RIGHT:
            moveright = true;
            moveleft = false;
            if (!isJump && ball.isAlive)
                moveball();
            break;
        case GLUT_KEY_LEFT:
            moveleft = true;
            moveright = false;
            if (!isJump && ball.isAlive)
                moveball();
            break;
        case GLUT_KEY_UP:
            // Normal gravity: jump up from ground or brick
            if (gravity < 0 && !isJump && ball.isAlive && (ball.y == ground || onBrick))
            {
                ball.vely = 24.5;
                isJump = true;
                moveleft = false;
                moveright = false;
            }
            // Reverse gravity: jump up from lower platform (fall up)
            else if (gravity > 0 && !isJump && ball.isAlive && ball.y == ground)
            {
                ball.vely = 24.5;
                isJump = true;
                moveleft = false;
                moveright = false;
            }
            break;
        case GLUT_KEY_DOWN:

            // Reverse gravity: jump down from brick (stay still on brick, jump down if down key pressed)
            if (gravity > 0 && !isJump && ball.isAlive)
            {
                int onPlatform = (screenHeight - platformHeight - ball.radius);
                if (onBrick || ball.y == onPlatform)
                {
                    ball.vely = -24.5;
                    isJump = true;
                    moveleft = false;
                    moveright = false;
                }
            }
            break;
        case GLUT_KEY_END:
            gamestate = MENU;
            break;

        default:
            break;
        }
    }
    else
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
            moveright = true;
            moveleft = false;
            if (!isJump && ball.isAlive)
                moveball();
            break;
        case GLUT_KEY_RIGHT:
            moveleft = true;
            moveright = false;
            if (!isJump && ball.isAlive)
                moveball();
            break;
        case GLUT_KEY_DOWN:
            // Normal gravity: jump up from ground or brick
            if (gravity < 0 && !isJump && ball.isAlive && (ball.y == ground || onBrick))
            {
                ball.vely = 24.5;
                isJump = true;
                moveleft = false;
                moveright = false;
            }
            // Reverse gravity: jump up from lower platform (fall up)
            else if (gravity > 0 && !isJump && ball.isAlive && ball.y == ground)
            {
                ball.vely = 24.5;
                isJump = true;
                moveleft = false;
                moveright = false;
            }
            break;
        case GLUT_KEY_UP:

            // Reverse gravity: jump down from brick (stay still on brick, jump down if down key pressed)
            if (gravity > 0 && !isJump && ball.isAlive)
            {
                int onPlatform = (screenHeight - platformHeight - ball.radius);
                if (onBrick || ball.y == onPlatform)
                {
                    ball.vely = -24.5;
                    isJump = true;
                    moveleft = false;
                    moveright = false;
                }
            }
            break;
        default:
            break;
        }
    }
}

void iSpecialKeyRelease(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        moveright = false;
        break;
    case GLUT_KEY_LEFT:
        moveleft = false;
        break;
    default:
        // Ignore all other special keys (including SHIFT, CTRL, etc.)
        return;
    }
}

void moveball1()
{
    ball.velx = 12;

    if (moveright)
    {
        ball.x += ball.velx;
        checkBrickCollision1();
        checklanding();
        checkSpikeCollision1();
        checkStarCollision1();
        checkWaterCollision1();
        checkRingCollision1();
        lev1Complete();
        if (ball.x - cameraX > screenWidth / 2 && cameraX + screenWidth < platformWidth1)
        {
            cameraX += ball.velx;
        }
    }
    if (moveleft)
    {
        ball.x -= ball.velx;
        checkBrickCollision1();
        checklanding();
        checkSpikeCollision1();
        checkStarCollision1();
        checkWaterCollision1();
        checkRingCollision1();
        lev1Complete();
        if (ball.x - cameraX < screenWidth / 2 && cameraX > 0)
        {
            cameraX -= ball.velx;
            if (cameraX < 0)
                cameraX = 0;
        }
    }
}

void balljump1()
{
    if (gamestate == PAUSE)
        return; // Don't update ball when paused
    if (isJump)
    {
        ball.y += ball.vely;
        ball.vely += gravity;

        checkBrickCollision1();
        checklanding();
        checkSpikeCollision1();
        checkStarCollision1();
        checkWaterCollision1();
        checkRingCollision1();
        lev1Complete();
        float nextY = ball.y + ball.vely;

        if (nextY <= ground)
        {
            ball.y = ground;
            ball.vely = 0;
            isJump = false;
        }
        else
        {
            midairmovement1();
        }
    }
}

void midairmovement1()
{
    moveright = isSpecialKeyPressed(GLUT_KEY_RIGHT);
    moveleft = isSpecialKeyPressed(GLUT_KEY_LEFT);
    moveball1();
}

void saveToLeaderboard()
{
    FILE *file = fopen("leaderboard.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s %d\n", currPlayerName, score);
        fclose(file);
    }
}

void lev1Complete()
{
    if (gamestate == LEVEL_1 && ball.x >= 102.2 * 50)
    {
        if (!scoresaved)
        {
            saveToLeaderboard();
            scoresaved = true;
        }
        gamestate = LEVEL_2;
        if (current_level != 2)
        {
            current_level = 2;
            reset();
        }
    }
}

void saveGame()
{
    FILE *fptr = fopen("savegame.txt", "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "%d\n", current_level);
        fprintf(fptr, "%s %d %d %d %d %f %d %d %d\n", currPlayerName, score, lives, ball.x, ball.y, ball.vely, isJump, cameraX, gamestate);
        // rings
        fprintf(fptr, "%d ", ringsCollected);
        if (current_level == 1)
        {
            for (int i = 0; i < ring_count; i++)
            {
                if (rings[i].isCollected)
                    fprintf(fptr, "%d ", 1);
                else
                    fprintf(fptr, "%d ", 0);
            }
            fprintf(fptr, "\n");
            // waters
            for (int i = 0; i < water_count; i++)
            {
                if (waters[i].isCollected)
                    fprintf(fptr, "%d ", 1);
                else
                    fprintf(fptr, "%d ", 0);
            }
            fprintf(fptr, "\n");
            // checkpoints
            for (int i = 0; i < star_count; i++)
            {
                if (stars[i].isCollected)
                    fprintf(fptr, "%d ", 1);
                else
                    fprintf(fptr, "%d ", 0);
            }
        }
        else if (current_level == 2)
        {
            for (int i = 0; i < ring_count; i++)
            {
                if (rings2[i].isCollected)
                    fprintf(fptr, "%d ", 1);
                else
                    fprintf(fptr, "%d ", 0);
            }
            fprintf(fptr, "\n");
            // waters
            for (int i = 0; i < water_count; i++)
            {
                if (waters2[i].isCollected)
                    fprintf(fptr, "%d ", 1);
                else
                    fprintf(fptr, "%d ", 0);
            }
            fprintf(fptr, "\n");
            // checkpoints
            for (int i = 0; i < star_count; i++)
            {
                if (stars2[i].isCollected)
                    fprintf(fptr, "%d ", 1);
                else
                    fprintf(fptr, "%d ", 0);
            }
            fprintf(fptr, "\n");
            fprintf(fptr, "%f ", gravity);
            fprintf(fptr, "%d", normal);
        }
        fprintf(fptr, "\n");
        fprintf(fptr, "%d %d %d", checkPointX, checkPointY, checkPointReached);
        fclose(fptr);
    }
    saved_level = current_level;
}

void loadGame()
{
    FILE *fptr = fopen("savegame.txt", "r");
    if (fptr != NULL)
    {
        fscanf(fptr, "%d", &saved_level);
        current_level = saved_level;
        reset();
        int temp_isJump;
        fscanf(fptr, "%s %d %d %d %d %f %d %d %d", currPlayerName, &score, &lives, &ball.x, &ball.y, &ball.vely, &temp_isJump, &cameraX, &gamestate);
        isJump = temp_isJump;
        fscanf(fptr, "%d", &ringsCollected);

        if (saved_level == 1)
        {
            for (int i = 0; i < ring_count; i++)
            {
                int val;
                fscanf(fptr, "%d", &val);
                if (val)
                    rings[i].isCollected = true;
                else
                    rings[i].isCollected = false;
            }
            for (int i = 0; i < water_count; i++)
            {
                int val;
                fscanf(fptr, "%d", &val);
                if (val)
                    waters[i].isCollected = true;
                else
                    waters[i].isCollected = false;
            }
            for (int i = 0; i < star_count; i++)
            {
                int val;
                fscanf(fptr, "%d", &val);
                if (val)
                    stars[i].isCollected = true;
                else
                    stars[i].isCollected = false;
            }
        }
        else if (saved_level == 2)
        {
            for (int i = 0; i < ring_count; i++)
            {
                int val;
                fscanf(fptr, "%d", &val);
                if (val)
                    rings2[i].isCollected = true;
                else
                    rings2[i].isCollected = false;
            }
            for (int i = 0; i < water_count; i++)
            {
                int val;
                fscanf(fptr, "%d", &val);
                if (val)
                    waters2[i].isCollected = true;
                else
                    waters2[i].isCollected = false;
            }
            for (int i = 0; i < star_count; i++)
            {
                int val;
                fscanf(fptr, "%d", &val);
                if (val)
                    stars2[i].isCollected = true;
                else
                    stars2[i].isCollected = false;
            }
            fscanf(fptr, "%f", &gravity);
            fscanf(fptr, "%d", &normal);
        }
        fscanf(fptr, "%d %d %d", &checkPointX, &checkPointY, &checkPointReached);
        fclose(fptr);
    }
    if (current_level == 1)
        gamestate = LEVEL_1;
    else if (current_level == 2)
        gamestate = LEVEL_2;
}

void balljump()
{
    if (current_level == 1)
    {
        balljump1();
    }
    else if (current_level == 2)
    {
        balljump2();
        lev2Complete();
    }
}

void moveball()
{
    if (current_level == 1)
    {
        moveball1();
    }
    else if (current_level == 2)
    {
        moveball2();
        lev2Complete();
    }
}
void lev2Complete()
{
    if (gamestate == LEVEL_2 && ball.x >= 139 * 50)
    {
        if (!scoresaved)
        {
            saveToLeaderboard();
            scoresaved = true;
        }
        iPauseTimer(0);
        gamestate = LEVEL_2_COMPLETE;
    }
}

int main(int argc, char *argv[])
{
    // reset();
    loadresources();
    iInitializeSound();
    channel = iPlaySound("assets/sounds/game_bm.mp3", true, 50);
    // channel2 =iPlaySound("assets/sounds/gravity_sound.mp3", false , 50 );
    deathTimerIndex = iSetTimer(16, deathDelayHandler);
    iPauseTimer(deathTimerIndex);
    iSetTimer(16, balljump);
    iWindowedMode(screenWidth, screenHeight, "GAME");
    iStartMainLoop();
    return 0;
}