#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h> 
#include <conio.h>   

#define COR_RESET     "\x1b[0m"
#define COR_VERDE     "\x1b[32m"
#define COR_AMARELO   "\x1b[33m"
#define COR_VERMELHO  "\x1b[31m"

/*
 Enums (enumerações) dão nomes a números, o que deixa o código mais legível.
 Em vez de checar se o status é 0, 1 ou 2, a gente checa se é STATUS_VAZIO, STATUS_VERDE, etc.
*/
enum { STATUS_VAZIO, STATUS_VERDE, STATUS_AMARELO, STATUS_VERMELHO };
enum Dificuldade { FACIL, MEDIO, DIFICIL };
/*
 A 'struct' é como um molde para criar nossas próprias variáveis complexas.
 'LetraFeedback' vai guardar cada letra de um palpite e a cor que ela deve ter.
 'Pontuacao' vai guardar as informações de um jogador no ranking.
*/
typedef struct { char letra; int statusCor; } LetraFeedback;
typedef struct { char username[50]; int pontuacao; long tempo; } Pontuacao;

const char* bancoFacil[] = { "PATO", "LIVRO", "BOLA", "GATO", "MESA", "RATO", "MOTO", "FITA", "FACA", "DADO", "AMOR", "COPO", "CEGO", "AGUA", "FOGO", "TERRA", "VENTO", "CARRO", "PEIXE", "FORTE", "VIDA", "MUSA", "POVO", "TRONO", "CAFE", "ROSA", "NAVIO", "PORTA", "CORPO", "ALMA", "SAGAZ", "AMAGO", "EXITO", "MEXER", "TERMO", "NOBRE", "SENSO", "AFETO", "ETICA", "PLENA", "MUTUA", "TENUE", "VIGOR", "SONHO", "IDEIA", "PODER", "VALOR", "PUDOR", "REGRA", "JUSTO"};
const int tamBancoFacil = sizeof(bancoFacil) / sizeof(bancoFacil[0]);
const char* bancoMedio[] = {"GARRAFA", "CASTELO", "JANELA", "CAVALO", "FLORESTA", "GOLEIRO", "PAREDE", "OBJETO", "PRINCESA", "GUERRA", "LIBERDADE", "RESPEITO", "PLANETA", "ESTRELA", "UNIVERSO", "FELIZ", "TRISTE", "AMIZADE", "FAMILIA", "ESCOLA", "TRABALHO", "DINHEIRO", "CULTURA", "MUSICA", "CINEMA", "TEATRO", "ESPORTE", "NATUREZA", "ANIMAL", "FLOR", "ARVORE", "MONTANHA", "OCEANO", "DESERTO", "CIDADE", "ESTRADA", "VIAGEM", "SONHOS", "PESADELO", "MEMORIA", "SAUDADE", "ESPERANCA", "CORAGEM", "MEDO", "ALEGRIA", "PAZ", "AMOROSO", "CARINHO", "BELEZA", "VERDADE"};
const int tamBancoMedio = sizeof(bancoMedio) / sizeof(bancoMedio[0]);
const char* bancoDificil[] = {"PROGRAMA", "INTERNET", "COMPUTADOR", "BIBLIOTECA", "DINOSSAURO", "ELEFANTE", "ORQUESTRA", "ARQUITETO", "PRESIDENTE", "MINISTERIO", "CONHECIMENTO", "SABEDORIA", "IGNORANCIA", "CIENCIA", "TECNOLOGIA", "FILOSOFIA", "PSICOLOGIA", "HISTORIA", "GEOGRAFIA", "MATEMATICA", "LITERATURA", "GRAMATICA", "VOCABULARIO", "DICIONARIO", "ENCICLOPEDIA", "PARADIGMA", "FENOMENO", "HIPOTESE", "EXPERIMENTO", "RESULTADO", "ANALISE", "SINTESE", "AVALIACAO", "CRITICA", "ARGUMENTO", "EVIDENCIA", "CONCLUSAO", "PERSPECTIVA", "CONTEXTO", "SIGNIFICADO", "INTERPRETACAO", "COMUNICACAO", "LINGUAGEM", "SOCIEDADE", "ECONOMIA", "POLITICA", "DEMOCRACIA", "JUSTICA", "ETIMOLOGIA", "PARALELO"};
const int tamBancoDificil = sizeof(bancoDificil) / sizeof(bancoDificil[0]);

Pontuacao historicoPontuacoes[100];
int totalPontuacoes = 0;

/*
 Isso aqui é tipo um "sumário" das funções que existem no código. A gente avisa
 o compilador que elas existem, pra poder usá-las em qualquer ordem no código.
*/
void exibirMenu();
void iniciarJogo(Pontuacao *historico, int *pTotalPontuacoes);
void exibirPontuacoes(const Pontuacao *historico, int totalPontuacoes);
void salvarPontuacao(char nome[], int pontos, long tempoGasto, bool silencioso, Pontuacao *historico, int *pTotalPontuacoes);
void limparTela();
void embaralhar(const char* arr[], int n);
void redesenharTela(char username[], int pontuacaoTotal, int rodadaAtual, int totalRodadas, int turnoAtual, int tentativasMaximas, long segundosCorridos, int tamanhoPalavra, LetraFeedback (*historico)[tamanhoPalavra], char palpiteAtual[], char mensagemErro[]);


int main() {
    SetConsoleOutputCP(65001);
    srand(time(NULL));
    
    /*
     O histórico de pontuações e o contador ficam aqui na 'main', e não como variáveis globais.
     É uma prática mais segura, pois evita que qualquer função os modifique acidentalmente.
     Para alterá-los, as funções precisarão receber um "ponteiro" para eles.
    */
    Pontuacao historicoPontuacoes[100];
    int totalPontuacoes = 0;
    int opcao;

    /*
     Este é o loop principal do menu. O jogo fica rodando aqui dentro
     até que o jogador escolha a opção 3 para sair.
    */
    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) { opcao = 0; }
        while (getchar() != '\n');
        switch (opcao) {
            case 1: iniciarJogo(historicoPontuacoes, &totalPontuacoes); break;
            case 2: exibirPontuacoes(historicoPontuacoes, totalPontuacoes); break;
            case 3: printf("\nObrigado por jogar! Saindo...\n"); break;
            default: printf("\nOpção inválida! Pressione Enter...\n"); getchar(); break;
        }
    } while (opcao != 3);
    return 0;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exibirMenu() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    limparTela();
    printf("==============================\n");
    printf("        JOGO TERMO\n");
    printf("==============================\n");
    printf("\n[1] Iniciar Jogo\n");
    printf("[2] Pontuações\n");
    printf("[3] Sair do Jogo\n");
    printf("\nEscolha uma opção: ");
}

/*
 Esta função embaralha o nosso banco de palavras usando o algoritmo de Fisher-Yates.
 A implementação usa ponteiros de uma forma mais "clássica" em C para percorrer e trocar os elementos do array.
*/
void embaralhar(const char* arr[], int n) {
    for (const char **p = arr + n - 1; p > arr; p--) {
        int j = rand() % (p - arr + 1);
        const char* temp = *p;
        *p = *(arr + j);
        *(arr + j) = temp;
    }
}

/*
 Esta é uma das funções mais importantes. Ela é responsável por desenhar TUDO que o jogador
 vê durante a partida. Recebe vários parâmetros porque precisa saber o estado completo
 do jogo (pontos, tempo, rodada, tentativas, histórico de palpites, etc.).
*/
void redesenharTela(char username[], int pontuacaoTotal, int rodadaAtual, int totalRodadas, int turnoAtual, int tentativasMaximas, long segundosCorridos, int tamanhoPalavra, LetraFeedback (*historico)[tamanhoPalavra], char palpiteAtual[], char mensagemErro[]) {
    limparTela();
    printf("================================================================================\n");
    printf(" Comandos: [1] Menu | [2] Pausar | [3] Reiniciar Rodada\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(" Jogador: %s | Pontos: %-6d | Rodada: %d/%d | Tentativas: %d/%d | Tempo: %02ld:%02ld\n",
           username, pontuacaoTotal, rodadaAtual + 1, totalRodadas, turnoAtual + 1, tentativasMaximas, segundosCorridos / 60, segundosCorridos % 60);
    printf("================================================================================\n\n");

    for (int i = 0; i < turnoAtual; i++) {
        for (int j = 0; j < tamanhoPalavra; j++) {
            char letra = historico[i][j].letra;
            int status = historico[i][j].statusCor;
            const char* cor;
            if (status == STATUS_VERDE) cor = COR_VERDE; else if (status == STATUS_AMARELO) cor = COR_AMARELO; else cor = COR_VERMELHO;
            printf("%s %c %s ", cor, letra, COR_RESET);
        }
        printf("\n\n");
    }

    if (strlen(mensagemErro) > 0) {
        printf(COR_AMARELO "Aviso: %s" COR_RESET "\n\n", mensagemErro);
    }
    
    printf("Digite seu palpite de %d letras: %s", tamanhoPalavra, palpiteAtual);
}


void iniciarJogo(Pontuacao *historico, int *pTotalPontuacoes) {
    char username[50];
    limparTela();
    printf("Digite seu nome de usuário: ");
    scanf("%49s", username);
    while (getchar() != '\n');

    const int totalRodadas = 14;
    int pontuacaoTotal = 0;
    time_t tempoInicioGeral = time(NULL);
    long tempoPausadoTotal = 0;

    /*
     É uma boa prática copiar os bancos de palavras para arrays locais da partida.
     Assim, podemos embaralhar a cópia sem bagunçar o array original, que é 'const'.
    */
    const char* palavrasFaceisPartida[tamBancoFacil];
    const char* palavrasMediasPartida[tamBancoMedio];
    const char* palavrasDificeisPartida[tamBancoDificil];
    for(int i=0; i<tamBancoFacil; i++) palavrasFaceisPartida[i] = bancoFacil[i];
    for(int i=0; i<tamBancoMedio; i++) palavrasMediasPartida[i] = bancoMedio[i];
    for(int i=0; i<tamBancoDificil; i++) palavrasDificeisPartida[i] = bancoDificil[i];
    embaralhar(palavrasFaceisPartida, tamBancoFacil);
    embaralhar(palavrasMediasPartida, tamBancoMedio);
    embaralhar(palavrasDificeisPartida, tamBancoDificil);
    int indiceFacil = 0, indiceMedio = 0, indiceDificil = 0;

    for (int rodadaAtual = 0; rodadaAtual < totalRodadas; rodadaAtual++) {
        bool querReiniciarRodada = false;
        do {
            querReiniciarRodada = false;
            
            int pontuacaoAntesDaRodada = pontuacaoTotal;
            
            const char* palavraSecreta;
            int tentativasMaximas;
            enum Dificuldade dificuldadeAtual;
            if (rodadaAtual < 7) { dificuldadeAtual = FACIL; tentativasMaximas = 8; palavraSecreta = palavrasFaceisPartida[indiceFacil]; } 
            else if (rodadaAtual < 11) { dificuldadeAtual = MEDIO; tentativasMaximas = 6; palavraSecreta = palavrasMediasPartida[indiceMedio]; } 
            else { dificuldadeAtual = DIFICIL; tentativasMaximas = 4; palavraSecreta = palavrasDificeisPartida[indiceDificil]; }
            int tamanhoPalavra = strlen(palavraSecreta);
            
            bool letrasJaPontuaram[tamanhoPalavra];
            for(int i=0; i<tamanhoPalavra; i++) letrasJaPontuaram[i] = false;

            /*
              ALOCAÇÃO DINÂMICA: Como o tamanho da palavra e o número de tentativas mudam,
              não podemos criar um array de histórico com tamanho fixo. Usamos 'malloc'
              para alocar a memória para o nosso "tabuleiro" dinamicamente, na hora.
            */
            LetraFeedback (*historicoJogadas)[tamanhoPalavra] = malloc(tentativasMaximas * sizeof(*historicoJogadas));
            if (historicoJogadas == NULL) { printf("Erro de alocação de memória!"); return; }

            int turnoAtual = 0;
            char mensagemErro[100] = "";
            for(int i=0; i<tentativasMaximas; i++) for(int j=0; j<tamanhoPalavra; j++) historicoJogadas[i][j].statusCor = STATUS_VAZIO;
            
            bool vitoriaNaRodada = false;
            while (turnoAtual < tentativasMaximas) {
                char palpite[20] = "";
                int palpiteLen = 0;
                time_t ultimoUpdate = 0;
                bool turnoAcabou = false;

                /*
                  LOOP DE ENTRADA EM TEMPO REAL: Em vez de usar um 'scanf' que para tudo, ficamos neste loop.
                  '_kbhit()' checa se alguma tecla foi pressionada, mas não para o programa. Se foi,
                  usamos '_getch()' para pegar a tecla. Isso permite que o cronômetro continue
                  rodando no fundo enquanto o jogador digita. O 'Sleep(50)' dá uma pequena
                  pausa para não sobrecarregar a CPU.
                */
                while (!turnoAcabou) {
                    bool precisaRedesenhar = false;
                    long segundosCorridos = (time(NULL) - tempoInicioGeral) - tempoPausadoTotal;

                    if (time(NULL) > ultimoUpdate) {
                        ultimoUpdate = time(NULL);
                        precisaRedesenhar = true;
                    }

                    if (_kbhit()) {
                        precisaRedesenhar = true;
                        char ch = _getch();

                        if (ch == 13) {
                            if ((strlen(palpite) == tamanhoPalavra) || (palpiteLen > 0 && (strcmp(palpite, "1")==0 || strcmp(palpite, "2")==0 || strcmp(palpite, "3")==0))) {
                                turnoAcabou = true;
                            } else {
                                strcpy(mensagemErro, "Palavra de tamanho incorreto!");
                            }
                        } else if (ch == 8) {
                            if (palpiteLen > 0) { palpiteLen--; palpite[palpiteLen] = '\0'; }
                        } else if (palpiteLen < 19 && isprint(ch)) {
                            palpite[palpiteLen++] = toupper(ch);
                            palpite[palpiteLen] = '\0';
                        }
                    }

                    if (precisaRedesenhar) {
                        redesenharTela(username, pontuacaoTotal, rodadaAtual, totalRodadas, turnoAtual, tentativasMaximas, segundosCorridos, tamanhoPalavra, historicoJogadas, palpite, mensagemErro);
                        if (strlen(mensagemErro) > 0) strcpy(mensagemErro, "");
                    }
                    Sleep(50);
                }
                
                if (strcmp(palpite, "1") == 0) { free(historicoJogadas); return; }
                if (strcmp(palpite, "3") == 0) {
                    if (turnoAtual + 1 == tentativasMaximas) { strcpy(mensagemErro, "Não é possível reiniciar na última tentativa!"); continue; }
                    
                    pontuacaoTotal = pontuacaoAntesDaRodada;

                    if(dificuldadeAtual == FACIL) indiceFacil++; else if (dificuldadeAtual == MEDIO) indiceMedio++; else indiceDificil++;
                    querReiniciarRodada = true; 
                    break;
                }
                if (strcmp(palpite, "2") == 0) {
                    time_t inicioPausa = time(NULL); limparTela(); printf("\n\n\n    JOGO PAUSADO\n\n    Pressione 'P' para continuar...");
                    while(true) { char c = getchar(); if (c == 'p' || c == 'P') break; }
                    tempoPausadoTotal += time(NULL) - inicioPausa; continue;
                }
                
                char tempSecreta[tamanhoPalavra + 1]; strcpy(tempSecreta, palavraSecreta);
                int statusLetras[tamanhoPalavra];

                for(int i=0; i<tamanhoPalavra; i++) {
                    if(palpite[i] == tempSecreta[i]) {
                        statusLetras[i] = STATUS_VERDE;
                        if (!letrasJaPontuaram[i]) { pontuacaoTotal += (50 * tentativasMaximas) - (50 * turnoAtual); letrasJaPontuaram[i] = true; }
                        tempSecreta[i] = '*';
                    } else { statusLetras[i] = STATUS_VERMELHO; }
                }
                for(int i=0; i<tamanhoPalavra; i++) {
                    if (statusLetras[i] == STATUS_VERDE) continue;
                    for (int j=0; j<tamanhoPalavra; j++) {
                        if (palpite[i] == tempSecreta[j]) {
                            statusLetras[i] = STATUS_AMARELO;
                            if (!letrasJaPontuaram[j]) { pontuacaoTotal += (20 * tentativasMaximas) - (20 * turnoAtual); letrasJaPontuaram[j] = true; }
                            tempSecreta[j] = '*'; break;
                        }
                    }
                }
                
                int acertou = 1;
                for(int i=0; i<tamanhoPalavra; i++) {
                    historicoJogadas[turnoAtual][i].letra = palpite[i];
                    historicoJogadas[turnoAtual][i].statusCor = statusLetras[i];
                    if(statusLetras[i] != STATUS_VERDE) acertou = 0;
                }

                if (acertou) { 
                    pontuacaoTotal += (100 * tentativasMaximas) - (100 * turnoAtual);
                    vitoriaNaRodada = true; 
                    break; 
                }
                turnoAtual++;
            }

            /*
              Antes de sair da função ou de terminar a rodada, é CRUCIAL liberar a memória
              que alocamos com o malloc usando 'free()'. Se não fizermos isso,
              essa memória fica "presa" e o programa começa a consumir recursos desnecessariamente,
              o que a gente chama de "vazamento de memória" (memory leak).
            */
            free(historicoJogadas);

            if (!querReiniciarRodada) {
                if (vitoriaNaRodada) {
                    if(dificuldadeAtual == FACIL) indiceFacil++; else if (dificuldadeAtual == MEDIO) indiceMedio++; else indiceDificil++;
                    
                    long segundosCorridos = (time(NULL) - tempoInicioGeral) - tempoPausadoTotal;
                    redesenharTela(username, pontuacaoTotal, rodadaAtual, totalRodadas, turnoAtual+1, tentativasMaximas, segundosCorridos, tamanhoPalavra, historicoJogadas, "VITORIA!", "");
                    printf(COR_VERDE "\nParabéns, você passou da rodada %d!" COR_RESET, rodadaAtual + 1);
                    printf("\nPontuação total: %d\n\n", pontuacaoTotal);

                    if (rodadaAtual < totalRodadas - 1) {
                        char escolha;
                        printf("Deseja continuar para a próxima rodada? [S] Sim [N] Não: ");
                        while (scanf(" %c", &escolha) != 1 || (toupper(escolha) != 'S' && toupper(escolha) != 'N')) {
                            while(getchar() != '\n'); printf("Opção inválida. Deseja continuar? [S] Sim [N] Não: ");
                        }
                        if (toupper(escolha) == 'N') { 
                            salvarPontuacao(username, pontuacaoTotal, (time(NULL) - tempoInicioGeral) - tempoPausadoTotal, true, historico, pTotalPontuacoes); 
                            return; 
                        }
                    }
                } else {
                    limparTela();
                    printf("\n\nFIM DE JOGO!\nVocê não conseguiu adivinhar a palavra '%s' na rodada %d.\n", palavraSecreta, rodadaAtual + 1);
                    printf("Pontuação final: %d\n", pontuacaoTotal);
                    salvarPontuacao(username, pontuacaoTotal, (time(NULL) - tempoInicioGeral) - tempoPausadoTotal, false, historico, pTotalPontuacoes);
                    printf("\nPressione Enter para voltar ao menu..."); getchar(); return;
                }
            }
        } while (querReiniciarRodada);
    }

    limparTela();
    printf(COR_VERDE "\n\nPARABÉNS, %s! VOCÊ VENCEU O JOGO!\n" COR_RESET, username);
    printf("Você completou todas as %d rodadas!\n", totalRodadas);
    printf("Pontuação final: %d\n", pontuacaoTotal);
    salvarPontuacao(username, pontuacaoTotal, (time(NULL) - tempoInicioGeral) - tempoPausadoTotal, false, historico, pTotalPontuacoes);
    printf("\nPressione Enter para voltar ao menu..."); getchar();
}

/*
 Esta função salva o resultado no histórico. Ela recebe um ponteiro para o contador
 'totalPontuacoes' que está na 'main'. Usando '*pTotalPontuacoes', conseguimos modificar
 o valor original da variável, e não apenas uma cópia.
*/
void salvarPontuacao(char nome[], int pontos, long tempoGasto, bool silencioso, Pontuacao *historico, int *pTotalPontuacoes) {
    if (*pTotalPontuacoes < 100) {
        strcpy(historico[*pTotalPontuacoes].username, nome);
        historico[*pTotalPontuacoes].pontuacao = pontos;
        historico[*pTotalPontuacoes].tempo = tempoGasto;
        (*pTotalPontuacoes)++;
        if (!silencioso) { printf("Seu resultado foi salvo no histórico!\n"); }
    }
}

void exibirPontuacoes(const Pontuacao *historico, int totalPontuacoes) {
    limparTela();
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    printf("==================================================\n");
    printf("                      PONTUAÇÕES\n");
    printf("==================================================\n");
    if (totalPontuacoes == 0) { printf("\nNenhuma pontuação registrada ainda.\n"); } 
    else {
        printf("\n%-20s %-10s %-10s\n", "JOGADOR", "PONTOS", "TEMPO(s)");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < totalPontuacoes; i++) {
            printf("%-20s %-10d %-10ld\n", 
                   historico[i].username, 
                   historico[i].pontuacao, 
                   historico[i].tempo);
        }
    }
    printf("\n\nPressione Enter para voltar ao menu...");
    getchar();
}