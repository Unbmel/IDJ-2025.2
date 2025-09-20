#ifndef H_BASE_MUSICA_ONDAQUADRADA
#define H_BASE_MUSICA_ONDAQUADRADA
#include "LinhaMelodica.hpp"
#include <cstdint>
namespace IDJ::MUSICA
{
    class OndaQuadrada: public LinhaMelodica
    {
        public:
        OndaQuadrada(LOADERS::Asset<TAGS::SMIDI>& f, int16_t volume):LinhaMelodica(f, volume){};
        int16_t gerar_sample();
    };
};
#endif