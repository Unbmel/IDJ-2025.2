#include "SDL.hpp"
#include <SDL3/SDL_log.h>
#include <cstdlib>
#include <cerrno>
#include <cstring>

namespace IDJ
{
    void sair_erro_SDL(const char* contexto, SDL_Window* janela)
    {
        const char* erro = SDL_GetError();
        sair_errostring(contexto, erro);
    }
    void sair_error(const char* contexto, int erron)
    {
        const char* erro = std::strerror(erron);
        sair_errostring(contexto, erro);
    }
    void sair_errostring(const char* contexto, const char* erro)
    {
        SDL_LogError(0, "Erro reportado no contexto (%s) - %s", contexto, erro);
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            contexto,
            erro,
            NULL
        );
        SDL_Quit();
        std::exit(-1);
    }
    void sair(const char* motivo)
    {
        const char* erro = motivo;
        SDL_LogError(0, "Fim inesperado - %s", erro);
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Fim inesperado",
            erro,
            NULL
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