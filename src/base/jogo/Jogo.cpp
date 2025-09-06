#include "Jogo.hpp"
#include <SDL3/SDL_timer.h>

namespace IDJ::JOGO
{
    uint32_t Jogo::frame()
    {
        uint32_t agr = SDL_GetTicks();
        this->mundo.desenhar();
        agr = SDL_GetTicks()-agr;
        return this->quantum - agr;
    }
    void Jogo::frame_delay()
    {
        SDL_Delay(this->frame());
    }
    void Jogo::loop()
    {
        for(;;)frame_delay();
    }
}