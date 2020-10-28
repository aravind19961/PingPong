//
// Created by Aravind Alluri on 10/27/20.
//

#include "Game.h"
#include <thread>

bool Game::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {

            obj_render = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );


            if(obj_render==nullptr )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {

                SDL_SetRenderDrawColor( obj_render, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

            }
        }
    }

    return success;
}

bool Game::loadMedia()
{
    //Loading success flag
    bool success = true;
    gFont=TTF_OpenFont("myfont/myfonyfont.ttf", 40);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        //Render text
        SDL_Color textColor = { 0, 0, 0 };
        if( !gTextTexture.loadFromRenderedText( "Score", textColor,obj_render,gFont ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }

    game_ball=std::make_shared<Ball>(SCREEN_HEIGHT,SCREEN_WIDTH,obj_render);
    player_left=std::make_shared<Left_player>(SCREEN_HEIGHT,SCREEN_WIDTH,obj_render,5,SCREEN_HEIGHT/2);
    player_right=std::make_shared<Right_player>(SCREEN_HEIGHT,SCREEN_WIDTH,obj_render,SCREEN_WIDTH-23,SCREEN_HEIGHT/2);

    return success;
}


void Game::render(){
    SDL_Event e;
    bool quit=false;

    SDL_Color textColorRed = { 0, 0, 0 };


    while( !quit )
    {
        SDL_Color textColor = { 0, 0, 0 };


        if( !ScoreTexture.loadFromRenderedText(std::to_string(player_left->getscore())+"         "+std::to_string(player_right->getscore()) , textColor,obj_render,gFont ) )
        {
            printf( "Failed to render text texture!\n" );

        }


        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
            {
                //Adjust the velocity
                if(e.key.keysym.sym==SDLK_SPACE ){
                    if (status==START) {
                        status=RUN;
                    }
                    else if(status==RUN){
                        status=PAUSE;
                    }
                    else if(status==PAUSE){
                        status=RUN;
                    }
                }

            }
            player_right->handleEvent(e);
            player_left->handleEvent(e);


            //Handle input for the dot


        }

        //Move the dot

        if (player_left->getscore()==5||player_right->getscore()==5) {
            if(player_left->getscore()<=player_right->getscore()){
                if( !instructions_controls.loadFromRenderedText("Right player is the Winner", textColorRed,obj_render,gFont ) )
                {
                    printf( "Failed to render text texture!\n" );

                }
            }
            else
            {
                if( !instructions_controls.loadFromRenderedText("Left Player is the Winner", textColorRed,obj_render,gFont ) )
                {
                    printf( "Failed to render text texture!\n" );

                }
            }

            instructions_controls.render(SCREEN_WIDTH/2-175, SCREEN_HEIGHT-40,NULL,0.0, NULL,SDL_FLIP_NONE,obj_render);

        }
        else if (status==PAUSE) {
            if( !instructions_controls.loadFromRenderedText("Press Space to Continue", textColorRed,obj_render,gFont ) )
            {
                printf( "Failed to render text texture!\n" );

            }
        }
        else if (status==RUN){
            game_ball->move(player_left,player_right);
            player_right->move();
            player_left->move();
            if( !instructions_controls.loadFromRenderedText("Press Space to Pause", textColorRed,obj_render,gFont ) )
            {
                printf( "Failed to render text texture!\n" );

            }
        }else if(status==START){
            player_right->move();
            player_left->move();
            if( !instructions_controls.loadFromRenderedText("Press Space to Start", textColorRed,obj_render,gFont ) )
            {
                printf( "Failed to render text texture!\n" );

            }
        }



        //Clear screen
        SDL_SetRenderDrawColor( obj_render, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( obj_render );

        //Render objects
        game_ball->render(obj_render);

        player_right->render(obj_render);
        player_left->render(obj_render);
        gTextTexture.render(SCREEN_WIDTH/2-50, 50, nullptr,0.0, nullptr,SDL_FLIP_NONE,obj_render);
        ScoreTexture.render(SCREEN_WIDTH/2-75, 100,nullptr,0.0, nullptr,SDL_FLIP_NONE,obj_render);
        instructions_controls.render(SCREEN_WIDTH/2-200, SCREEN_HEIGHT-40, nullptr,0.0, nullptr,SDL_FLIP_NONE,obj_render);

        //Update screen
        SDL_RenderPresent( obj_render );

    }



}

void Game::close()
{
    //Free loaded images



    //Destroy window
    SDL_DestroyRenderer( obj_render );

    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    obj_render=nullptr;
    free(gFont);

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

