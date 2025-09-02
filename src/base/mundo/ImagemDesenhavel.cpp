#include "ImagemDesenhavel.hpp"

namespace IDJ::MUNDO
{
    void ImagemDesenhavel::desenhar()
    {
        this->comandar({
            .tipo=MENSAGENS::ComandoGrafico::DESENHA,
            .dados = {
                .desenha = this->sprite
            }
        });
    }
}