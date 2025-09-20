#ifndef H_CONC_MIGHTYTREE
#define H_CONC_MIGHTYTREE
#include "../../base/musica/Musica.hpp"
#include "../../base/musica/OndaQuadrada.hpp"
#include "../../base/musica/Ruido.hpp"
#include "../../assets.hpp"

namespace IDJ::BIBLIOTECA::MUSICA
{
    class SeeTheMightyTree: public IDJ::MUSICA::Musica
    {
        LOADERS::Asset<TAGS::SMIDI> fuga1_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue1_smid_start,
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue1_smid_end
        );
        LOADERS::Asset<TAGS::SMIDI> fuga2_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue2_smid_start,
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue2_smid_end
        );
        LOADERS::Asset<TAGS::SMIDI> fuga3_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue3_smid_start,
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue3_smid_end
        );
        LOADERS::Asset<TAGS::SMIDI> fuga4_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue4_smid_start,
            IDJ::ASSETS::_binary_assets_musica_mightytree_fugue4_smid_end
        );
        LOADERS::Asset<TAGS::SMIDI> hihat_a=LOADERS::Asset<TAGS::SMIDI>(
            IDJ::ASSETS::_binary_assets_musica_mightytree_hihat_smid_start,
            IDJ::ASSETS::_binary_assets_musica_mightytree_hihat_smid_end
        );
        IDJ::MUSICA::OndaQuadrada fuga1=IDJ::MUSICA::OndaQuadrada(fuga1_a, (1<<12)-1);
        IDJ::MUSICA::OndaQuadrada fuga2=IDJ::MUSICA::OndaQuadrada(fuga2_a, (1<<12)-1);
        IDJ::MUSICA::OndaQuadrada fuga3=IDJ::MUSICA::OndaQuadrada(fuga3_a, (1<<12)-1);
        IDJ::MUSICA::OndaQuadrada fuga4=IDJ::MUSICA::OndaQuadrada(fuga4_a, (1<<12)-1);
        IDJ::MUSICA::Ruido hihat=IDJ::MUSICA::Ruido(hihat_a, (1<<12)-1);
        IDJ::MUSICA::LinhaMelodica* linhas[5]={
            &fuga4, &fuga3, &fuga2, &fuga1,
            &hihat
        };
        public:
        SeeTheMightyTree(IDJ::MUSICA::Synth& s)
        :IDJ::MUSICA::Musica(s, linhas, 5)
        {fuga2.batida=&this->batida;}
    };
};

#endif