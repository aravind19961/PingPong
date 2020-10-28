//
// Created by Aravind Alluri on 10/27/20.
//

#ifndef SDL2TEST_GAME_H
#define SDL2TEST_GAME_H
#include "L_Texture.h"
#include "Player.h"
#include "Left_player.h"
#include "Ball.h"
#include "Right_Player.h"


enum GameState{
    START,
    PAUSE,
    RUN
};

class Game{

private:

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window* gWindow = nullptr;
    std::shared_ptr<Ball> game_ball=nullptr;
    std::shared_ptr<Left_player> player_left=nullptr;
    std::shared_ptr<Right_player> player_right=nullptr;
    TTF_Font *gFont = nullptr;
    L_Texture gTextTexture;
    L_Texture ScoreTexture;
    L_Texture instructions_controls;
    L_Texture intstructions;
    GameState status=START;
    SDL_Renderer* obj_render=nullptr;



public:


    bool init();

    //Loads media
    bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    void render();

};



#endif //SDL2TEST_GAME_H
