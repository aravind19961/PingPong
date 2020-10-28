#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

#include "Game.h"



int main( int argc, char* args[] )
{
    Game myGame;
    if( !myGame.init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !myGame.loadMedia() )
        {
            printf( "Failed to load media!\n" );

        }
        else
        {
            myGame.render();
        }
    }

    //Free resources and close SDL
    myGame.close();



    return 0;
}