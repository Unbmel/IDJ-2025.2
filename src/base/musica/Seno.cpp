#include "Seno.hpp"
#include <cstdint>

namespace IDJ::MUSICA
{
    /*
    Seno((x-0.5)*2*pi)
    Espera entradas ponto-fixo de 10 bits de precisão com sinal
    Por que 10 bits? Sinal + 3 inteiro (-8 a 8) + precisão. Bom pro nosso alcance.
    As entradas devem ser entre 0 e 1 (0b01000000 00000000)
    Vide approx_sen.py para entender a aproximação
    */
    int16_t seno(int16_t x)
    {
        const int16_t k1 = 1010;//.9872 10 bits
        const int16_t k3 = -158;//-.1548 10 bits
        const int16_t k5 = 5;//0.00560059 10 bits
        int16_t res, pot;
        x-=512;//0.5 10 bits, x \in [-0.5,0.5]
        x=(x>>5)*(pi_10bit>>5);//x\in [-2*pi,2*pi]
        res=(x>>5)*(k1>>5);
        pot=(x>>5)*(x>>5)*(x>>5);
        res+=(pot>>5)*(k3>>5);
        pot=(pot>>5)*(x>>5)*(x>>5);
        return res+((pot>>5)*(k5>>5));
    }
}