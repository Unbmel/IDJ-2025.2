#ifndef H_BASE_MUSICA_RUIDO
#define H_BASE_MUSICA_RUIDO
#include "LinhaMelodica.hpp"
#include <cstdint>
namespace IDJ::MUSICA
{
    class Ruido: public LinhaMelodica
    {
        public:
        Ruido(LOADERS::Asset<TAGS::SMIDI>& f, int16_t volume):LinhaMelodica(f, volume){};
        int16_t gerar_sample();
    };
};
#endif