#include "SBMPDesenhavel.hpp"
#include "ImagemDesenhavel.hpp"
#include <cstdint>
#include <cstdio>

namespace IDJ::MUNDO
{
    SDL_Rect SBMPDesenhavel::le_header(LOADERS::Asset<TAGS::SBMP>& asset)
    {
        uint8_t* ptr = (uint8_t*) asset.get_ptr();
        return {
            .x=0,.y=0,.w=*((uint16_t*)(ptr+3)),.h=*((uint16_t*)(ptr+5))
        };
    }
    SBMPDesenhavel::SBMPDesenhavel(
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo,
        LOADERS::Asset<TAGS::SBMP>& asset,
        SDL_Renderer* renderer
    ):IDJ::MUNDO::SBMPDesenhavel(alvo, le_header(asset),asset,renderer){};
    SBMPDesenhavel::SBMPDesenhavel(
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo,
        SDL_Rect dest,
        LOADERS::Asset<TAGS::SBMP>& asset,
        SDL_Renderer* renderer
    ):
    ImagemDesenhavel(
        alvo,
        LOADERS::assetsbmp_to_textura(asset, renderer),
        le_header(asset),
        dest
    )
    {
        uint8_t* ptr = (uint8_t*) asset.get_ptr();
        this->frames = *((uint16_t*)(ptr+7));
        this->pulo = (
            ((uint32_t)ImagemDesenhavel::sprite.clip.w)
        );
    }
    void SBMPDesenhavel::prox_frame()
    {
        this->frame++;
        this->frame%=this->frames;
        ImagemDesenhavel::sprite.clip.x = this->frame*this->pulo;
    }
}