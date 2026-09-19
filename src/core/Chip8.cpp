#include "Chip8.hpp"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <cstdlib>
#include <ctime>


constexpr int MEMORY_SIZE = 4096;
constexpr int START = 512;
constexpr int FREE_SPACE = MEMORY_SIZE -START;

using namespace std;

Chip8::Chip8(){
    srand(time(NULL));

    for(int i = 0; i < (sizeof(memory)/sizeof(uint8_t)); i++){
        memory[i] = 0;
    }

    uint8_t fontset[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for(int i = 0; i < sizeof(fontset); i++){
        memory[i] = fontset[i];
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
    for(int i = 0; i < sizeof(keypad)/sizeof(bool); i++){
        keypad[i] = false;
    }
}

void Chip8::setKey(uint8_t index, bool isPressed) {
    if (index < 16) {
        keypad[index] = isPressed;
    }
}

const uint8_t* Chip8::getDisplay() const {
    return display;
}

bool Chip8::getDrawFlag() const {
    return drawFlag;
}

void Chip8::setDrawFlag(bool flag) {
    drawFlag = flag;
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

void Chip8::draw(uint8_t x, uint8_t y, uint8_t n){

    V[0xF] = 0;

    uint8_t startX = x % 64;
    uint8_t startY = y % 32;

    for(int i = 0; i < n ; i++){
        uint8_t line = memory[I+i];
        for(int j = 0; j < 8; j++){
            if((line & (0x80 >> j)) != 0){

                if(startX + j >= 64 || startY + i >= 32) {
                    continue;
                }

                int pos = ((startY + i) * 64) + (startX + j);
                if(display[pos] == 1){
                    V[0xF] = 1;
                }
                display[pos] ^= 1;
            }
        }
    }
    setDrawFlag(true);

}

void Chip8::executeOpcode(uint16_t opcode){

    uint16_t NNN = opcode & 0x0FFF;
    uint8_t NN = opcode & 0x00FF;
    uint8_t N = opcode & 0x000F;
    uint8_t X = (opcode & 0x0F00) >> 8;
    uint8_t Y = (opcode & 0x00F0) >> 4;
    uint8_t flag = 0;


    switch (opcode & 0xF000) {
        case 0x0000:
            if(opcode == 0x00E0){
                for(int i = 0; i < (sizeof(display)/sizeof(uint8_t)); i++){
                    display[i] = 0;
                }
            }else if (opcode == 0x00EE){
                SP--;
                PC = stack[SP];
            }
            break;
        case 0x1000:
            PC = NNN;
            break;
        case 0x2000:
            stack[SP] = PC;
            SP++;    
            PC = NNN;
            break;
        case 0x3000:
            if(V[X] == NN){
                PC+=2;
            }
            break;
        case 0x4000:
            if(V[X] != NN){
                PC+=2;
            }
            break;
        case 0x5000:
            if(V[X] == V[Y]){
                PC+=2;
            }
            break;
        case 0x6000:
            V[X] = NN;
            break;
        case 0x7000:
            V[X] += NN;
            break;
        case 0x8000:
            switch (N) {
                case 0:
                    V[X] = V[Y];
                    break;
                case 1:
                    V[X] |= V[Y];
                    break;
                case 2: 
                    V[X] &= V[Y];
                    break;
                case 3:
                    V[X] ^= V[Y];
                    break;
                case 4:
                    //remaining space in V[X] - V[Y]  to check if there is the overflow
                    if(UINT8_MAX - V[X] < V[Y]){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                    V[X] += V[Y];
                    V[0xF] = flag;
                    break;
                case 5:
                    if(V[X] >= V[Y]){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                    V[X] -= V[Y];
                    V[0xF] = flag;
                    break;
                case 6:
                    flag = V[X] & 0x1;
                    V[X] >>= 1;
                    V[0xF] = flag;
                    break;
                case 7:
                    if(V[Y] >= V[X]){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                    V[X] = V[Y] - V[X];
                    V[0xF] = flag;
                    break;
                case 0XE:
                    flag =(V[X] & 0x80) >> 7;
                    V[X] <<= 1;
                    V[0xF] = flag;
                    break;
            }
            break;
        case 0x9000:
            if(V[X] != V[Y]){
                PC+=2;
            }
            break;
        case 0xA000:
            I = NNN;
            break;
        case 0xB000:
            PC = V[0]+ NNN;
            break;
        case 0xC000:
            V[X] = (rand() % 256) & NN;
            break;
        case 0xD000:
            draw(V[X], V[Y], N);
            break;
        case 0xE000:
            if(NN == 0x9E){
                if((keypad[V[X] & 0xF])!= 0){
                    PC += 2;
                }
            }else if(NN == 0xA1){
                if((keypad[V[X] & 0xF]) == 0){
                    PC += 2;
                }
            }
            break;
        case 0xF000:
            switch (NN) {
                case 0x07:
                    V[X] = delayTimer;
                    break;
                case 0x0A:
                {
                    bool Press = false;
                    for(int i = 0; i <sizeof(keypad)/sizeof(bool); i++){
                        if(keypad[i] != false){
                            V[X] = i;
                            Press = true;
                        }
                    }
                    
                    if(!Press){
                        PC-=2;
                    }
                    break;
                }
                case 0x15:
                    delayTimer = V[X];
                    break;
                case 0x18:
                    soundTimer = V[X];
                    break;
                case 0x1E:
                    I+=V[X];
                    break;
                case 0x29:
                    I = (V[X] & 0xF) * 0x5;
                    break;
                case 0x33:
                {
                    int i = 2;
                    uint8_t value = V[X];
                    while(i >= 0){
                        memory[I+i] = value % 10;
                        value = value/10;
                        i--;
                    }
                    break;
                }
                case 0x55:  
                    for(int i = 0; i <= X; i++){
                        memory[I+i] = V[i];
                    }
                    break;
                case 0x65:
                    for(int i = 0; i <= X; i++){
                        V[i] = memory[I+i];
                    }
                    break;
            }
            break;
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
    
    PC = PC + 2;
    
    executeOpcode(opcode);

}

void Chip8::updateTime() {
    if (delayTimer > 0) {
        delayTimer--;
    }

    if (soundTimer > 0) {
        soundTimer--;
    }
}