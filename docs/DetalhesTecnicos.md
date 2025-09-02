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
