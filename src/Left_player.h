//
// Created by Aravind Alluri on 10/28/20.
//

#ifndef SDL2TEST_LEFT_PLAYER_H
#define SDL2TEST_LEFT_PLAYER_H


#include <stdio.h>
#include "Player.h"
class Left_player:public Player{


public:
    Left_player(int screen_height,int screen_width,SDL_Renderer *obj_render,int x,int y);
    void handleEvent( SDL_Event& e );

};

#endif //SDL2TEST_LEFT_PLAYER_H
