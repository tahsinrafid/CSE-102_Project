
#ifndef LEVEL2_H
#define LEVEL2_H

#include "globals.h"
#include "iFont.h"
#include "iSound.h"
// Level 2 function declarations (all with '2' suffix)
void loadresources2();
void initlevel2();
void drawlevel2();
void checklanding2();

void checkBrickCollision2();
void checkSpikeCollision2();
void checkRingCollision2();
void checkStarCollision2();
void checkWaterCollision2();
void check_gravity_perk_collision();
void check_reverse_key_collision();

void balljump2();
void moveball2();
void midairmovement2();
void draw_moving_spike2();
void GameOver();
void lev2Complete();

#endif // LEVEL2_H
// All functions have been renamed with a "2" at the end.

void loadresources2()
{
    // Using existing global Image variables from iMain.cpp
    iLoadImage(&menu, "assets/images/newmenu.jpg");
    iResizeImage(&menu, screenWidth, screenHeight);
    iLoadImage(&brick_img, "assets/images/brick.png");
    iResizeImage(&brick_img, brickW, brickW);
    iLoadImage(&bg, "assets/images/levelbg1.png");
    iLoadImage(&spike_img, "assets/images/spike.png");
    iLoadImage(&water_img, "assets/images/Water@2x.png");
    iResizeImage(&water_img, 62, 62);
    iLoadImage(&star_img, "assets/images/Star@2x.png");
    iResizeImage(&star_img, 55, 55);
    iLoadImage(&ring_img, "assets/images/ring_small@2x.png");
    iResizeImage(&ring_img, 30, 90);
    iLoadImage(&ring_rotated_img, "assets/images/ring_rotated@2x.png");
    iResizeImage(&ring_rotated_img, 90, 30);
    // iLoadImage(&bg2, "assets/images/bg2.jpg");
    // iResizeImage(&bg2, screenWidth, screenHeight);
    iLoadImage(&checkpoint_img, "assets/images/Star@2x.png");
    iResizeImage(&checkpoint_img, 30, 30);
    iLoadImage(&checkpoint_reached, "assets/images/checkpoint_catched@2x.png");
    iResizeImage(&checkpoint_reached, 30, 30);
    iLoadImage(&pause, "assets/images/pause.png");
    iResizeImage(&pause, 800, 400);
    iLoadImage(&gameover_img, "assets/images/gameover.png");
    iLoadImage(&life_img, "assets/images/Water@3x.png");
    iResizeImage(&life_img, 30, 30);
    iLoadImage(&thorn_img, "assets/images/dyn_thorn@2x.png");
    iResizeImage(&thorn_img, 50, 50);

    iInitSprite(&ball.sprite);
    iLoadFramesFromFolder(ball.img, "assets/images/sprites/BallFrames/Moving");
    iChangeSpriteFrames(&ball.sprite, ball.img, 1);
    iResizeSprite(&ball.sprite, 60, 60);

    iLoadImage(&restart_icon, "assets/images/restart_icon.png");
    iLoadImage(&menu_icon, "assets/images/menu_icon.png");
    iLoadImage(&resume_icon, "assets/images/resume_icon.png");
    iLoadImage(&sound_on_icon, "assets/images/sound_on_icon.png");
    iLoadImage(&sound_off_icon, "assets/images/sound_off_icon.png");
    iLoadImage(&restart_button, "assets/images/restart_button.png");
    iResizeImage(&restart_button, 150, 50);
    iLoadImage(&menu_button, "assets/images/menu_button.png");
    iResizeImage(&menu_button, 150, 50);
    iLoadImage(&leaderboard, "assets/images/Leaderboard_UI.png");
    iResizeImage(&leaderboard, screenWidth, screenHeight);
    iLoadImage(&congo_img, "assets/images/congo_img.png");
    iLoadImage(&next_level_img, "assets/images/next_level.png");
    iLoadImage(&complete_star, "assets/images/complete_star.png");
    iLoadImage(&reverse_gravity_img, "assets/images/reverse_gravity.png");
    iResizeImage(&reverse_gravity_img, 50, 50);
    iLoadImage(&reverse_gravity_2_img, "assets/images/reverse_gravity_2.png");
    iResizeImage(&reverse_gravity_2_img, 50, 50);

    iLoadImage(&pop_img, "assets/images/sprites/BallFrames/Moving/ball_pop.png");
}

void initlevel2()
{
    // Reset counts
    brick_count = 0;
    spike_count = 0;
    ring_count = 0;
    star_count = 0;
    water_count = 0;
    printf("%d\n", current_level);
    printf("%d\n",saved_level);
    for (int i = 0; i < 142; i++)
    {
        bricks[brick_count].x = i * brickW;
        bricks[brick_count].y = 0;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = true;
        brick_count++;
    }
    // draw upper platform
    for (int i = 0; i < 142; i++)
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
            brick_count++;
        }
        k = brickW;
    }
    k = 0;
    for (int j = 0; j < 7; j++)
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
    k = 6 * brickW;
    for (int j = 0; j < 1; j++)
    {
        for (int i = 0; i < 7; i++)
        {
            bricks[brick_count].x = 16 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
    }
    k = 5 * brickW;
    for (int j = 0; j < 1; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 21 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 25 * brickW + i * brickW;
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
            bricks[brick_count].x = 29 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            bricks[brick_count].x = 33 * brickW + j * brickW;
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
        for (int i = 0; i < 5; i++)
        {
            bricks[brick_count].x = 39 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 50 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 7; j++)
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
        k -= brickW;
    }
    k = screenHeight - 2 * brickW;
    for (int i = 0; i < 5; i++)
    {
        bricks[brick_count].x = 76 * brickW;
        bricks[brick_count].y = k - i * brickW;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = brickW;
    for (int i = 0; i < 3; i++)
    {
        bricks[brick_count].x = 76 * brickW;
        bricks[brick_count].y = k - i * brickW;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = screenHeight - 2 * brickW;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            bricks[brick_count].x = 80 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = brickW;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            bricks[brick_count].x = 80 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = brickW;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 86 * brickW + i * brickW;
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
            bricks[brick_count].x = 90 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = 5 * brickW;
    for (int i = 0; i < 5; i++)
    {
        bricks[brick_count].x = 96 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = brickW;
    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 100 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = screenWidth - 2 * brickW;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 105 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k -= brickW;
    }
    k = brickW;
    for (int i = 0; i < 3; i++)
    {
        bricks[brick_count].x = 110 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = 2 * brickW;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 1; i++)
        {
            bricks[brick_count].x = 112 * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = 5 * brickW;
    for (int i = 0; i < 3; i++)
    {
        bricks[brick_count].x = 112 * brickW + i * brickW;
        bricks[brick_count].y = k;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = 5 * brickW;
    for (int i = 0; i < 3; i++)
    {
        bricks[brick_count].x = 114 * brickW;
        bricks[brick_count].y = k + i * brickW;
        bricks[brick_count].width = bricks[brick_count].height = brickW;
        bricks[brick_count].isVisible = true;
        bricks[brick_count].isGround = false;
        brick_count++;
    }
    k = 6 * brickW;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            bricks[brick_count].x = 115 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = brickW;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 122 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = brickW;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 128 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    k = brickW;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            bricks[brick_count].x = 134 * brickW + i * brickW;
            bricks[brick_count].y = k;
            bricks[brick_count].width = bricks[brick_count].height = brickW;
            bricks[brick_count].isVisible = true;
            bricks[brick_count].isGround = false;
            brick_count++;
        }
        k += brickW;
    }
    // initialize spikes2
    spikes2[spike_count] = (Spike){.x = 17 + 17 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 17 + 21 * brickW, .y = 7 * brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 17 + 31 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 10 + 36 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 10 + 42 * brickW, .y = 6 * brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 58 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 59 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 60 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 61 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 62 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 63 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 85 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 98 * brickW, .y = 6 * brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 111 * brickW, .y = 2 * brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 124 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 126 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 130 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;
    spikes2[spike_count] = (Spike){.x = 132 * brickW, .y = brickW, .width = spikeW, .height = spikeH, .isVisible = true};
    spike_count++;

    // initialize rings2
    rings2[ring_count] = (Ring){.x = 5 + 9 * brickW, .y = brickW + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 17 + 16 * brickW - 5, .y = brickW + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 23 * brickW, .y = 5 * brickW + 5, .width = ringW, .height = ringH, .isRotated = true, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 34 * brickW, .y = brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 39 * brickW, .y = 6 * brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 50 * brickW, .y = brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 69 * brickW, .y = brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 76 * brickW, .y = 2 * brickW + spikeH + 5, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 83 * brickW, .y = brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 88 * brickW, .y = 5 * brickW, .width = ringW, .height = ringH, .isRotated = true, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 97 * brickW, .y = 6 * brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 113 * brickW, .y = brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 122 * brickW, .y = 6 * brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 128 * brickW, .y = 6 * brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;
    rings2[ring_count] = (Ring){.x = 5 + 134 * brickW, .y = 6 * brickW, .width = ringW, .height = ringH, .isRotated = false, .isCollected = false};
    ring_count++;

    // initialize stars2(checkpoints)
    stars2[star_count] = (Star){.x = 38 * brickW, .y = brickW, .width = starW, .height = starH, .isVisible = true, .isCollected = false};
    star_count++;
    stars2[star_count] = (Star){.x = 56 * brickW, .y = 7 * brickW, .width = starW, .height = starH, .isVisible = true, .isCollected = false};
    star_count++;
    stars2[star_count] = (Star){.x = 90 * brickW, .y = brickW, .width = starW, .height = starH, .isVisible = true, .isCollected = false};
    star_count++;
    stars2[star_count] = (Star){.x = 114 * brickW, .y = brickW, .width = starW, .height = starH, .isVisible = true, .isCollected = false};
    star_count++;

    // initialize waters2
    waters2[water_count] = (Water){.x = 73 * brickW, .y = 6 * brickW, .width = 30, .height = 30, .isCollected = false};
    water_count++;
    waters2[water_count] = (Water){.x = 103 * brickW, .y = 6 * brickW, .width = 30, .height = 30, .isCollected = false};
    water_count++;

    // reverse_gravity
    gravity_perks[0] = (GravityPerk){.x = 33 * brickW, .y = brickW, .width = brickW, .height = brickW, .isVisible = true, .isReversed = false};
    gravity_perks[1] = (GravityPerk){.x = 92 * brickW, .y = screenHeight - 2 * brickW, .width = brickW, .height = brickW, .isVisible = true, .isReversed = true};

    // reverse_key
    reverse_keys[0] = (reverse_key){.x = 50 * brickW, .y = 3 * brickW, .width = 50, .height = 50, .isVisible = true};
    reverse_keys[1] = (reverse_key){.x = 86 * brickW, .y = 7 * brickW, .width = 50, .height = 50, .isVisible = true};
}

void draw_moving_spike2()
{
    static int y[6] = {100, 200, 300, 400, 500, 100}; // initial y positions for 5 thorns
    static bool upmove[6] = {true, false, true, false, true, false};
    float speed = 1;
    for (int idx = 0; idx < 2; idx++)
    {
        // Give random x for demonstration (replace with your logic later)
        thornes[idx].x = 65 * brickW + (idx * 100);
        thornes[idx].isVisible = true;
        thornes[idx].height = spikeH;
        thornes[idx].width = spikeW;

        if (upmove[idx])
        {
            y[idx] += speed;
            if (y[idx] >= screenHeight - 2 * spikeH)
                upmove[idx] = false;
        }
        else
        {
            y[idx] -= speed;
            if (y[idx] <= brickW)
                upmove[idx] = true;
        }
        thornes[idx].y = y[idx];
        iShowLoadedImage(thornes[idx].x - cameraX, thornes[idx].y, &thorn_img);
        // Collision detection for moving thorns
        if (ball.isAlive &&
            ball.x + ball.radius > thornes[idx].x &&
            ball.x - ball.radius < thornes[idx].x + thornes[idx].width &&
            ball.y + ball.radius > thornes[idx].y &&
            ball.y - ball.radius < thornes[idx].y + thornes[idx].height)
        {
            popX = ball.x;
            popY = ball.y;
            channel3 = iPlaySound("assets/Sounds/ball_pop_sound.mp3",false, 50);
            //score -= 50;
            ball.isAlive = false;
            isdead = true;
            iResumeTimer(deathTimerIndex);
            deathDelayCounter = 0;
        }
    }
    for (int idx = 2; idx < 4; idx++)
    {
        // Give random x for demonstration (replace with your logic later)
        thornes[idx].x = 101 * brickW + (idx * 100);
        thornes[idx].isVisible = true;
        thornes[idx].height = spikeH;
        thornes[idx].width = spikeW;
        if (upmove[idx])
        {
            y[idx] += speed;
            if (y[idx] >= screenHeight - 2 * spikeH)
                upmove[idx] = false;
        }
        else
        {
            y[idx] -= speed;
            if (y[idx] <= brickW)
                upmove[idx] = true;
        }
        thornes[idx].y = y[idx];
        iShowLoadedImage(thornes[idx].x - cameraX, thornes[idx].y, &thorn_img);
        // Collision detection for moving thorns
        if (ball.isAlive &&
            ball.x + ball.radius > thornes[idx].x &&
            ball.x - ball.radius < thornes[idx].x + thornes[idx].width &&
            ball.y + ball.radius > thornes[idx].y &&
            ball.y - ball.radius < thornes[idx].y + thornes[idx].height)
        {
            popX = ball.x;
            popY = ball.y;
            channel3=iPlaySound("assets/Sounds/ball_pop_sound.mp3",false, 50);
            //score -= 50;
            ball.isAlive = false;
            isdead = true;
            iResumeTimer(deathTimerIndex);
            deathDelayCounter = 0;
        }
    }
    for (int idx = 4; idx < 5; idx++)
    {
        // Give random x for demonstration (replace with your logic later)
        thornes[idx].x = 111 * brickW + (idx * 100);
        thornes[idx].isVisible = true;
        thornes[idx].height = spikeH;
        thornes[idx].width = spikeW;
        if (upmove[idx])
        {
            y[idx] += speed;
            if (y[idx] >= screenHeight - 2 * spikeH)
                upmove[idx] = false;
        }
        else
        {
            y[idx] -= speed;
            if (y[idx] <= brickW)
                upmove[idx] = true;
        }
        thornes[idx].y = y[idx];
        iShowLoadedImage(thornes[idx].x - cameraX, thornes[idx].y, &thorn_img);
        // Collision detection for moving thorns
        if (ball.isAlive &&
            ball.x + ball.radius > thornes[idx].x &&
            ball.x - ball.radius < thornes[idx].x + thornes[idx].width &&
            ball.y + ball.radius > thornes[idx].y &&
            ball.y - ball.radius < thornes[idx].y + thornes[idx].height)
        {
            popX = ball.x;
            popY = ball.y;
            channel3=iPlaySound("assets/Sounds/ball_pop_sound.mp3",false, 50);
            //score -= 50;
            ball.isAlive = false;
            isdead = true;
            iResumeTimer(deathTimerIndex);
            deathDelayCounter = 0;
        }
    }
}

void drawlevel2()
{
    for (int i = 0; i < brick_count; i++)
    {
        if (bricks[i].isVisible)
        {
            iShowLoadedImage(bricks[i].x - cameraX, bricks[i].y, &brick_img);
        }
    }
    for (int i = 0; i < spike_count; i++)
    {
        if (spikes2[i].isVisible)
        {
            iShowLoadedImage(spikes2[i].x - cameraX, spikes2[i].y, &spike_img);
        }
    }
    for (int i = 0; i < ring_count; i++)
    {
        if (!rings2[i].isRotated)
        {
            if (!rings2[i].isCollected)
                iShowLoadedImage(rings2[i].x - cameraX, rings2[i].y, &ring_img);
            else
                iShowLoadedImage(rings2[i].x - cameraX, rings2[i].y, &ring_collected_img);
        }
        else
        {
            if (!rings2[i].isCollected)
                iShowLoadedImage(rings2[i].x - cameraX, rings2[i].y, &ring_rotated_img);
            else
                iShowLoadedImage(rings2[i].x - cameraX, rings2[i].y, &ring_rotated_col_img);
        }
    }
    for (int i = 0; i < star_count; i++)
    {
        if (!stars2[i].isCollected)
        {
            iShowLoadedImage(stars2[i].x - cameraX, stars2[i].y, &star_img);
        }
    }
    for (int i = 0; i < star_count; i++)
    {
        if (stars2[i].isCollected)
        {
            iShowLoadedImage(stars2[i].x - cameraX, stars2[i].y, &checkpoint_catched_img);
        }
    }
    for (int i = 0; i < water_count; i++)
    {
        if (!waters2[i].isCollected)
        {
            iShowLoadedImage(waters2[i].x - cameraX, waters2[i].y, &water_img);
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (gravity_perks[i].isVisible)
        {
            if (!gravity_perks[i].isReversed)
            {
                iShowLoadedImage(gravity_perks[i].x - cameraX, gravity_perks[i].y, &reverse_gravity_img);
            }
            else
            {
                iShowLoadedImage(gravity_perks[i].x - cameraX, gravity_perks[i].y, &reverse_gravity_2_img);
            }
        }
    }
    for (int i = 0; i < 2; i++)
    {
        if (reverse_keys[i].isVisible)
        {
            iShowLoadedImage(reverse_keys[i].x - cameraX, reverse_keys[i].y, &reverse_key_img);
        }
    }
    draw_moving_spike2();
    iShowLoadedImage(138 * 50 - cameraX, 45, &game_win_star);
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

void check_gravity_perk_collision()
{
    for (int i = 0; i < 2; i++)
    {
        GravityPerk g = gravity_perks[i];
        if (gravity_perks[i].isVisible)
        {
            bool hitup = (ball.x + ball.radius > g.x &&
                          ball.x - ball.radius < g.x + g.width &&
                          ball.y >= g.y + g.height &&
                          ball.y + ball.vely <= g.y + g.height);

            // check hitting from down
            bool hitdown = (ball.x + ball.radius > g.x &&
                            ball.x - ball.radius < g.x + g.width &&
                            ball.y <= g.y &&
                            ball.y + ball.vely >= g.y);

            // check hitting from left
            bool hitleft = (ball.x < g.x &&
                            ball.x + ball.radius >= g.x &&
                            ball.y + ball.radius > g.y &&
                            ball.y - ball.radius < g.y + g.height);

            // check hitting from right
            bool hitright = (ball.x > g.x + g.width &&
                             ball.x - ball.radius <= g.x + g.width &&
                             ball.y + ball.radius > g.y &&
                             ball.y - ball.radius < g.y + g.height);

            if (hitup || hitdown || hitleft || hitright)
            {
                if (!gravity_perks[i].isReversed && gravity < 0)
                {
                    gravity = 0.9;
                    channel2 =iPlaySound("assets/sounds/gravity_sound.mp3", false , 50 );
                }
                else if (gravity_perks[i].isReversed && gravity > 0)
                {
                    gravity = -0.9;
                    channel2 =iPlaySound("assets/sounds/gravity_sound.mp3", false , 50 );
                }
            }
        }
    }
}

void check_reverse_key_collision()
{
    for (int i = 0; i < 2; i++)
    {
        reverse_key r = reverse_keys[i];
        if (reverse_keys[i].isVisible)
        {
            bool hitup = (ball.x + ball.radius > r.x &&
                          ball.x - ball.radius < r.x + r.width &&
                          ball.y >= r.y + r.height &&
                          ball.y + ball.vely <= r.y + r.height);

            // check hitting from down
            bool hitdown = (ball.x + ball.radius > r.x &&
                            ball.x - ball.radius < r.x + r.width &&
                            ball.y <= r.y &&
                            ball.y + ball.vely >= r.y);

            // check hitting from left
            bool hitleft = (ball.x < r.x &&
                            ball.x + ball.radius >= r.x &&
                            ball.y + ball.radius > r.y &&
                            ball.y - ball.radius < r.y + r.height);

            // check hitting from right
            bool hitright = (ball.x > r.x + r.width &&
                             ball.x - ball.radius <= r.x + r.width &&
                             ball.y + ball.radius > r.y &&
                             ball.y - ball.radius < r.y + r.height);

            if (hitup || hitdown || hitleft || hitright)
            {
                if (i == 0)
                {
                    normal = false;
                }
                else
                {
                    normal = true;
                }
            }
        }
    }
}

void checkBrickCollision2()
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
            if (gravity > 0)
                onBrick = false;
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
            if (gravity > 0)
            {
                onBrick = true;
                isJump = false;
            }
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

void checklanding2()
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
            else if (ball.x + ball.radius > b.x &&
                     ball.x - ball.radius < b.x + b.width &&
                     ball.y == b.y - ball.radius && gravity > 0)
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

void checkSpikeCollision2()
{
    if (isdead || !ball.isAlive)
        return;
    for (int i = 0; i < spike_count; i++)
    {
        Spike s = spikes2[i];
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
            popX = ball.x;
            popY = ball.y;
            channel3 = iPlaySound("assets/Sounds/ball_pop_sound.mp3",false, 50);
            //score -= 50;
            ball.isAlive = false;
            isdead = true;
            iResumeTimer(deathTimerIndex);
            deathDelayCounter = 0;
        }
    }
}

void checkWaterCollision2()
{
    for (int i = 0; i < water_count; i++)
    {
        Water s = waters2[i];
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
                waters2[i].isCollected = true;
                lives++;
            }
        }
    }
}

void checkStarCollision2()
{
    for (int i = 0; i < star_count; i++)
    {
        Star s = stars2[i];
        if (ball.isAlive && stars2[i].isVisible)
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
                stars2[i].isVisible = false;
                stars2[i].isCollected = true;
                checkPointX = stars2[i].x;
                checkPointY = ball.y;
                checkPointIndex = i;
                checkPointReached = true;
            }
        }
    }
}

void checkRingCollision2()
{
    for (int i = 0; i < ring_count; i++)
    {
        Ring s = rings2[i];
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
                rings2[i].isCollected = true;
                ringsCollected++;
                score += 50;
            }
        }
    }
}

void moveball2()
{
    ball.velx = 12;

    if (moveright)
    {
        ball.x += ball.velx;
        checkBrickCollision2();
        checklanding2();
        checkSpikeCollision2();
        checkStarCollision2();
        checkWaterCollision2();
        checkRingCollision2();
        check_gravity_perk_collision();
        check_reverse_key_collision();
        if (ball.x - cameraX > screenWidth / 2 && cameraX + screenWidth < platformWidth2)
        {
            cameraX += ball.velx;
        }
    }
    if (moveleft)
    {
        ball.x -= ball.velx;
        checkBrickCollision2();
        checklanding2();
        checkSpikeCollision2();
        checkStarCollision2();
        checkWaterCollision2();
        checkRingCollision2();
        check_gravity_perk_collision();
        check_reverse_key_collision();
        if (ball.x - cameraX < screenWidth / 2 && cameraX > 0)
        {
            cameraX -= ball.velx;
            if (cameraX < 0)
                cameraX = 0;
        }
    }
}

void balljump2()
{
    if (isJump)
    {
        ball.y += ball.vely;
        ball.vely += gravity;

        checkBrickCollision2();
        checklanding2();
        checkSpikeCollision2();
        checkStarCollision2();
        checkWaterCollision2();
        checkRingCollision2();
        check_gravity_perk_collision();
        check_reverse_key_collision();
        //lev2Complete();
        float nextY = ball.y + ball.vely;

        if (gravity < 0)
        { // Normal gravity
            if (nextY <= ground)
            {
                ball.y = ground;
                ball.vely = 0;
                isJump = false;
            }
            else
            {
                midairmovement2();
            }
        }
        else
        { // Reverse gravity
            int upperPlatform = screenHeight - platformHeight - ball.radius;
            if (nextY >= upperPlatform)
            {
                ball.y = upperPlatform;
                ball.vely = 0;
                isJump = false;
            }
            else
            {
                midairmovement2();
            }
        }
    }
}

void midairmovement2()
{
    if (normal)
    {
        moveright = isSpecialKeyPressed(GLUT_KEY_RIGHT);
        moveleft = isSpecialKeyPressed(GLUT_KEY_LEFT);
        moveball2();
    }
    else
    {
        moveleft = isSpecialKeyPressed(GLUT_KEY_RIGHT);
        moveright = isSpecialKeyPressed(GLUT_KEY_LEFT);
        moveball2();
    }
}

void GameOver()
{
    iShowLoadedImage(0,0, &sad_img);
    iShowLoadedImage((screenWidth-256)/2, (screenHeight-60)/2, &gameover_img);
    iShowLoadedImage((screenWidth-356)/2, (screenHeight-385)/2, &menu_button);
}

