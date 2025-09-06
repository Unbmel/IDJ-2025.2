# Delta-t

Para evitar trabalhar com delta-t variável, presumiremos que o processamento sempre caberá na janela que alocamos para um frame. Isso permite inclusive mantermos um "FPS" estável.

Se calculássemos o delta-t no início de cada frame e usássemos para fazer os cálculos de movimentos e colisões, poderíamos acabar com pulos gigantescos quando tivéssemos "engasgos" de CPU por cause de outros processos. É melhor o jogo ficar mais lento que termos explosões de movimento.

# Aritmética de ponto fixo

Decidi usar ponto fixo ao invés de ponto flutuante por dois motivos:

- A estética do jogo é "antiga"
- Operações em decimais são marginalmente mais rápidas que operações em floats (ao menos na minha CPU dentro dos testes que eu fiz)

# Cross-compilation

Como o projeto permite o uso de MinGW, decidi fazer todo o desenvolvimento e compilação no linux, que é um ambiente mais amigável para desenvolvedores.

Os binários para windows são compilados com as bibliotecas do MinGW e são linkados estaticamente, para evitar shenanigans de DLL. Os binários foram testados no Windows 11.

# SBMP

Sprites foram guardados em um formato simples que chamei de "SBMP".

SBMPs são sequências de imagens de mesmo tamanho com pixels no formato "AIII" (alpha, intensidadex3).

O formato é o seguinte (little-endian):

```
String "SBM"
16-bit unsigned int largura_frame
16-bit unsigned int altura_frame
16-bit unsigned int frames_count
Frames ((altura*largura*frames+1)//2):
    - Formato AIII, 1 bit alpha, 3 bit intensidade
    4-bit pixel n
    4-bit pixel n+1 (0 se for o último e o número for ímpar)
```

O uso de 16 bits permite que o formato fique pequeno, mas suporte arquivos grandes com muitos frames (o ponteiro máximo para o final de um frame ainda cabe em 32 bits).
