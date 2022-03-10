//Modulos
#include <unistd.h>
#include "constantes.h"
#include "input.h"
#include "mapa.h"
#include "menu.h"
#include "player.h"
#include "ranking.h"
#include "salvar.h"

void definir_cores();

int main(){
    //Ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    definir_cores();

    //Variaveis
    mapa_t mapa;
    player_t player;
    ranking_t ranking[TAM], novo_ranking;
    int linha, coluna;
    int mid = getmaxx(stdscr) / 2;
    int aux = 0, destaque = 0, tecla = 0, score = 0, nivel = 1, vida = 5;
    bool iniciar = false, lose = false, next = false, win = false, sair = false, retornar=false, salvar=false, novo=false;
    char menu_logo[900] = {
        "\n\n\n\n\n\td8888b.  .d8b.  d8b   db  d888b  d88888b d8888b.  .d88b.  db    "
        "db .d8888.     d8888b.  .d8b.  db    db d88888b\n\t88  `8D d8' `8b 888o "
        " 88 88' Y8b 88'     88  `8D .8P  Y8. 88    88 88'  YP     88  `8D d8' "
        "`8b 88    88 88'    \n\t88   88 88ooo88 88V8o 88 88      88ooooo "
        "88oobY' 88    88 88    88 `8bo.       88   88 88ooo88 Y8    8P "
        "88ooooo\n\t88   88 88~~~88 88 V8o88 88  ooo 88~~~~~ 88`8b   88    88 88 "
        "   88   `Y8b.     88   88 88~~~88 `8b  d8' 88~~~~~\n\t88  .8D 88   88 "
        "88  V888 88. ~8~ 88.     88 `88. `8b  d8' 88b  d88 db   8D     88  "
        ".8D 88   88  `8bd8'  88.    \n\tY8888D' YP   YP VP   V8P  Y888P  "
        "Y88888P 88   YD  `Y88P'  ~Y8888P' `8888Y'     Y8888D' YP   YP    YP   "
        " Y88888P"};

    //Receber mapa
    ler_mapa(&mapa, &nivel);

    //Setar atributos do player
    player.jump_frames = 0;
    player.x = mapa.player_spawn_x;
    player.y = mapa.player_spawn_y;
    player.v_x = 0;
    player.v_y = 0;
    player.input_x = 0;
    player.input_y = 0;
    player.no_chao = false;
    player.tem_jetpack = false;
    player.tem_trofeu = false;

    //Inicializar
    while(!lose && !win && !sair){
        //Menu
        if(iniciar == false && lose == false){
            do{
                mvprintw(0, 0, "");
                printar_logo(c_rubi, 900, menu_logo);
                //Prosseguir de acordo com a opcao escolhida
                if(imprimir_menu(&destaque, &tecla)){
                    switch (destaque) {
                        case 0:
                            iniciar = true;
                            break;
                        case 1:
                            if(carregar_dados(&mapa, &player, &score, &vida, &nivel)){
                                iniciar = true;
                            }else{
                                clear();
                                mvprintw(16, mid - 15, "Voce nao possui um jogo salvo!");
                                refresh();
                                sleep(3);
                            }
                            break;
                        case 2:
                            clear();
                            le_arquivo(ranking);
                            escreve_ranking(ranking);
                            break;
                        case 3:
                            iniciar = true;
                            sair = true;
                            break;
                    }
                }
                refresh();
                usleep(50000);
            } while (iniciar != true);
            clear();

        //Iniciar jogo
        } else if(iniciar == true && lose == false){
            ler_input(&player, &salvar, &novo, &retornar);
            update_player(&player, &mapa);
            checar_itens(&player, &mapa, &score);
            mvprintw(OFF_I - 1, OFF_J,
                     "SCORE: %.6d\t\tNIVEL: %.2d\t       DAVE: %.2d", score,
                     nivel, vida);
            colorir(&mapa);
            draw_player(&player);

            //Perder vida
            if (jogador_morreu(&player, &mapa)) {
                vida--;
                score -= 500;
                if (vida <= 0) {
                    lose = true;
                    break;
                }
            }

            //Salvar jogo
            if (salvar) {
                salvar_dados(&mapa, &player, &score, &vida, &nivel);
                clear();
                mvprintw(16, mid - 6, "Jogo salvo!");
                refresh();
                sleep(3);
            }

            //Retornar
            if(retornar){
                aux = 0;
                destaque = 0;
                tecla = 0;
                score = 0;
                nivel = 1;
                vida = 5;
                iniciar = false;
                lose = false;
                next = false;
                win = false;
                sair = false;
                retornar=false;
                salvar=false;
                novo=false;
                ler_mapa(&mapa, &nivel);
                player.jump_frames = 0;
                player.x = mapa.player_spawn_x;
                player.y = mapa.player_spawn_y;
                player.v_x = 0;
                player.v_y = 0;
                player.input_x = 0;
                player.input_y = 0;
                player.no_chao = false;
                player.tem_jetpack = false;
                player.tem_trofeu = false;
                continue;
            }

            //Novo jogo
            if(novo){
                nivel = 1;
                score = 0;
                vida = 5;
                ler_mapa(&mapa, &nivel);
                player.jump_frames = 0;
                player.x = mapa.player_spawn_x;
                player.y = mapa.player_spawn_y;
                player.v_x = 0;
                player.v_y = 0;
                player.input_x = 0;
                player.input_y = 0;
                player.no_chao = false;
                player.tem_jetpack = false;
                player.tem_trofeu = false;
            }

            //Passar de fase
            if(passar_fase(&player, &mapa)){
                clear();
                nivel++;
                if (nivel > VITORIA) {
                    win = true;
                    break;
                }else{
                    player.tem_trofeu = false;
                    player.tem_jetpack = false;
                    ler_mapa(&mapa, &nivel);
                    player.jump_frames = 0;
                    player.x = mapa.player_spawn_x;
                    player.y = mapa.player_spawn_y;
                    player.v_x = 0;
                    player.v_y = 0;
                    player.input_x = 0;
                    player.input_y = 0;
                    player.no_chao = false;
                }
            }

            refresh();
            usleep(100000);
        }
    }

    //Vitoria
    if(win){
        clear();
        int mid = getmaxx(stdscr) / 2;
        mvprintw(16, mid - 4, "YOU WIN.");
        refresh();
        sleep(3);
        le_arquivo(ranking);
        if (score > ranking[TAM - 2].score) {
            ler_nome(&novo_ranking, &score);
            add_ranking(ranking, novo_ranking);
        }
        clear();
        escreve_ranking(ranking);
    //Derrota
    }else if(lose){
        clear();
        mvprintw(16, mid - 4, "YOU LOSE.");
        refresh();
        sleep(3);
        le_arquivo(ranking);
        if (score > ranking[TAM - 2].score) {
            ler_nome(&novo_ranking, &score);
            add_ranking(ranking, novo_ranking);
        }
        clear();
        escreve_ranking(ranking);
    }

    getch();
    endwin();
}

//Setar pares de cores para cada caractere
void definir_cores() {
    init_pair(c_dave, COLOR_WHITE, COLOR_BLACK);
    init_pair(c_entrada, COLOR_WHITE, COLOR_WHITE);
    init_pair(c_parede, COLOR_RED, COLOR_BLACK);
    init_pair(c_porta, COLOR_GREEN, COLOR_GREEN);
    init_pair(c_fogo, COLOR_RED, COLOR_RED);
    init_pair(c_agua, COLOR_BLUE, COLOR_BLUE);
    init_pair(c_jetpack, COLOR_WHITE, COLOR_BLACK);
    init_pair(c_rubi, COLOR_RED, COLOR_BLACK);
    init_pair(c_safira, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(c_ametista, COLOR_CYAN, COLOR_BLACK);
    init_pair(amarelo, COLOR_YELLOW, COLOR_BLACK);
}