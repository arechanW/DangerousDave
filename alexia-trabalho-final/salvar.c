#include "constantes.h"
#include "salvar.h"
#include <stdbool.h>

//Salvar dados em arquivo binario
void salvar_dados(mapa_t *mapa, player_t *player, int *score, int *vida, int *nivel){
    FILE *arquivo = fopen(FMAPA, "wb");
    if (arquivo == NULL) {
        return;
    } else {
        fwrite(score, sizeof(int), 1, arquivo);
        fwrite(vida, sizeof(int), 1, arquivo);
        fwrite(nivel, sizeof(int), 1, arquivo);
        fwrite(mapa, sizeof(mapa_t), 1, arquivo);
        fwrite(player, sizeof(player_t), 1, arquivo);
    }

    fclose(arquivo);
}

//Ler dados de jogo salvo do arquivo binario
bool carregar_dados(mapa_t *mapa, player_t *player, int *score, int *vida, int *nivel){
    FILE *arquivo = fopen(FMAPA, "rb");
    if (arquivo == NULL) {
        return false;
    } else {
        fread(score, sizeof(int), 1, arquivo);
        fread(vida, sizeof(int), 1, arquivo);
        fread(nivel, sizeof(int), 1, arquivo);
        fread(mapa, sizeof(mapa_t), 1, arquivo);
        fread(player, sizeof(player_t), 1, arquivo);
    }

    fclose(arquivo);
    return true;
}