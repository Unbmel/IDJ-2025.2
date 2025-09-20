#include "../base/interface/Janela.hpp"
#include "../base/mundo/Mundo.hpp"
#include "../base/mundo/SBMPDesenhavel.hpp"
#include "../base/loaders/LoaderSBMP.hpp"
#include "../base/jogo/Jogo.hpp"
#include "../assets.hpp"
#include "../base/musica/Synth.hpp"
#include "../concreto/musicas/MightyTree.hpp"
#include "../concreto/musicas/TakeFive.hpp"
#include <SDL3/SDL_asyncio.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>

int main()
{
    using namespace IDJ;
    INTERFACE::Janela janela;
    MUNDO::Mundo mundo(janela.get_canal());
    MUSICA::Synth synth;

    std::cout<<"Carregando e descompactando assets...\n";
    LOADERS::Asset<TAGS::SBMP> placeholder_asset(
        IDJ::ASSETS::_binary_assets_placeholder_sbmp_start,
        IDJ::ASSETS::_binary_assets_placeholder_sbmp_end
    );
    LOADERS::Asset<TAGS::SBMP> zann_asset(
        IDJ::ASSETS::_binary_assets_zann_sbmp_start,
        IDJ::ASSETS::_binary_assets_zann_sbmp_end
    );
    BIBLIOTECA::MUSICA::SeeTheMightyTree SeeTheMightyTree(synth);
    BIBLIOTECA::MUSICA::TakeFive TakeFive(synth);
    std::cout<<"Assets carregados em memória!\n";
    MUNDO::SBMPDesenhavel placeholder_des(
        mundo.get_camera(), placeholder_asset,
        janela.get_renderer()
    );
    MUNDO::SBMPDesenhavel placeholder2_des(
        mundo.get_camera(), placeholder_asset,
        janela.get_renderer()
    );
    placeholder2_des.sprite.dest.x=placeholder2_des.sprite.dest.w;
    MUNDO::SBMPDesenhavel zann_des(
        mundo.get_camera(), zann_asset,
        janela.get_renderer()
    );
    MUNDO::ObjetoDesenhavel placeholder(placeholder_des);
    MUNDO::ObjetoDesenhavel placeholder2(placeholder2_des);
    MUNDO::ObjetoDesenhavel zann(zann_des);
    zann_des.sprite.dest.y=janela.geth()-zann_des.sprite.dest.h;
    mundo.add_desenhavel(&zann);
    mundo.add_desenhavel(&placeholder);
    mundo.add_desenhavel(&placeholder2);

    JOGO::Jogo jogo(mundo, janela, 25); //lixo para causar recompilação 1xsad

    MUSICA::Musica& mus = TakeFive;

    mus.set_repetir();
    mus.tocar();

    //Tudo isso será removido e administrado pelos estados de jogo
    int16_t vx=7,vy=2, i=0;
    int16_t vx2=3,vy2=2;
    int16_t sinal=(1<<15);
    for(;;)
    {
        if(mus.batida)
        {
            placeholder_des.prox_frame();
            placeholder2_des.prox_frame();
            mus.batida=0;
        }
        placeholder_des.sprite.dest.x+=vx;
        placeholder_des.sprite.dest.y+=vy;
        int16_t mod = vx*(1-2*((uint16_t)(vx&sinal)>>15));
        if(placeholder_des.sprite.dest.x>1200-placeholder_des.sprite.clip.w)vx=-mod;
        if(placeholder_des.sprite.dest.x<0){vx=mod;placeholder_des.sprite.dest.x=0;}
        mod = vy*(1-2*(((uint16_t)vy&sinal)>>15));
        if(placeholder_des.sprite.dest.y>900-placeholder_des.sprite.clip.h)vy=-mod;
        if(placeholder_des.sprite.dest.y<0){vy=mod;placeholder_des.sprite.dest.y=0;}
        
        placeholder2_des.sprite.dest.x+=vx2;
        placeholder2_des.sprite.dest.y+=vy2;
        mod = vx2*(1-2*((uint16_t)(vx2&sinal)>>15));
        if(placeholder2_des.sprite.dest.x>1200-placeholder2_des.sprite.clip.w)vx2=-mod;
        if(placeholder2_des.sprite.dest.x<0){vx2=mod;placeholder2_des.sprite.dest.x=0;}
        mod = vy2*(1-2*((uint16_t)(vy2&sinal)>>15));
        if(placeholder2_des.sprite.dest.y>900-placeholder2_des.sprite.clip.h)vy2=-mod;
        if(placeholder2_des.sprite.dest.y<0){vy2=mod;placeholder2_des.sprite.dest.y=0;}
        
        jogo.frame_delay();

        //Demonstração de colisão
        struct {int16_t x; int16_t y;} dirs[4] = {
            {1, 1}, {-1, 1}, {1, -1}, {-1,-1}
        };
        SDL_Point pontos[4] = {
            {.x=placeholder_des.sprite.dest.x,.y=placeholder_des.sprite.dest.y},
            {.x=placeholder_des.sprite.dest.x+placeholder_des.sprite.dest.w,.y=placeholder_des.sprite.dest.y},
            {.x=placeholder_des.sprite.dest.x,.y=placeholder_des.sprite.dest.y+placeholder_des.sprite.dest.h},
            {.x=placeholder_des.sprite.dest.x+placeholder_des.sprite.dest.w,.y=placeholder_des.sprite.dest.y+placeholder_des.sprite.dest.h},
        };
        for(int j=0;j<4;j++)
        {
            if(SDL_PointInRect(&pontos[j], &placeholder2_des.sprite.dest))
            {
                if(!(vx*dirs[j].x>0))vx=-vx;
                if(!(vy*dirs[j].y>0))vy=-vy;
                if((vx2*dirs[j].x>0))vx2=-vx2;
                if((vy2*dirs[j].y>0))vy2=-vy2;
            }
        }

        SDL_PumpEvents();
        const bool* keys = SDL_GetKeyboardState(NULL);
        if(keys[SDL_SCANCODE_Q])break;//Isso não detecta caso alguém pressione e solte entre frames
    }
}