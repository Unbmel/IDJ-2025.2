#include "Mundo.hpp"
#include "ObjetoDesenhavel.hpp"

namespace IDJ::MUNDO
{
    void Mundo::add_desenhavel(ObjetoDesenhavel* obj)
    {
        this->objetos.emplace(obj);
        this->desenhaveis.emplace(obj);
    }
    void Mundo::add_obj(Objeto* obj)
    {
        this->objetos.emplace(obj);
    }
    void Mundo::desenhar()
    {
        for(ObjetoDesenhavel* d:this->desenhaveis)
            d->desenhar();
        this->real.receber({.tipo=MENSAGENS::ComandoGrafico::COMMIT});
    }
    void Mundo::tratar_grafico(void *ref_obj, MENSAGENS::ComandoGrafico cmd)
    {
        Mundo* self = (Mundo*) ref_obj;
        switch(cmd.tipo)
        {
            case MENSAGENS::ComandoGrafico::DESENHA:
                MENSAGENS::ComandoGrafico movido;
                movido.tipo=cmd.tipo;
                movido.dados.desenha.clip=cmd.dados.desenha.clip;
                movido.dados.desenha.txtr=cmd.dados.desenha.txtr;
                movido.dados.desenha.dest.h=cmd.dados.desenha.dest.h;
                movido.dados.desenha.dest.w=cmd.dados.desenha.dest.w;
                movido.dados.desenha.dest.x=cmd.dados.desenha.dest.x-self->pos_camera.x;
                movido.dados.desenha.dest.y=cmd.dados.desenha.dest.y-self->pos_camera.y;
                self->real.receber(movido);
                break;
            case MENSAGENS::ComandoGrafico::COMMIT:
            default:
                self->real.receber(cmd);
        }
    }
    MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& Mundo::get_camera()
    {
        return this->camera;
    }
}