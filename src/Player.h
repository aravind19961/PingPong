//
// Created by Aravind Alluri on 10/28/20.
//

#ifndef SDL2TEST_PLAYER_H
#define SDL2TEST_PLAYER_H


#include <stdio.h>
#include "SDL2/SDL.h"

#include <SDL2_image/SDL_image.h>
#include "L_Texture.h"
#include <string>


class Player{
public:


    //Initializes the variables
    Player(int screen_height,int screen_width,SDL_Renderer *obj_render,int x,int y);

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render(SDL_Renderer *myrender);

    int position_x();
    int position_y();
    int height();
    int width();
    int getscore();
    void inc_score();

protected:
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    int score=0;
    int screen_h,screen_w;

    //The velocity of the dot
    int mVelX, mVelY;

    SDL_Rect dasher;

    L_Texture dasher_texture;

    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_VEL = 10;
};

#endif //SDL2TEST_PLAYER_H
