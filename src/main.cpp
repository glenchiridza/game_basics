#include <iostream>
#include "Game.h"


int main() {

    //seed
    std::srand(static_cast<unsigned>(time(NULL)));

    //initialize game engine
    Game game;

    //game loop
    while (game.running() )
    {
       
        //update
        game.update();

        //render
        game.render();
    }
    
    


    return 0;
}