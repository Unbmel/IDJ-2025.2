#include "Musica.hpp"
#include "LinhaMelodica.hpp"
#include "Synth.hpp"
#include <SDL3/SDL_audio.h>
#include <cstddef>
#include <cstdint>
#include "../SDL.hpp"
#include "Samplerate.h"
#include <cstdio>
#include <cstdlib>

namespace IDJ::MUSICA
{
    Musica::Musica(Synth& s, LinhaMelodica** linhas, uint8_t n_linhas)
    :synth(s), linhas(linhas), n_linhas(n_linhas),
    flags(0)
    {
        if(this->n_linhas<1)sair_errostring("Instanciação de música", "Música precisa ter ao menos uma linha melódica");
        SDL_AudioSpec saida, entrada = {
            .format=SDL_AUDIO_S16,
            .channels=1,
            .freq=SAMPLERATE
        };
        int sf;
        SDL_GetAudioDeviceFormat(synth.get_id(), &saida, &sf);
        this->stream = SDL_CreateAudioStream(&entrada, &saida);
        if(!this->stream)sair_erro_SDL("Criação do stream", NULL);
    }
    Musica::~Musica()
    {
        SDL_DestroyAudioStream(this->stream);
    }
    void Musica::zerar()
    {
        for(uint8_t i=0;i<this->n_linhas;i++)
            (this->linhas[i])->zerar();
    }
    void Musica::tocar()
    {
        if(this->flags&this->TOCANDO)return;
        this->flags|=this->TOCANDO;
        SDL_SetAudioStreamGetCallback(this->stream, this->callback_audio, this);
        if(!SDL_BindAudioStream(this->synth.get_id(), this->stream))sair_erro_SDL("Bind audio stream", NULL);
    }
    void Musica::parar()
    {
        if(!(this->flags&this->TOCANDO))return;
        this->flags&=~this->TOCANDO;
        SDL_SetAudioStreamGetCallback(this->stream, NULL, NULL);
        SDL_UnbindAudioStream(this->stream);
    }
    void Musica::set_repetir()
    {
        this->flags|=this->REPETIR;
    }
    void Musica::unset_repetir()
    {
        this->flags&=~this->REPETIR;
    }
    void Musica::callback_audio(void *self, SDL_AudioStream *stream, int tanto_min, int tanto_req)
    {
        Musica* eu = (Musica*) self;
        tanto_req = tanto_req/sizeof(uint16_t);
        int16_t *samples = (int16_t*) std::calloc(tanto_req, sizeof(uint16_t));
        if(!(eu->flags&eu->ACABOU))
        {
            uint8_t acabou = 1;
            for(uint8_t i=0;i<eu->n_linhas;i++)
            {
                eu->linhas[i]->adicionar_samples(samples, tanto_req);
                acabou = acabou && (eu->linhas[i]->flags&LinhaMelodica::ACABOU);
            }
            eu->flags|=acabou*eu->ACABOU;
        }
        else
        {
            if(eu->flags&eu->REPETIR)
            {
                eu->flags&=~eu->ACABOU;
                eu->zerar();
            }
            else eu->parar();
        }
        //for(int i=0;i<tanto_req;i++)printf("%hd,", samples[i]);
        SDL_PutAudioStreamData(eu->stream, samples, tanto_req*sizeof(int16_t));
        SDL_FlushAudioStream(stream);
        std::free(samples);
    }
};