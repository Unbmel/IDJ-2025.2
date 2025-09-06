#ifndef H_BASE_SDL
#define H_BASE_SDL
#include <SDL3/SDL.h>

namespace IDJ
{
    void sair_erro_SDL(const char* contexto, SDL_Window* janela);
    void sair_error(const char* contexto, int erro);
    void sair_errostring(const char* contexto, const char* erro);
    void sair(const char* motivo);
    class CtxSDL
    {
        public:
        CtxSDL();
        ~CtxSDL();
    };
};

#endif