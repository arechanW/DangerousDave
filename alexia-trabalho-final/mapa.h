#ifndef _MAPA_H
#define _MAPA_H 
#include "constantes.h"
#include <stdio.h>

typedef struct mapa{
    char m[MAPA_L][MAPA_C + 2];             //recebe o mapa importado do arquivo .txt
    int size_x, size_y;                     //tamanho do mapa caso nao seja maximo
    int player_spawn_x, player_spawn_y;     //coordenadas do local de entrada do personagem
}mapa_t;

void ler_mapa(mapa_t *mapa, int *nivel);
void definir_cores();
void colorir(mapa_t *mapa);

#endif