//
// Created by Aravind Alluri on 10/28/20.
//

#ifndef SDL2TEST_BALL_H
#define SDL2TEST_BALL_H



#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <string>

#include "L_Texture.h"

#include "Left_player.h"
#include "Right_Player.h"
#include "Player.h"

class Ball{

public:


    //Initializes the variables
    Ball(int screen_height,int screen_width,SDL_Renderer *obj_render);

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move(std::shared_ptr<Left_player> left,std::shared_ptr<Right_player> right);

    //Shows the dot on the screen
    void render(SDL_Renderer *myrender);

    bool collision_check_left(std::shared_ptr<Left_player> check_left);

    bool collision_check_right(std::shared_ptr<Right_player> check_right);

private:
    //The X and Y offsets of the dot
    int mPosX, mPosY;

    int screen_h,screen_w;

    //The velocity of the dot
    int mVelX, mVelY;

    int velocity=3;

    static int direction_x;
    static int direction_y;

    L_Texture ball_texture;

    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 1;

};

#endif //SDL2TEST_BALL_H
