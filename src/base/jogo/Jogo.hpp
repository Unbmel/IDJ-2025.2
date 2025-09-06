#ifndef H_BASE_JOGO_JOGO
#define H_BASE_JOGO_JOGO
#include "../interface/Janela.hpp"
#include "../mundo/Mundo.hpp"
#include <cstdint>

namespace IDJ::JOGO
{
    class Jogo
    {
        MUNDO::Mundo& mundo;
        INTERFACE::Janela& janela;
        uint32_t quantum;
        public:
        Jogo(
            MUNDO::Mundo& mundo,
            INTERFACE::Janela& janela,
            uint32_t fps
        ):
            mundo(mundo),
            janela(janela),
            quantum(1000/fps)
        {};
        uint32_t frame(); // Retorna o número de milissegundos restantes na janela do frame
        void frame_delay(); // Incorpora o delay da função "frame"
        void loop();
    };
}

#endif