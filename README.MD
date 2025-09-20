# Projeto(s) de IDJ

Para montar o projeto, siga o padrão de projetos GNU:

```sh
./configure
make
```

Para compilar para windows com MinGW, você precisará de um cross-compiler. Geralmente há um pacote com "mingw-w64". Pesquise para o seu sistema.

```sh
./configure --host=x86_64-w64-mingw32 --build=x86_64
make
```

> Assegure que você instalou/compilou a biblioteca .dll para mingw - a SDL sempre libera duas versões diferentes: mingw e "normal".

O projeto é compilado exclusivamente em ambientes com:
- Bourne shell
- GNU Make
- Algum compilador de C++

A maioria dos sistemas GNU/Linux se encaixam nessa descrição. Não sei se Windows+MinGW também se encaixa.

A geração dos scripts de configuração pode ser re-feita com `autoreconf`, mas não é necessária (as releases são teoricamente prontas como qualquer outro projeto GNU-compliant).

Mais informação pode ser encontrada no diretório [docs](./docs/):
- [Detalhes](./docs/DetalhesTecnicos.md) de decisões técnicas tomadas no desenvolvimento
- O [planejamento](./docs/Planejamento.md) do projeto
- A descrição do sistema de [síntese](./docs/Synth.md) de áudio.

# Notas de propriedade intelectual

As músicas descritas na pasta [assets/musica](./assets/musica/) são arranjos originais meus sobre músicas que não são minhas (criados com o software [LMMS](https://lmms.io/)) posteriormente convertidos para o formato que criei aqui usando o script disponível na pasta [scripts](./scripts/midi_to_smidi.py).

Aqui e nos créditos do jogo, listo o seguinte:

- Música:
    - Take Five
        - Música usada no combate/fases do jogo
        - Arranjo para trio de ondas quadradas (e ruído branco) por Amélia O. F da S. (2025), baseado na composição original por Paul Desmond (1959)
    - See the mighty tree
        - Música usada no menu
        - Arranjo para quarteto de ondas quadradas (e ruído branco) por Amélia O. F da S. (2025), baseado na composição original por Louis "Moondog" Thomas Hardin (1981)