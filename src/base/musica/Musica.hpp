#ifndef H_BASE_MUSICA_MUSICA
#define H_BASE_MUSICA_MUSICA
#include "Synth.hpp"
#include "LinhaMelodica.hpp"
#include <SDL3/SDL_audio.h>
#include <cstdint>

namespace IDJ::MUSICA
{
    class Musica
    {
        Synth& synth;
        uint8_t flags;
        SDL_AudioStream* stream;
        static const uint8_t REPETIR = 1<<0;
        static const uint8_t ACABOU = 1<<1;
        static const uint8_t TOCANDO = 1<<2;
        LinhaMelodica** linhas;
        uint8_t n_linhas;
        public:
        uint8_t batida=0;
        Musica(Synth& s, LinhaMelodica** linhas, uint8_t n_linhas);
        ~Musica();
        void tocar();
        void parar();
        void set_repetir();
        void unset_repetir();
        void zerar();
        static void callback_audio(void* self, SDL_AudioStream* stream, int tanto_min, int tanto_req);
    };
}

#endif