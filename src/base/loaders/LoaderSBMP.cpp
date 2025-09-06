#include "LoaderSBMP.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <cstdint>
#include <cstdio>
#include "../SDL.hpp"

namespace IDJ::LOADERS
{
    SDL_Texture* assetsbmp_to_textura(Asset<TAGS::SBMP>& asset, SDL_Renderer* renderer)
    {
        uint32_t tamanho = asset.get_tam();
        const char* ptr = asset.get_ptr();
        if(tamanho<=9)
            sair("Ao tentar carregar textura SBMP, o asset não tem tamanho suficiente para caber nem o header.");
        tamanho-=9;
        uint16_t w,h,n;
        uint32_t w_final,pixels;
        w=*((uint16_t*)(ptr+3));
        h=*((uint16_t*)(ptr+5));
        n=*((uint16_t*)(ptr+7));
        pixels=((uint32_t)w)*h;
        w_final = ((uint32_t)w)*n;
        ptr+=9;
        //SDL_LogInfo(0, "Dados do header: %hu(%04hX) %hu(%04hX) %hu(%04hX) %u",w,w, h,h, n,n, w_final);
        //SDL_LogInfo(0, "Precisa: (%u*%hu+1)/2=%u, tem %u", w_final, h, (w_final*h+1)/2, tamanho);
        if(tamanho<(w_final*h+1)/2)
            sair("Ao tentar carregar textura SBMP, o asset não tem tamanho suficiente para caberem todos os pixels especificados no header.");
        SDL_Texture* ret = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB1555,
            SDL_TEXTUREACCESS_STREAMING,
            w_final,
            h
        );
        if(!ret)sair_erro_SDL("Criação da textura para guardar um SBMP", NULL);
        SDL_Rect fullimg = {
            .x=0,.y=0,
            .w=(int)w_final,.h=h // Cast para int pode causar problemas!
            //Não vou resolver isso agora. Boa sorte, pessoa do futuro.
        };
        uint16_t* img_pixels;
        int linha;//Mesmo problema de casting!
        if(!SDL_LockTexture(
            ret,
            &fullimg,
            (void**)&img_pixels,
            (int*)&linha
        ))
            sair_erro_SDL("Locking da textura para carregar um asset", NULL);
        linha /= 2;
        uint32_t frame_img = (h*linha);
        const char* INTE = " .oOxX%#";
        for(uint16_t frame=0;frame<n;frame++)
        for(uint16_t y=0;y<h;y++)
        for(uint32_t x=0;x<w;x+=2)
        {
            uint8_t in = ptr[(frame*pixels/2)+(y*(w/2))+(x/2)];
            uint16_t out;
            uint8_t intensidade;
            //Pixel 1
            //Alpha
            out = (in&0b10000000)<<(15-7);
            //Intensidade
            intensidade = (
                (in&0b01110000)//3 bits
                >> 2 //5 bits!
            );
            out |= intensidade|(intensidade<<5)|(intensidade<<10);
            img_pixels[(frame*w)+(y*linha)+x] = out;
            if(x+1>=w)continue;
            //Pixel 2
            //Alpha
            out = (in&0b00001000)<<(15-3);
            //Intensidade
            intensidade = (
                (in&0b00000111)//3 bits
                << 2 //5 bits!
            );
            out |= intensidade|(intensidade<<5)|(intensidade<<10);
            img_pixels[(frame*w)+(y*linha)+x+1] = out;
        };
        SDL_UnlockTexture(ret);
        SDL_SetTextureScaleMode(ret, SDL_SCALEMODE_NEAREST);
        return ret;
    }
}