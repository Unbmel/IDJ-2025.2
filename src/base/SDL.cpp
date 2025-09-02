#include "SDL.hpp"
#include <SDL3/SDL_log.h>
#include <cstdlib>

namespace IDJ
{
    void sair_erro_SDL(const char* contexto, SDL_Window* janela)
    {
        const char* erro = SDL_GetError();
        SDL_LogError(0, "Erro reportado - %s", erro);
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            contexto,
            erro,
            janela
        );
        SDL_Quit();
        std::exit(-1);
    }
    CtxSDL::CtxSDL()
    {
        if(!SDL_Init(
            SDL_INIT_AUDIO|SDL_INIT_VIDEO
            |SDL_INIT_EVENTS
        ))
            sair_erro_SDL("Erro de inicialização", NULL);
    }
    CtxSDL::~CtxSDL()
    {
        SDL_Quit();
    }
}