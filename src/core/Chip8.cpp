#include "Chip8.hpp"

Chip8::Chip8(){
    for(int i = 0; i < (sizeof(memory)/sizeof(uint8_t)); i++){
        memory[i] = 0;
    }
    for(int i = 0; i < (sizeof(V)/sizeof(uint8_t)); i++){
        V[i] = 0;
    }
    I = 0;
    PC = 0x200;
    for(int i = 0; i < (sizeof(stack)/sizeof(uint16_t)); i++){
        stack[i] = 0;
    }
    SP = 0;
    delayTimer = 0;
    soundTimer = 0;
    for(int i = 0; i < (sizeof(display)/sizeof(uint8_t)); i++){
        display[i] = 0;
    }
    for(int i = 0; i < sizeof(keypad); i++){
        keypad[i] = false;
    }
}

//void Chip8::loadROM(const char* filename){}