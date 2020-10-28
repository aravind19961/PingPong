//
// Created by Aravind Alluri on 10/28/20.
//

#include "Player.h"
Player::Player(int screen_height,int screen_width,SDL_Renderer *obj_render,int x,int y):screen_h(screen_height),screen_w(screen_width){


    mVelX = 0;
    mVelY = 0;


    dasher.h=100;
    dasher.w=18;
    dasher.x=x;
    dasher.y=y;
}

void Player::handleEvent( SDL_Event& e )
{
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

void Player::move()
{


    //Move the dot up or down
    dasher.y += mVelY;

    //If the dot went too far up or down
    if(  ( dasher.y + dasher.h > screen_h ) )
    {
        //Move back
        dasher.y -= mVelY;
    }
    else if( dasher.y < 0 ){
        dasher.y -= mVelY;
    }

}

void Player::render(SDL_Renderer *myrender)
{
    SDL_SetRenderDrawColor( myrender, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( myrender, &dasher );
    //myrender= nullptr;
    //dasher_texture.render( mPosX, mPosY,NULL, 0.0,  NULL, SDL_FLIP_NONE,myrender);
}


int Player::position_x(){
    return dasher.x;
}

int Player::position_y(){
    return dasher.y;
}

int Player::height(){
    return dasher.h;
}

int Player::width(){
    return dasher.w;
}
int Player::getscore(){
    return score;
}
void Player::inc_score(){
    this->score++;
}