#include <cstdint>

class Chip8 {
    private:
        uint8_t memory[4096];
        uint8_t  V[16];
        uint16_t I;
        uint16_t PC;
        uint16_t stack[16];
        uint8_t SP;
        uint8_t delayTimer;
        uint8_t soundTimer;
        uint8_t display[64 * 32];
        bool keypad[16];

    public:
        /*  Resets all the register, memory and timer to zero. Set the program counter (PC) to 0x200 
        *   (because the first 512 bytes were reserved to the interpreter)
        */
        Chip8();

        /*  Open the file, read the binary content and copies it into the memory array stating from
        *   0x200 address
        *   @param {filename} - the path and name of the ROM to load
        */
        void loadROM(const char* filename);
};