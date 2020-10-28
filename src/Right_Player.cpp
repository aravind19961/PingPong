//
// Created by Aravind Alluri on 10/28/20.
//

#include "Right_Player.h"
Right_player::Right_player(int screen_height,int screen_width,SDL_Renderer *obj_render,int x,int y):Player(screen_height, screen_width, obj_render, x, y){

}
void Right_player::handleEvent(SDL_Event &e){

    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;

        }
    }
        //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;

        }
    }
}
