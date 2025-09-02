#ifndef H_BASE_MENSAGENS_COMANDOGRAFICO
#define H_BASE_MENSAGENS_COMANDOGRAFICO
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
        } tipo;
        union
        {
            struct SpriteRenderizavel desenha;
        } dados;
    };
};
#endif