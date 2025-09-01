# Sistema de síntese

O sistema de síntese é baseado em instrumentos e é inspirado pelo MIDI.

Ele tem uma série de "músicas", que são sequências de comandos de início e fim de notas (temporizados pelo contador de amostras).

Um número qualquer de "músicas" podem estar ativas a qualquer momento.

Músicas possuem flags que permitem seu re-início (para música de fundo, por exemplo).

Músicas são usadas como efeitos sonoros (um "som" temporário é só uma música de uma nota só em um instrumento específico de "barulho").
