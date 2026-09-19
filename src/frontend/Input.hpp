#pragma once
#include "../core/Chip8.hpp"

class Input{
    public:
        /* This operation have to detect the key to set to true the value on chip8 class if the correspond 
        *  key is press oterquise set to false it.
        *  @return Returns false if a window close event is triggered, otherwise returns true
        */
        bool setKeys(Chip8& chip8);
};