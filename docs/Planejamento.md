# Objetivos

- Objetivo primário: Cumprir com as features apresentadas em cada projeto da matéria.
    - De acordo com o que perguntei, podemos modificar a estrutura desde que o resultado ainda funcione.
- Objetivo secundário: Criar um jogo que caiba nos disquetes graváveis que ainda tenho (1474560 bytes sem sistema de arquivos, menos que isso se quisermos algum sistema de arquivos)
- Objetivo terciário: Criar um jogo interessante/com mecânicas além do sugerido.

# Arquitetura/Premissas

O jogo será modular e organizado por mensagens (e por composição mais que herança), permitindo fácil modificação e integração de novos componentes/passos de processamento.

# Ideias

## Brainstorm

- Gráficos em preto-e-branco (arquivos menores!)
- Misturar melee e ataques à distância
- Mouse só para efeitos visuais/controle no menu principal
    - Talvez só por brincadeira, possamos "petelecar" zumbis com o mouse
        - Usar essa feature demais dispara um trigger tipo as galinhas de zelda
- Boss fight com dança?
    - Música e zumbis movendo no ritmo, tipo "Crypt of the necrodancer"
    - Todos os inimigos têm ritmo? Talvez tenha de alternar melee e ataque à distância para acertar
        - Zumbi com dois escudos. Protege de ataques à distância, mas um melee bloqueia com a esquerda, outro com a direita, aí dash pra trás (forçando ataque à distância).
        - Zumbis que andam em um ciclo e o personagem tem de somente desviar (se atacar alguém, todos viram contra o jogador)
- Criar um micro-sintetizador de música!
    - MIDI é grande demais...
- Procedural. Salas definidas, mas em ordem aleatória.
    - Mapa no canto da tela. A saída está em algum lugar (a pelo menos duas salas de distância)
- Mapa em tiles, pode ter paredes. Zumbis são atrelados a um ponto-raíz e voltam "para casa" se ficarem longe demais (isso faz com que haja zonas de luta)
- Boss fight com uma aranha mecânica gigante (pernas independentes! Movimentos legais)
- Menu em 3D wireframe, só pra ficar bacana, mesmo
    - Pode ser um cubo, tetraedro, qualquer coisa geométrica legal (vide símbolo sagrado em "Chants of Sennaar")

## Features

### A fazer

- Módulos básicos
    - Geração de grafo de mensagens ("main")
    - Nó de 

### Feitas
