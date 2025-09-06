#ifndef H_BASE_MUSICA_SYNTH
#define H_BASE_MUSICA_SYNTH
#include <SDL3/SDL_audio.h>

namespace IDJ::MUSICA
{
    class Synth
    {
        SDL_AudioDeviceID audio;
        public:
        Synth();
        ~Synth();
        SDL_AudioDeviceID get_id();
    };
}

#endif