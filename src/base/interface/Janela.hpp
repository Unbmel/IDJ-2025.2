#ifndef H_BASE_INTERFACE_JANELA
#define H_BASE_INTERFACE_JANELA
#include <SDL3/SDL.h>

namespace IDJ::INTERFACE
{
    class Janela
    {
        SDL_Window* Win = 0;
        SDL_Renderer* Render = 0;
        public:
        Janela();
        ~Janela();
        SDL_Renderer* get_renderer();
    };
};

#endif