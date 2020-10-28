//
// Created by Aravind Alluri on 10/28/20.
//

#include "Ball.h"
#include <thread>
#include <chrono>
Ball::Ball(int screen_height,int screen_width,SDL_Renderer *obj_render):screen_h(screen_height),screen_w(screen_width){
    mPosX = screen_w/2;
    mPosY = screen_h/2;

    ball_texture.loadFromFile("./image/dot.bmp", obj_render);

    mVelX = 0;
    mVelY = 0;
}


int Ball::direction_x=-1;

int Ball::direction_y=1;


void Ball::move(std::shared_ptr<Left_player> left,std::shared_ptr<Right_player> right)
{
    if(direction_x==0&&direction_y==0){

        mPosX=screen_w/2;
        mPosY=screen_h/2;
        direction_x=1;
        direction_y=-1;
    }

    if (  collision_check_right(right)) {

    }
    else if(collision_check_left(left)){

    }
    else if(mPosX<=0)
    {
        direction_x=1;
        right->inc_score();

    }
    else if( mPosY+DOT_HEIGHT==screen_h||mPosY>=screen_h)
    {
        direction_y=-1;
        //Move back

    }

    else if(mPosY+DOT_HEIGHT==0||mPosY<0)
    {
        direction_y=1;
    }
    else if(mPosX>=screen_w){
        direction_x=-1;
        left->inc_score();
    }



    mPosX+=(velocity*direction_x);
    mPosY+=(velocity*direction_y);

}

void Ball::render(SDL_Renderer *myrender)
{


    ball_texture.render( mPosX, mPosY,NULL, 0.0,  NULL, SDL_FLIP_NONE,myrender);
}

bool Ball::collision_check_left(std::shared_ptr<Left_player> check_left){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = check_left->position_x();
    rightA = check_left->position_x()+check_left->width();
    topA = check_left->position_y();
    bottomA = check_left->position_y()+check_left->height();

    leftB = this->mPosX;
    rightB = this->mPosX + this->DOT_WIDTH;
    topB = this->mPosY;
    bottomB = this->mPosY + this->DOT_HEIGHT;


    if(rightA==leftB){
        if(bottomB==topA){
            direction_y=-1;
            return true;
        }
        else if(topB==bottomA){
            direction_y=1;
            return true;
        }
        else if(bottomB>topA&&bottomB<bottomA){
            direction_x=1;
            return true;
        }
        else if(topB<bottomA&&topB>topA){
            direction_x=1;
            return true;
        }
        return false;
    }

    return false;

}

bool Ball::collision_check_right(std::shared_ptr<Right_player> check_right){

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = check_right->position_x();
    rightA = check_right->position_x()+check_right->width();
    topA = check_right->position_y();
    bottomA = check_right->position_y()+check_right->height();

    leftB = this->mPosX;
    rightB = this->mPosX + this->DOT_WIDTH;
    topB = this->mPosY;
    bottomB = this->mPosY + this->DOT_HEIGHT;


    if(leftA==rightB||leftA<rightB){

        if(bottomB==topA){
            direction_y=-1;
            return true;
        }
        else if(topB==bottomA){
            direction_y=1;
            return true;
        }
        else if(bottomB>topA&&bottomB<bottomA){
            direction_x=-1;
            return true;
        }
        else if(topB<bottomA&&topB>topA){
            direction_x=-1;
            return true;
        }
        return false;
    }

    return false;

}
