#ifndef H_BASE_MUNDO_IMAGEMDESENHAVEL
#define H_BASE_MUNDO_IMAGEMDESENHAVEL
#include "Desenhavel.hpp"

namespace IDJ::MUNDO
{
    class ImagemDesenhavel: public Desenhavel
    {
        public:
        void desenhar();
        MENSAGENS::SpriteRenderizavel sprite;
        ImagemDesenhavel(
            MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo,
            SDL_Texture* txtr,
            SDL_Rect clip,
            SDL_Rect dest
        ):
            Desenhavel(alvo),
            sprite{
                .txtr=txtr,
                .clip=clip,
                .dest=dest
            }
        {};
        ImagemDesenhavel(
            MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo,
            SDL_Texture* txtr,
            SDL_Rect clip
        ):
            Desenhavel(alvo),
            sprite{
                .txtr=txtr,
                .clip=clip,
                .dest={
                    .x=0,
                    .y=0,
                    .w=clip.w,
                    .h=clip.h
                }
            }
        {};
        ~ImagemDesenhavel();
    };
};

#endif