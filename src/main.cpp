#include "core/Chip8.hpp"
#include "frontend/Input.hpp"
#include "frontend/Renderer.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>




int main(int argc, char **argv){
    Chip8 mychip8;
    Input input;
    Renderer display;
    bool running = true;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS; 
    uint32_t frameStart;
    int frameTime;


    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <ROM path>" << std::endl;
        return 1;
    }
    mychip8.loadROM(argv[1]);

    while(running){
        frameStart = SDL_GetTicks();

        for(int i = 0; i < 10; ++i) {
            mychip8.emulateCycle();
        }

        if(mychip8.getDrawFlag()){
            display.drawGraphics(mychip8);
            mychip8.setDrawFlag(false);
        }

        mychip8.updateTime();
        
        running = input.setKeys(mychip8);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }


    }   



    return 0;
}
