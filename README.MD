# Projeto(s) de IDJ

Para montar o projeto, siga o padrão de projetos GNU:

```sh
./configure
make
```

Para compilar para windows com MinGW, você precisará de um cross-compiler. Geralmente há um pacote com "mingw-w64". Pesquise para o seu sistema.

```sh
./configure --host=x86_64-w64-mingw32
make
```

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
