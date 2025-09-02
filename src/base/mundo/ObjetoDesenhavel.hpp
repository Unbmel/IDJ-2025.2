#ifndef H_BASE_MUNDO_OBJETODESENHAVEL
#define H_BASE_MUNDO_OBJETODESENHAVEL
#include "Objeto.hpp"
#include "Desenhavel.hpp"
namespace IDJ::MUNDO
{
    class ObjetoDesenhavel: public Objeto
    {
        Desenhavel& des;
        public:
        ObjetoDesenhavel(Desenhavel& des): des(des){};
        void desenhar();
    };
}
#endif