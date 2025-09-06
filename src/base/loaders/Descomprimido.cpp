#include "Descomprimido.hpp"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <zlib.h>
#include <cstdint>
#include "../SDL.hpp"
#include <list>
#include "../../autoconf.h"

namespace IDJ::LOADERS
{
    #ifdef ASSETS_COMPRIMIDOS
    Descomprimido::Descomprimido(const char* inicio, const char* fim)
    {
        const size_t TAM = 1024;
        z_stream z;
        z.avail_in = fim - inicio;
        z.next_in = (Bytef *) inicio;
        z.zalloc = Z_NULL;
        z.zfree = Z_NULL;
        int erron;
        if((erron=inflateInit(&z))!=Z_OK)
            IDJ::sair_errostring("Descompressão - Inicialização", zError(erron));
        uint32_t len = 0;
        uint32_t rlen = 0;
        std::list<char*> blocos;
        for(;;)
        {
            char* bloco = (char*) std::malloc(TAM);
            blocos.emplace_back(bloco);
            z.avail_out = TAM;
            z.next_out = (Bytef*) bloco;
            erron = inflate(&z, Z_SYNC_FLUSH);
            len += TAM - z.avail_out;
            rlen += TAM;
            if(erron==Z_STREAM_END)break;
            else if(erron!=Z_OK)
                IDJ::sair_errostring("Descompressão - Inflando", zError(erron));
        }
        this->ptr = (char*) std::malloc(len);
        this->tam = len;
        char* dst = (char*) this->ptr;
        for(char* ptr: blocos)
        {
            memcpy(dst, ptr, len>TAM?TAM:len);
            /*
            for(int c=0;c<TAM;c++)
                printf("%02X", dst[c]);
            printf("\n");
            //*/
            std::free(ptr);
            dst+=TAM;
            len-=TAM;
        }
    }
    Descomprimido::~Descomprimido()
    {
        std::free((void*) this->ptr);
    }
    #else
    Descomprimido::Descomprimido(const char* inicio, const char* fim)
    {
        this->ptr = inicio;
        this->tam = fim - inicio;
    }
    Descomprimido::~Descomprimido()
    {
    }
    #endif
    uint32_t Descomprimido::get_tam()
    {
        return this->tam;
    }
    const char* Descomprimido::get_ptr()
    {
        return this->ptr;
    }
}