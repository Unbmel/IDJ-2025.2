#ifndef H_BASE_MUNDO_DESENHAVEL
#define H_BASE_MUNDO_DESENHAVEL
#include "../mensagens/Canal.hpp"
#include "../mensagens/ComandoGrafico.hpp"

namespace IDJ::MUNDO
{
    class Desenhavel
    {
        MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo;
        public:
        virtual void desenhar()=0;
        Desenhavel(MENSAGENS::Canal<MENSAGENS::ComandoGrafico>& alvo): alvo(alvo) {};
        void comandar(MENSAGENS::ComandoGrafico cmd);
        ~Desenhavel();
    };
};

#endif