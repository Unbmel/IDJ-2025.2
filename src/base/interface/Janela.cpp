#include "Janela.hpp"
#include "../SDL.hpp"
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <cstdio>

namespace IDJ::INTERFACE
{
    Janela::Janela(): real(this, tratar_grafico)
    {
        this->Win = SDL_CreateWindow(
            "Amélia Oliveira Freitas da Silva - 190037971",
            1200, 900,
            SDL_WINDOW_OPENGL
        );
        if(!this->Win)IDJ::sair_erro_SDL("Erro na inicialização da janela", NULL);
        this->render = SDL_CreateRenderer(this->Win, 0);
        //SDL_SetRenderScale(this->render, 8, 8);
        if(!this->render)
            IDJ::sair_erro_SDL("Erro na criação do renderer", this->Win);
    }
    Janela::~Janela()
    {
        SDL_DestroyRenderer(this->render);
        SDL_DestroyWindow(this->Win);
    }
    SDL_Renderer* Janela::get_renderer()
    {
        return this->render;
    }
    MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& Janela::get_canal()
    {
        return this->real;
    }
    void Janela::tratar_grafico(void *ref_obj, MENSAGENS::ComandoGrafico cmd)
    {
        Janela* self = (Janela*)ref_obj;
        switch(cmd.tipo)
        {
            case MENSAGENS::ComandoGrafico::DESENHA:
            {
                SDL_FRect clip = {
                    .x=(float) cmd.dados.desenha.clip.x,
                    .y=(float) cmd.dados.desenha.clip.y,
                    .w=(float) cmd.dados.desenha.clip.w,
                    .h=(float) cmd.dados.desenha.clip.h,
                };
                SDL_FRect dest = {
                    .x=(float) cmd.dados.desenha.dest.x,
                    .y=(float) cmd.dados.desenha.dest.y,
                    .w=(float) cmd.dados.desenha.dest.w,
                    .h=(float) cmd.dados.desenha.dest.h,
                };
                /*
                printf(
                    "Renderizando em (%f, %f), tamanho (%f, %f), do clip (%f,%f,%f,%f)\n",
                    dest.x, dest.y, dest.w, dest.h,
                    clip.x, clip.y, clip.w, clip.h
                );
                //*/
                //*
                SDL_RenderTexture(
                    self->render,
                    cmd.dados.desenha.txtr,
                    &clip,
                    &dest
                );
                //*/
            }
            break;
            case MENSAGENS::ComandoGrafico::COMMIT:
            default:
                SDL_RenderPresent(self->render);
        }
    }
}