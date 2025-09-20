#ifndef H_BASE_INTERFACE_JANELA
#define H_BASE_INTERFACE_JANELA
#include <SDL3/SDL.h>
#include "../mensagens/Canal.hpp"
#include "../mensagens/ComandoGrafico.hpp"

namespace IDJ::INTERFACE
{
    class Janela
    {
        SDL_Window* Win = 0;
        SDL_Renderer* render = 0;
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico> real;
        int w,h;
        public:
        static void tratar_grafico(void* ref_obj, MENSAGENS::ComandoGrafico cmd);
        Janela();
        ~Janela();
        SDL_Renderer* get_renderer();
        int getw();
        int geth();
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& get_canal();
    };
};

#endif