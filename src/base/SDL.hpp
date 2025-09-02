#ifndef H_BASE_SDL
#define H_BASE_SDL
#include <SDL3/SDL.h>

namespace IDJ
{
    void sair_erro_SDL(const char* contexto, SDL_Window* janela);
    class CtxSDL
    {
        public:
        CtxSDL();
        ~CtxSDL();
    };
};

#endif