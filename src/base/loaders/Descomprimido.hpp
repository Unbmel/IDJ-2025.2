#ifndef H_BASE_LOADERS_DESCOMPRIMIDO
#define H_BASE_LOADERS_DESCOMPRIMIDO
#include <cstdint>
#include <stdint.h>

namespace IDJ::LOADERS
{
    class Descomprimido
    {
        const char* ptr;
        uint32_t tam;
        public:
        const char* get_ptr();
        uint32_t get_tam();
        Descomprimido(const char* inicio, const char* fim);
        ~Descomprimido();
    };
    template<class T>
    class Asset: public Descomprimido{
        public:
        Asset(const char* inicio, const char* fim): Descomprimido(inicio, fim){};
    };
}

#endif