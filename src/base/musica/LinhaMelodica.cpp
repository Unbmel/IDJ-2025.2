#include "LinhaMelodica.hpp"
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <cstdio>
#include "../SDL.hpp"
#include "Samplerate.h"

namespace IDJ::MUSICA
{
    LinhaMelodica::LinhaMelodica(LOADERS::Asset<TAGS::SMIDI>& f, int16_t volume)
    :fonte(f),
    tempo_midi_atual(0),tempo_ms16_atual(0), contador_samples(0),
    evento_atual(0), flags(0), tempo_ms16_atual_onda(0),
    volume(volume)
    {
        uint32_t tam = fonte.get_tam();
        if(tam<7)sair_errostring("Instanciação de linha melódica", "Asset selecionado não tem tamanho suficiente para guardar música");
        this->periodo_midi = 1000; //TODO: Corrigir problemas de tempo (*((uint16_t*)(fonte.get_ptr()+3)));
        this->periodo_atual = this->periodo_midi;
        this->n_eventos = (tam-5)/2;
        this->eventos = (ComandoSMIDI*)(fonte.get_ptr()+5);
    }
    void LinhaMelodica::zerar()
    {
        this->tempo_midi_atual=0;
        this->tempo_ms16_atual=0;
        this->tempo_ms16_atual_onda=0;
        this->contador_samples=0;
        this->evento_atual = 0;
        this->flags = 0;
    }
    static const uint16_t periodos[] = {
        1956, 1847, 1743, 1645, 1553, 1466, 1383, 1306, 1232, 1163, 1098, 1036, 978, 923, 871, 822, 776, 733, 691, 653, 616, 581, 549, 518, 489, 461, 435, 411, 388, 366, 345, 326, 308, 290, 274, 259, 244, 230, 217, 205, 194, 183, 172, 163, 154, 145, 137, 129, 122, 115, 108, 102, 97, 91, 86, 81, 77, 72, 68, 64, 61, 57, 54, 51, 48, 45, 43, 40, 38, 36, 34, 32, 30, 28, 27, 25, 24, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    void LinhaMelodica::adicionar_samples(int16_t* samples, int n)
    {
        if(this->flags&this->ACABOU)return;
        // Samplerate = 1/s
        // ms16 = 16000/s
        // presumamos samplerate 16000, que fica bacana com a precisão do midi
        for(int i=0;i<n;i++)
        {
            this->contador_samples++;
            //Avanço do tempo em milissegundos
            if(this->contador_samples>=(SAMPLERATE/16000)-1)
            {
                this->contador_samples=0;
                this->tempo_ms16_atual+=1;
                this->tempo_ms16_atual_onda+=1;
                this->tempo_ms16_atual_onda%=this->periodo_atual;
                if(this->tempo_ms16_atual % this->periodo_midi == 0)
                {
                    this->tempo_midi_atual+=1;
                    this->tempo_ms16_atual=0;
                }
            }
            //Checagem de evento smidi
            ComandoSMIDI cmd = this->eventos[this->evento_atual];
            if(this->tempo_midi_atual>=cmd.intervalo)
            {
                this->tempo_midi_atual=0;
                if(cmd.tipo_nota&(1<<7))
                {
                    //printf("Nota %hu, %hu tempos\n", cmd.tipo_nota&0x7f, cmd.intervalo);
                    if(this->batida)*batida=1;
                    this->periodo_atual = periodos[(cmd.tipo_nota&0x7F)];
                    this->flags|=this->ATIVO;
                }
                else
                {
                    //printf("Off Nota %hu, %hu tempos\n", cmd.tipo_nota&0x7f, cmd.intervalo);
                    this->flags&=~this->ATIVO;
                }
                this->evento_atual+=1;
                if(this->evento_atual>=this->n_eventos)
                    this->flags|=this->ACABOU;
            }
            if(this->flags&this->ATIVO)samples[i]+=this->gerar_sample();
        }
    }
}