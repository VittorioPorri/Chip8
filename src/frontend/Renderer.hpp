#pragma once
#include "../core/Chip8.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class Renderer{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        const int SCREEN_WIDTH = 64;
        const int SCREEN_HEIGHT = 32;
        const int SCALE = 15;

    public:
        /* Creates the application window and the hardware-accelerated renderer,
        *  applying the scale multiplier to the original 64x32 CHIP-8 resolution        *
        */
        Renderer();
        
        // Destroys the renderer and the window to prevent memory leaks when the emulator is closed.
        ~Renderer();

        /* Fetches the display state from the CHIP-8 core.
         * Clears the screen, draws scaled rectangles for every active pixel, and updates the window
         */
        void drawGraphics(Chip8& chip8);
};