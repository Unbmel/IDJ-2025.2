#ifndef H_BASE_LOADERS_LOADERSBMP
#define H_BASE_LOADERS_LOADERSBMP
#include <SDL3/SDL.h>
#include "./Descomprimido.hpp"
#include <stdint.h>

namespace IDJ::TAGS
{
    struct SBMP {};
}

namespace IDJ::LOADERS
{
    SDL_Texture* assetsbmp_to_textura(Asset<TAGS::SBMP>& asset, SDL_Renderer* renderer);
}

#endif