#include "Synth.hpp"
#include "../SDL.hpp"
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_init.h>
#include <cstdio>

namespace IDJ::MUSICA
{
    Synth::Synth()
    {
        if(!SDL_Init(SDL_INIT_AUDIO))sair_erro_SDL("Inicialização do contexto de áudio", NULL);
        this->audio = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
        printf("Audio dev id %u\n", this->audio);
        if(!this->audio)sair_erro_SDL("Abrir dispositivo de áudio", NULL);
    }
    Synth::~Synth()
    {
        SDL_CloseAudioDevice(this->audio);
    }
    SDL_AudioDeviceID Synth::get_id()
    {
        return this->audio;
    }
}