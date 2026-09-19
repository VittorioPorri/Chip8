#include "core/Chip8.hpp"
#include "frontend/Input.hpp"
#include "frontend/Renderer.hpp"
#include <iostream>




int main(int argc, char **argv){
    Chip8 mychip8;
    Input input;
    Renderer display;
    bool running = true;

    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <ROM path>" << std::endl;
        return 1;
    }
    mychip8.loadROM(argv[1]);

    while(running){
        mychip8.emulateCycle();

        if(mychip8.getDrawFlag()){
            display.drawGraphics(mychip8);
            mychip8.setDrawFlag(false);
        }

        running = input.setKeys(mychip8);
        //TODO: Timing (60 Hz per delayTimer/soundTimer e limitatore CPU)
    }   



    return 0;
}
