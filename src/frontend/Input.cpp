#include "Input.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

bool Input::setKeys(Chip8& chip8){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type ==SDL_QUIT){
                return false;
        }

        if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
                case SDLK_1: chip8.setKey(0x1, true); break;
                case SDLK_2: chip8.setKey(0x2, true); break;
                case SDLK_3: chip8.setKey(0x3, true); break;
                case SDLK_4: chip8.setKey(0xC, true); break;

                case SDLK_q: chip8.setKey(0x4, true); break;
                case SDLK_w: chip8.setKey(0x5, true); break;
                case SDLK_e: chip8.setKey(0x6, true); break;
                case SDLK_r: chip8.setKey(0xD, true); break;

                case SDLK_a: chip8.setKey(0x7, true); break;
                case SDLK_s: chip8.setKey(0x8, true); break;
                case SDLK_d: chip8.setKey(0x9, true); break;
                case SDLK_f: chip8.setKey(0xE, true); break;

                case SDLK_z: chip8.setKey(0xA, true); break;
                case SDLK_x: chip8.setKey(0x0, true); break;
                case SDLK_c: chip8.setKey(0xB, true); break;
                case SDLK_v: chip8.setKey(0xF, true); break;

            }

        }

        if (event.type == SDL_KEYUP){
            switch(event.key.keysym.sym){
                case SDLK_1: chip8.setKey(0x1, false); break;
                case SDLK_2: chip8.setKey(0x2, false); break;
                case SDLK_3: chip8.setKey(0x3, false); break;
                case SDLK_4: chip8.setKey(0xC, false); break;

                case SDLK_q: chip8.setKey(0x4, false); break;
                case SDLK_w: chip8.setKey(0x5, false); break;
                case SDLK_e: chip8.setKey(0x6, false); break;
                case SDLK_r: chip8.setKey(0xD, false); break;

                case SDLK_a: chip8.setKey(0x7, false); break;
                case SDLK_s: chip8.setKey(0x8, false); break;
                case SDLK_d: chip8.setKey(0x9, false); break;
                case SDLK_f: chip8.setKey(0xE, false); break;

                case SDLK_z: chip8.setKey(0xA, false); break;
                case SDLK_x: chip8.setKey(0x0, false); break;
                case SDLK_c: chip8.setKey(0xB, false); break;
                case SDLK_v: chip8.setKey(0xF, false); break;

            }   
        }
        
    }
    return true;
}