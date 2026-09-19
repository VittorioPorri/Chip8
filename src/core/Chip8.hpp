#pragma once
#include <cstdint>

class Chip8 {
    private:
        uint8_t memory[4096];
        uint8_t  V[16];
        uint16_t I;
        uint16_t PC;
        uint16_t stack[16];
        uint8_t SP; //stack index 
        uint8_t delayTimer;
        uint8_t soundTimer;
        uint8_t display[64 * 32];
        bool keypad[16];
        bool drawFlag = false;


        /*All of the 35 implementation of the opcode */
        void executeOpcode(uint16_t opcode);

        /*Draw a sprite at cordinate (x,y) that has width of 8 pixel and height of n pixel, starting from I value */
        void draw(uint8_t x, uint8_t y, uint8_t n);
    
    public:
        /*  Resets all the register, memory and timer to zero. Set the program counter (PC) to 0x200 
        *   (because the first 512 bytes were reserved to the interpreter)
        */
        Chip8();

        /* Sets the state of a specific key on the hex keypad.
        *  @param index - The hex keypad index (0x0 to 0xF)
        *  @param isPressed - Boolean indicating if the key is currently held down
        */
        void setKey(uint8_t index, bool isPressed);

        /* Returns a read-only pointer to the display array.
        *  Used by the frontend renderer to draw the pixels on the screen.
        *  @return A constant pointer to the 64x32 display buffer
        */
        const uint8_t* getDisplay() const;

        /* Checks if the display has been updated during the last cycle.
        *  @return True if a draw operation occurred, meaning the screen needs to be re-rendered
        */
        bool getDrawFlag() const;

        /* Manually sets the draw flag. 
        *  Primarily used by the frontend to reset the flag to false after updating the screen.
        *  @param flag - The boolean value to set the draw flag to
        */
        void setDrawFlag(bool flag);

        /*  Open the file, read the binary content and copies it into the memory array stating from
        *   0x200 address
        *   @param {filename} - the path of the ROM to load
        */
        void loadROM(const char* filepath);

        /* This operation executes a single CPU cycle. 
        *  Performs the fetch, decode, execute strictly respecting the 35 standard CHIP-8 opcodes.
        */
        void emulateCycle();


};