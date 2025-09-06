#ifndef H_BASE_MUNDO_SBMPDESENHAVEL
#define H_BASE_MUNDO_SBMPDESENHAVEL
#include "ImagemDesenhavel.hpp"
#include <SDL3/SDL_rect.h>
#include <cstdint>
#include "../loaders/Descomprimido.hpp"
#include "../loaders/LoaderSBMP.hpp"

namespace IDJ::MUNDO
{
    class SBMPDesenhavel: public ImagemDesenhavel
    {
        uint16_t frame=0, frames;
        uint32_t pulo;
        static SDL_Rect le_header(LOADERS::Asset<TAGS::SBMP>& asset);
        public:
        SBMPDesenhavel(
            MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo,
            SDL_Rect dest,
            LOADERS::Asset<TAGS::SBMP>& asset,
            SDL_Renderer* renderer
        );
        SBMPDesenhavel(
            MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo,
            LOADERS::Asset<TAGS::SBMP>& asset,
            SDL_Renderer* renderer
        );
        void prox_frame();
    };
}

#endif