#ifndef H_BASE_MUSICA_SENO
#define H_BASE_MUSICA_SENO
#include "Synth.hpp"
#include <cstdint>
#include <stdint.h>

namespace IDJ::MUSICA
{
    int16_t seno(int16_t x);
    const int16_t pi_10bit = 3216;
}

#endif