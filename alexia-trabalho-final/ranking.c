#include "ranking.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Ler e importar dados do arquivo binario
void le_arquivo(ranking_t ranking[TAM]) {
    FILE *arquivo = fopen(FPESSOAS, "r");
    if (arquivo == NULL) {
        for (int i = 0; i < TAM; i++) {
            ranking[i].nome[0] = '-';
            ranking[i].nome[1] = '\0';
            ranking[i].score = 0;
        }
    } else {
        fread(ranking, sizeof(ranking_t), TAM, arquivo);
    }

    fclose(arquivo);
}

//Receber nome do jogador
void ler_nome(ranking_t *novo_ranking, int *score) {
    int x = getmaxx(stdscr);
    int mid = x/2;

    clear();
    mvprintw(16, mid-16, "Digite seu nome: ");
    refresh();
    echo();
    nocbreak();
    curs_set(1);
    fflush(stdin);
    nodelay(stdscr, FALSE);
    scanw("%s", novo_ranking->nome);
    nodelay(stdscr, TRUE);
    curs_set(0);
    noecho();
    cbreak();
    novo_ranking->score = *score;
}

//Ordenar ranking
void ordena(ranking_t *ranking) {
    int sinal, fim;
    ranking_t aux;
    fim = TAM - 1;
    do {
        sinal = 0;
        for (int i = 0; i < fim; i++) {
            if ((ranking + i)->score < (ranking + i + 1)->score) {
                aux = *(ranking + i);
                *(ranking + i) = *(ranking + i + 1);
                *(ranking + i + 1) = aux;
                sinal = 1;
            }
        }
        fim--;
    } while (sinal == 1);
}

//Atualizar arquivo binario
void salva_arquivo(ranking_t ranking[TAM]) {
    FILE *arquivo = fopen(FPESSOAS, "w");
    if (arquivo) {
        fwrite(ranking, sizeof(ranking_t), TAM, arquivo);
    } else {
        printf("Nao foi possivel abrir o arquivo.\n");
    }
    fclose(arquivo);
}

//Incluir jogador no ranking
void add_ranking(ranking_t ranking[TAM], ranking_t novo_ranking) {
    ranking[TAM - 1] = novo_ranking;
    ordena(ranking);
    salva_arquivo(ranking);
}

//Imprimir ranking na tela
void escreve_ranking(ranking_t ranking[TAM]) {
    int x = getmaxx(stdscr);
    int mid = x/2;

    mvprintw(12, mid-5, "*** TOP 5 ***");
    for (int i = 0; i < TAM-1; i++) {
        mvprintw(16+i, mid-41, "%40s     %.6d\n", ranking[i].nome, ranking[i].score);
    }
    refresh();
    sleep(5);
}