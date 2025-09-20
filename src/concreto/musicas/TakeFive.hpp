#ifndef H_CONC_TAKEFIVE
#define H_CONC_TAKEFIVE
#include "../../base/musica/Musica.hpp"
#include "../../base/musica/OndaQuadrada.hpp"
#include "../../base/musica/Ruido.hpp"
#include "../../base/musica/Silencio.hpp"
#include "../../assets.hpp"

namespace IDJ::BIBLIOTECA::MUSICA
{
    class TakeFive: public IDJ::MUSICA::Musica
    {
        LOADERS::Asset<TAGS::SMIDI> baixo_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_takefive_baixo_smid_start,
            IDJ::ASSETS::_binary_assets_musica_takefive_baixo_smid_end
        );
        IDJ::MUSICA::OndaQuadrada baixo =IDJ::MUSICA::OndaQuadrada(baixo_a, (1<<12)-1);
        LOADERS::Asset<TAGS::SMIDI> piano_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_takefive_piano_smid_start,
            IDJ::ASSETS::_binary_assets_musica_takefive_piano_smid_end
        );
        IDJ::MUSICA::OndaQuadrada piano =IDJ::MUSICA::OndaQuadrada(piano_a, (1<<12)-1);
        LOADERS::Asset<TAGS::SMIDI> sax_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_takefive_sax_smid_start,
            IDJ::ASSETS::_binary_assets_musica_takefive_sax_smid_end
        );
        IDJ::MUSICA::OndaQuadrada sax=IDJ::MUSICA::OndaQuadrada(sax_a, (1<<12)-1);
        LOADERS::Asset<TAGS::SMIDI> hihat_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_takefive_hihat_smid_start,
            IDJ::ASSETS::_binary_assets_musica_takefive_hihat_smid_end
        );
        IDJ::MUSICA::Ruido hihat = IDJ::MUSICA::Ruido(hihat_a, (1<<12)-1);
        ///*
        LOADERS::Asset<TAGS::SMIDI> ritmo_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_takefive_ritmo_smid_start,
            IDJ::ASSETS::_binary_assets_musica_takefive_ritmo_smid_end
        );
        IDJ::MUSICA::Silencio ritmo = IDJ::MUSICA::Silencio(ritmo_a, (1<<12)-1);
        //*/
        
        IDJ::MUSICA::LinhaMelodica* linhas[5]={
            &hihat,
            &baixo, &piano, &sax,
            &ritmo
        };
        public:
        TakeFive(IDJ::MUSICA::Synth& s)
        :IDJ::MUSICA::Musica(s, linhas, 5)
        {this->ritmo.batida=&this->batida;}
    };
};

#endif