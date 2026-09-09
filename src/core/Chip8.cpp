#include "Chip8.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>

constexpr int MEMORY_SIZE = 4096;
constexpr int START = 512;
constexpr int FREE_SPACE = MEMORY_SIZE -START;

using namespace std;

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

void Chip8::loadROM(const char* filepath){
    ifstream file(filepath, ios::binary | ios::ate);
    
    if(!file.is_open()){
        cerr << "Error: file doesn't opening" << endl;
        return;
    }

    streamsize fileSize = file.tellg();

    if( fileSize > FREE_SPACE){
        cerr << "Error: file size is to big" << endl;
        return;
    }

    file.seekg(0, ios_base::beg);

    file.read(reinterpret_cast<char*>(&memory[START]), fileSize);

    file.close();
}


void executeOpcode(uint16_t opcode){
    switch (opcode & 0xF000) {
        case 0x0000:
            
        case 0x1000:

        case 0x2000:

        case 0x3000:

        case 0x4000:

        case 0x5000:

        case 0x6000:

        case 0x7000:

        case 0x9000:

        case 0xA000:

        case 0xB000:

        case 0xC000:

        case 0xD000:

        case 0xE000:

        case 0xF000:

        default:
            printf ("Unknown opcode: 0x%X\n", opcode);
    }
}


void Chip8::emulateCycle(){

    /*
    *  memory[PC]    ---> 0xA2 = 1010 0010 
    *  memory[PC +1] ---> 0xB1 = 1011 0001
    *  
    *  1. memory[PC] << 8  ---> 0xA200
    *  2. (memory[PC] << 8) | memory[PC+1]
    *  
    *     1010 0010 0000 0000 \
    *               1011 0001 =
    *    ----------------------
    *     1010 0010 1011 0001     ---> 0xA2B1
    */

    uint16_t opcode = (memory[PC] << 8) | memory[PC+1];

    executeOpcode(opcode);

    PC = PC + 2;
}