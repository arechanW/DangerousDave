#include "input.h"
#include <ncurses.h>
#include <string.h>

bool confirmar(char *mensagem);

void ler_input(player_t *player, bool *salvar, bool *novo, bool *retornar){
    int a;
    *salvar = false;
    *novo = false;

    //Captura a INTENCAO do jogador
    while ((a = getch()) != ERR) {
        if (a == KEY_RIGHT) {
            player->input_x += 1;
            player->input_x = (player->input_x > 0) ? 1 : player->input_x;
        } else if (a == KEY_LEFT) {
            player->input_x -= 1;
            player->input_x = (player->input_x < 0) ? -1 : player->input_x;
        } else if (a == KEY_UP) {
            player->input_y -= 1;
            player->input_y = (player->input_y < 0) ? -1 : player->input_y;
        } else if (a == KEY_DOWN) {
            player->input_y += 1;
            player->input_y = (player->input_y > 0) ? 1 : player->input_y;
        } else if (a == 'S' || a == 's'){
            *salvar = true;
        } else if (a == 'N' || a == 'n'){
            *novo = confirmar("Deseja comecar um novo jogo? Y/N");
        } else if (a == 'Q' || a == 'q'){
            *retornar = confirmar("Deseja retornar ao menu principal? Y/N");
        } else if (a == ' '){
            player->ativar_jetpack = !player->ativar_jetpack;
        }
    }
}

//Tela de confirmacao
bool confirmar(char *mensagem){
    //Obter tamanho do terminal
    int x = getmaxx(stdscr);
    int y = getmaxy(stdscr);

    clear();
    //Centralizando
    mvprintw(y/2, (x-strlen(mensagem))/2, "%s", mensagem);
    refresh();
    while(1){
        switch(getch()){
            case 'Y':
            case 'y':
                clear();
                return true;
            break;
            case 'N':
            case 'n':
                clear();
                return false;
            break;
        }
    }
}