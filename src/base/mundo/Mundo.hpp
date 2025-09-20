#ifndef H_BASE_MUNDO_MUNDO
#define H_BASE_MUNDO_MUNDO
#include <list>
#include "Objeto.hpp"
#include "ObjetoDesenhavel.hpp"

namespace IDJ::MUNDO
{
    class Mundo
    {
        std::list<Objeto*> objetos;
        std::list<ObjetoDesenhavel*> desenhaveis;
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico> camera;
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& real;
        public:
        static void tratar_grafico(void* ref_obj, MENSAGENS::ComandoGrafico cmd);
        void add_obj(Objeto* obj);
        void add_desenhavel(ObjetoDesenhavel* obj);
        void desenhar();
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& get_camera();
        struct {int x; int y;} pos_camera;
        Mundo(MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& real):
            camera(this, this->tratar_grafico),
            real(real),
            pos_camera{.x=0,.y=0}
        {};
    };
}
#endif