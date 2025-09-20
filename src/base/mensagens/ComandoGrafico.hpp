#ifndef H_BASE_MENSAGENS_COMANDOGRAFICO
#define H_BASE_MENSAGENS_COMANDOGRAFICO
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdint.h>

namespace IDJ::MENSAGENS
{
    struct SpriteRenderizavel
    {
        SDL_Texture* txtr;
        SDL_Rect clip;
        SDL_Rect dest;
    };
    struct ComandoGrafico
    {
        enum
        {
            COMMIT, // Troca de tela
            DESENHA, // Desenha uma textura em algum lugar
            FILLCOR, // Preenche a tela com uma cor
        } tipo;
        union
        {
            struct SpriteRenderizavel desenha;
            SDL_Color fillcor;
        } dados;
    };
};
#endif