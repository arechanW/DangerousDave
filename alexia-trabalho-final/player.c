#include "player.h"
#include <stdbool.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "constantes.h"

//Imprimir Dave ao longo do jogo
void imprimir(player_t a) {
    clear();
    box(stdscr, 0, 0);
    mvprintw(a.y, a.x, "D");
    refresh();
}

//Movimentacao sem jetpack
void andar(player_t *player, mapa_t *mapa){
    player->v_x=0;
    //Obstaculos na horizontal
    if (mapa->m[player->y][player->x + player->input_x] != parede) {
        player->v_x = player->input_x * VELOCIDADE_H;
    }

    //Movimento horizontal
    player->x = player->x + player->v_x;

    //Retorna se o player estava no chao
    bool estava_no_chao = player->no_chao;

    //Testar se o player esta no chao no momento
    player->no_chao = mapa->m[player->y + 1][player->x] == parede;
    if(player->no_chao){
        //Zerar velocidade vertical 
        if (player->v_y > 0) {
            player->v_y = 0;
        }
    }else{
        //Se estiver pulando
        if(player->jump_frames > 0){
            player->v_y = -1;
            player->jump_frames--;
        //Cair
        } else {
            player->v_y = 1;
        }
    }

    //Condicao para pular
    if (player->no_chao || estava_no_chao) {
        //Se QUER pular
        if (player->input_y == -1) {
            player->jump_frames = FPULO;
            player->v_y = -1;
        }
    }

    //Parede em cima
    if (mapa->m[player->y - 1][player->x] == parede) {
        player->jump_frames = 0;
        if (player->v_y < 0) {
            player->v_y = 0;
        }
    }

    //Movimento vertical
    player->y = player->y + player->v_y;
    player->input_y=0;
}

//Movimentacao com jetpack
void voar(player_t *player, mapa_t *mapa){
    player->v_x=0;
    player->v_y=0;
    //Obstaculos na horizontal
    if (mapa->m[player->y][player->x + player->input_x] != parede) {
        player->v_x = player->input_x * VELOCIDADE_H;
    }

    //Movimento horizontal
    player->x = player->x + player->v_x;

    //Obstaculos na vertical
    if (mapa->m[player->y + player->input_y][player->x] != parede) {
        player->v_y = player->input_y * VELOCIDADE_H;
    }

    //Movimento vertical
    player->y = player->y + player->v_y;

    
}

//Movimentar dentro das condicoes anteriores
void update_player(player_t *player, mapa_t *mapa) {
    if(player->tem_jetpack && player->ativar_jetpack){
        player->jump_frames = 0;
        player->no_chao = false;
        voar(player, mapa);
    }else{
        andar(player, mapa);
    }
}

//Desenhar Dave
void draw_player(player_t *player) {
    attron(COLOR_PAIR(c_dave));
    mvprintw(player->y + OFF_I, player->x + OFF_J, "%c", dave);
}

//Itens do mapa somem apos coletados
void checar_itens(player_t *player, mapa_t *mapa, int *score) {
    switch (mapa->m[player->y][player->x]) {
        case jetpack:
            mapa->m[player->y][player->x] = ' ';
            player->tem_jetpack = true;
            break;
        case rubi:
            mapa->m[player->y][player->x] = ' ';
            *score += 150;
            break;
        case safira:
            mapa->m[player->y][player->x] = ' ';
            *score += 100;
            break;
        case ametista:
            mapa->m[player->y][player->x] = ' ';
            *score += 50;
            break;
        case anel:
            mapa->m[player->y][player->x] = ' ';
            *score += 200;
            break;
        case coroa:
            mapa->m[player->y][player->x] = ' ';
            *score += 300;
            break;
        case trofeu:
            mapa->m[player->y][player->x] = ' ';
            *score += 1000;
            player->tem_trofeu = true;
            break;
    }
}

//Encostar na agua ou fogo
bool jogador_morreu(player_t *player, mapa_t *mapa) {
    switch (mapa->m[player->y][player->x]) {
        case fogo:
            player->jump_frames = 0;
            player->x = mapa->player_spawn_x;
            player->y = mapa->player_spawn_y;
            player->v_x = 0;
            player->v_y = 0;
            player->input_x = 0;
            player->input_y = 0;
            player->no_chao = false;
            return true;
            break;
        case agua:
            player->jump_frames = 0;
            player->x = mapa->player_spawn_x;
            player->y = mapa->player_spawn_y;
            player->v_x = 0;
            player->v_y = 0;
            player->input_x = 0;
            player->input_y = 0;
            player->no_chao = false;
            return true;
            break;
        default:
            return false;
            break;
    }
}

//Retorna se pode ou nao passar de fase
bool passar_fase(player_t *player, mapa_t *mapa){
    if(player->tem_trofeu && (mapa->m[player->y][player->x] == porta)){
        return true;
    }else{
        return false;
    }
}

