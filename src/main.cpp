#include "core/Chip8.hpp"
#include "frontend/Input.hpp"
#include "frontend/Renderer.hpp"
#include <iostream>




int main(int argc, char **argv){
    Chip8 mychip8;
    Input input;
    Renderer display;
    
    if (argc < 2){
        std::cerr << "To many arguments" << std::endl;
    }
    mychip8.loadROM(argv[1]);

    for(;;){
        mychip8.emulateCycle();

        if(mychip8.getDrawFlag()){
            display.drawGraphics();
            mychip8.setDrawFlag(false);
        }

        input.setKeys();
        //Ogni 60HZ devo decrementare delayTimer, soundTimer;
    }   



    return 0;
}
