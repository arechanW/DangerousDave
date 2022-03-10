#ifndef _PLAYER_H
#define _PLAYER_H 
#include "mapa.h"
#include <stdbool.h>

typedef struct player{
    //Coordenadas da intencao do jogador, posicao e velocidade/ frames
    int input_x, input_y, x, y, v_x, v_y, jump_frames;
    bool no_chao, tem_trofeu, tem_jetpack, ativar_jetpack;
}player_t;

void imprimir(player_t a);
void update_player(player_t* player, mapa_t *mapa);
void draw_player(player_t *player);
void checar_itens(player_t *player, mapa_t *mapa, int *score);
bool jogador_morreu(player_t *player, mapa_t *mapa);
bool passar_fase(player_t *player, mapa_t *mapa);

#endif