#include "Renderer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <iostream>

Renderer::Renderer(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Errore inizializzazione SDL: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH * SCALE,
        SCREEN_HEIGHT * SCALE,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Renderer::drawGraphics(Chip8 &chip8){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    const uint8_t* display = chip8.getDisplay();

    for(int i = 0; i < SCREEN_HEIGHT; i++){
        for(int j = 0; j < SCREEN_WIDTH; j++){
            if(display[i * SCREEN_WIDTH + j] == 1){
                SDL_Rect pixelRect;
                pixelRect.x = j * SCALE;
                pixelRect.y = i * SCALE;
                pixelRect.w = SCALE;
                pixelRect.h = SCALE;

                SDL_RenderFillRect(renderer, &pixelRect);
            }
        }
    }


    SDL_RenderPresent(renderer);
}