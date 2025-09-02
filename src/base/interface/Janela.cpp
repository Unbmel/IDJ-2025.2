#include "Janela.hpp"
#include "../SDL.hpp"

namespace IDJ::INTERFACE
{
    Janela::Janela()
    {
        this->Win = SDL_CreateWindow(
            "Amélia Oliveira Freitas da Silva - 190037971",
            1200, 900,
            SDL_WINDOW_OPENGL
        );
        if(!this->Win)IDJ::sair_erro_SDL("Erro na inicialização da janela", NULL);
        this->Render = SDL_CreateRenderer(this->Win, 0);
        if(!this->Render)
            IDJ::sair_erro_SDL("Erro na criação do renderer", this->Win);
    }
    Janela::~Janela()
    {
        SDL_DestroyRenderer(this->Render);
        SDL_DestroyWindow(this->Win);
    }
    SDL_Renderer* Janela::get_renderer()
    {
        return this->Render;
    }
}