#include "Desenhavel.hpp"

namespace IDJ::MUNDO
{
    void Desenhavel::comandar(MENSAGENS::ComandoGrafico cmd)
    {
        this->alvo.receber(cmd);
    }
    Desenhavel::~Desenhavel(){}
}