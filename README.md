🎮 Jogo de Adivinhação de Palavras - Versão Console (C)
Bem-vindo ao WordGuess Console Game, um jogo de adivinhação de palavras com múltiplas rodadas, níveis de dificuldade e sistema de pontuação em tempo real!

📋 Sobre o Projeto
Este é um jogo desenvolvido em linguagem C, totalmente jogável pelo terminal/console. O jogador deve adivinhar palavras secretas de diferentes tamanhos e dificuldades, dentro de um número limitado de tentativas. A cada tentativa, o jogador recebe feedback colorido indicando quais letras estão corretas e nas posições certas.

🎯 Funcionalidades Principais
✅ Modo de jogo com 14 rodadas progressivas (Fácil, Médio e Difícil)
✅ Sistema de pontuação baseado em performance (tentativas e tempo)
✅ Cronômetro em tempo real durante as rodadas
✅ Feedback de letras colorido por status (acerto, letra presente em outra posição, ou erro)
✅ Histórico de partidas armazenado na sessão
✅ Possibilidade de pausar, reiniciar rodada ou voltar ao menu a qualquer momento

🕹️ Como Jogar
📌 Controles durante o jogo:
1 → Voltar ao Menu Principal

2 → Pausar Jogo

3 → Reiniciar a Rodada Atual

📌 Regras:
O jogador digita o palpite letra por letra no terminal.

Cada tentativa gera um feedback visual (com cores) mostrando o status de cada letra:

🟩 Verde: Letra correta no lugar correto

🟨 Amarelo: Letra correta no lugar errado

🟥 Vermelho: Letra incorreta

O número de tentativas varia conforme a dificuldade:

Fácil: 8 tentativas

Médio: 6 tentativas

Difícil: 4 tentativas

O tempo gasto afeta a exibição, mas a pontuação só considera tentativas.

🏗️ Estrutura do Projeto
css
Copiar
Editar
.
├── main.c
├── jogo.c
├── jogo.h
├── utils.c
├── utils.h
└── README.md
Obs: Dependendo de como você organizou seus arquivos, adapte os nomes dos .c e .h que você está usando.

🖥️ Tecnologias Utilizadas
Linguagem: C

Recursos:

Uso de alocação dinâmica de memória (malloc e free)

Manipulação de tempo com time.h

Manipulação de teclado em tempo real (_kbhit(), _getch(), Sleep())

Impressão com códigos de cor ANSI (compatível com Windows e Linux com ajustes)

🧪 Requisitos para Compilar e Rodar
Um compilador C compatível: GCC, MinGW, ou TCC

Terminal com suporte a cores ANSI (cmd, PowerShell, ou terminal Linux)

Exemplo de compilação no terminal:
bash
Copiar
Editar
gcc main.c jogo.c utils.c -o WordGuessGame
./WordGuessGame
🏅 Próximos Passos / Melhorias Futuras (Ideias)
Implementar um sistema de salvamento em arquivo (persistência de histórico)

Criar uma versão gráfica (com SDL ou outra lib)

Adicionar níveis customizáveis pelo jogador

Suporte a ranking de jogadores

Palavras aleatórias de dicionário externo

👨‍💻 Autores
João Gabriel Moura Rosa
Antônio Biscotto Neto

Acadêmicos de Engenharia de Software
 
