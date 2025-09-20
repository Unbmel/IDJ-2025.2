#ifndef H_BASE_MUSICA_LINHAMELODICA
#define H_BASE_MUSICA_LINHAMELODICA
#include "../loaders/Descomprimido.hpp"
#include <cstdint>

namespace IDJ::TAGS
{
    struct SMIDI{};
}

namespace IDJ::MUSICA
{
    struct ComandoSMIDI
    {
        uint8_t tipo_nota; // TNNNNNNN, t=1 para ligar, 0 desligar, N = número da nota MIDI
        uint8_t intervalo; // Intervalo em 16 avos de nota
    };

    struct HeaderSMIDI
    {
        const char magic[3];
        const uint16_t msptm; // Mili-segundos por tempo midi - usado para conversão dos tempos
    };

    class LinhaMelodica
    {
        protected:
        LOADERS::Asset<TAGS::SMIDI>& fonte;
        uint16_t contador_samples;
        uint16_t tempo_ms16_atual;
        uint16_t tempo_ms16_atual_onda;
        uint16_t tempo_midi_atual;
        uint16_t evento_atual;
        uint16_t n_eventos;
        uint16_t periodo_midi;
        uint16_t periodo_atual;
        ComandoSMIDI* eventos;
        public:
        static const uint8_t ATIVO=1<<0;
        static const uint8_t ACABOU=1<<1;
        uint8_t *batida=0;
        uint8_t flags;
        LinhaMelodica(LOADERS::Asset<TAGS::SMIDI>& f, int16_t volume);
        void zerar();
        uint16_t volume;
        void adicionar_samples(int16_t* samples, int n);
        virtual inline int16_t gerar_sample() = 0;
    };
}

#endif