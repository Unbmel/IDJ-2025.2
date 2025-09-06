#include "../base/interface/Janela.hpp"
#include "../base/mundo/Mundo.hpp"
#include "../base/mundo/SBMPDesenhavel.hpp"
#include "../base/loaders/LoaderSBMP.hpp"
#include "../base/jogo/Jogo.hpp"
#include "../assets.hpp"
#include "../base/musica/Synth.hpp"
#include "../base/musica/Seno.hpp"
#include "../base/SDL.hpp"
#include <SDL3/SDL_asyncio.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>

//Estou recuperando de uma enxaqueca. Não consigo trabalhar direito nem comer e estou com sono e fome
//É o dia anterior à entrega.
//Vou apagar isso tudo e fazer um sistema decente para o jogo quando estiver em condição de pensar
//mas para entregar o requisito de "ter música", vou fazer essa gambiarra e ir dormir
void gera_notas(void* nulo, SDL_AudioStream* stream, int tanto_min, int tanto_req)
{
    static uint16_t freq = 220;
    uint16_t* samples = (uint16_t*) malloc(tanto_req);

    //1 sample = 1/16000s
    //T = 1/f s
    //1 sample = (1/16000)/(1/f) progresso
    //f/16000 progresso
    static double progresso = (((double)freq)/(16000));
    static double cur = 0;
    static double secs = 0;
    static uint16_t seminota = 1;
    static uint16_t notas[]={440, 392, 349, 392};
    /*
    n*2^-5 / m*2^-15
    n/m * 2^10  - 10 bits de fração
    */
    static bool troca=0;
    for(int i=0;i<tanto_req/2;i++)
    {
        if(0 && !troca)samples[i]=0;
        else
        {
            /*
            s*p*2^10
            */
            samples[i]=(1<<10)*SDL_sin(cur*2*3.14);
        }
        cur+=progresso;
        cur=SDL_fmod(cur, 1.0);
        secs+=1.0/16000;
        if(secs>0.3/2)
        {
            secs=0.0;
            troca=!troca;
            if(!troca)
            {
                freq = notas[seminota/4]/((seminota%2==0?2:1));
                seminota++;
                seminota%=16;
                progresso = (((double)freq)/(16000));
            }
        }
    }
    SDL_PutAudioStreamData(stream, samples, tanto_req);
    free(samples);
}

int main()
{
    using namespace IDJ;
    std::cout<<"Carregando e descompactando assets...\n";
    LOADERS::Asset<TAGS::SBMP> placeholder_asset(
        IDJ::ASSETS::_binary_assets_placeholder_sbmp_start,
        IDJ::ASSETS::_binary_assets_placeholder_sbmp_end
    );
    std::cout<<"Assets carregados em memória!\n";

    INTERFACE::Janela janela;
    MUNDO::Mundo mundo(janela.get_canal());
    MUNDO::SBMPDesenhavel placeholder_des(
        mundo.get_camera(), placeholder_asset,
        janela.get_renderer()
    );
    MUNDO::ObjetoDesenhavel placeholder(placeholder_des);
    mundo.add_desenhavel(&placeholder);

    JOGO::Jogo jogo(mundo, janela, 30);

    MUSICA::Synth synth;
    SDL_AudioSpec saida, entrada = {
        .format=SDL_AUDIO_S16,
        .channels=1,
        .freq=16000
    };
    int sf;
    SDL_GetAudioDeviceFormat(synth.get_id(), &saida, &sf);
    SDL_AudioStream* stream = SDL_CreateAudioStream(&entrada, &saida);
    if(!stream)sair_erro_SDL("Criação do stream", NULL);
    SDL_SetAudioStreamGetCallback(
        stream, 
        gera_notas,
        NULL
    );

    if(!SDL_BindAudioStream(synth.get_id(), stream))sair_erro_SDL("Bind audio stream", NULL);

    //Tudo isso será removido e administrado pelos estados de jogo
    int16_t vx=10,vy=10, i=0;
    for(;;)
    {
        jogo.frame_delay();
        if((i=(i+1)%10)==0)
            placeholder_des.prox_frame();
        placeholder_des.sprite.dest.x+=vx;
        placeholder_des.sprite.dest.y+=vy;
        if(placeholder_des.sprite.dest.x>1200-placeholder_des.sprite.clip.w)vx=-vx;
        if(placeholder_des.sprite.dest.y>900-placeholder_des.sprite.clip.h)vy=-vy;
        if(placeholder_des.sprite.dest.x<0)vx=-vx;
        if(placeholder_des.sprite.dest.y<0)vy=-vy;
        SDL_PumpEvents();
        const bool* keys = SDL_GetKeyboardState(NULL);
        if(keys[SDL_SCANCODE_Q])break;//Isso não detecta caso alguém pressione e solte entre frames
    }
    SDL_UnbindAudioStream(stream);
}