#include "Ruido.hpp"
#include <SDL3/SDL_stdinc.h>
#include <cstdint>

namespace IDJ::MUSICA
{
    inline int16_t Ruido::gerar_sample()
    {
        return this->volume*(SDL_rand_bits()&0x1);
    }
};