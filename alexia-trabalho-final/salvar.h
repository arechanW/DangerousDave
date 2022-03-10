#ifndef _SALVAR_H
#define _SALVAR_H 
#include "mapa.h"
#include "player.h"

void salvar_dados(mapa_t *mapa, player_t *player, int *score, int *vida, int *nivel);
bool carregar_dados(mapa_t *mapa, player_t *player, int *score, int *vida, int *nivel);

#endif