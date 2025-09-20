#ifndef H_BASE_MUSICA_SILENCIO
#define H_BASE_MUSICA_SILENCIO
#include "LinhaMelodica.hpp"
#include <cstdint>
namespace IDJ::MUSICA
{
    class Silencio: public LinhaMelodica
    {
        public:
        Silencio(LOADERS::Asset<TAGS::SMIDI>& f, int16_t volume):LinhaMelodica(f, volume){};
        int16_t gerar_sample();
    };
};
#endif