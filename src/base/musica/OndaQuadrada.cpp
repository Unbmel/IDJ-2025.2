#include "OndaQuadrada.hpp"
#include <SDL3/SDL_stdinc.h>
#include <cstdint>
#include <cstdio>

namespace IDJ::MUSICA
{
    inline int16_t OndaQuadrada::gerar_sample()
    {
        int16_t ret = (1-(2*(((this->tempo_ms16_atual_onda*2)/((this->periodo_atual)))%2)))*this->volume;
        return ret;
    }
};