#ifndef _RANKING_H
#define _RANKING_H 
#include "constantes.h"

typedef struct ranking{
    char nome[40];
    int score;
}ranking_t;

void le_arquivo(ranking_t ranking[TAM]);
void ler_nome(ranking_t *novo_ranking, int *score);
void ordena(ranking_t *ranking);
void salva_arquivo(ranking_t ranking[TAM]);
void add_ranking(ranking_t ranking[TAM], ranking_t novo_ranking);
void escreve_ranking(ranking_t ranking[TAM]);

#endif