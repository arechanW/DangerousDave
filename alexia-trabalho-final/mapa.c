#include "mapa.h"
#include "constantes.h"
#include <ncurses.h>

//Ler mapa do arquivo txt
void ler_mapa(mapa_t *mapa, int *nivel){
    int i=0, j=0;
    char lido;
    FILE *arquivo;

    //Escolher o arquivo para ler
    switch(*nivel){
        case 1:
            arquivo = fopen(MAPA_01, "r");
        break;
        case 2:
            arquivo = fopen(MAPA_02, "r");
        break;
        case 3:
            arquivo = fopen(MAPA_03, "r");
        break;
    }
    
    //Importando o mapa para os atributos do player
    if(arquivo == NULL){
        printf("Nao foi possivel abrir o arquivo.\n");
    }else{
        lido = fgetc(arquivo);
        while(lido != EOF){
            if(lido != '\n'){
                mapa->m[i][j] = lido;
                if(lido == dave){
                    mapa->m[i][j] = ' ';
                    mapa->player_spawn_x = j;
                    mapa->player_spawn_y = i;
                }
                j++;
            }else if(lido == '\n'){
                i++;
                mapa->size_x = j;
                j = 0;
            }
            lido = fgetc(arquivo);
        }
        mapa->size_y = i+1;
    }
    
    fclose(arquivo);
}

//Imprimir de acordo com os pares de cores setados na main
void colorir(mapa_t *mapa){
    for (int i = 0; i < mapa->size_y; i++) {
        for (int j = 0; j < mapa->size_x; j++) {
            switch(mapa->m[i][j]){
                case dave:
                    attron(COLOR_PAIR(c_dave));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                case entrada:
                    attron(COLOR_PAIR(c_entrada));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);    
                break;
                case parede:
                    attron(COLOR_PAIR(c_parede));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);   
                break;
                case porta:
                    attron(COLOR_PAIR(c_porta));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);       
                break;
                case fogo:
                    attron(COLOR_PAIR(c_fogo));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);    
                break;
                case agua:
                    attron(COLOR_PAIR(c_agua));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]); 
                break;
                case jetpack:
                    attron(COLOR_PAIR(c_jetpack));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]); 
                break;
                case rubi:
                    attron(COLOR_PAIR(c_rubi));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                case safira:
                    attron(COLOR_PAIR(c_safira));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                case ametista:
                    attron(COLOR_PAIR(c_ametista));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                case anel:
                    attron(COLOR_PAIR(amarelo));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                case coroa:
                    attron(COLOR_PAIR(amarelo));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                case trofeu:
                    attron(COLOR_PAIR(amarelo));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
                default:
                    attroff(COLOR_PAIR(c_dave));
                    mvprintw(i+OFF_I, j+OFF_J, "%c", mapa->m[i][j]);
                break;
            }
        }
    }            
}