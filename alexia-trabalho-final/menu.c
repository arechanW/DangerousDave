#include "menu.h"
#include "ranking.h"
#include "salvar.h"
#include "player.h"
#include "mapa.h"
#include <stdio.h>

//Imprime menu inicial
bool imprimir_menu(int* destaque, int* tecla){
    printw("\n\n\n\n\n\n");
	printw("\t\t\t\t\t\t\t%s \n\n",  *destaque == 0 ? "> NOVO JOGO <" : "  Novo Jogo");
	printw("\t\t\t\t\t\t\t%s \n\n", *destaque == 1 ? "> CONTINUAR <" : "  Continuar");
	printw("\t\t\t\t\t\t\t %s \n\n", *destaque == 2 ? "> RANKING <" : "  Ranking");
    printw("\t\t\t\t\t\t\t  %s \n\n", *destaque == 3 ? "> SAIR <" : "  Sair");

    //Destacar opcao escolhida
    *tecla = getch();
    if (*tecla == KEY_UP){
        *destaque -= 1;
    }else if (*tecla == KEY_DOWN){
         *destaque += 1;
    }

    //Loop
    if (*destaque > 3){
        *destaque = 0;
    }else if (*destaque < 0){
        *destaque = 3;
    }

    //Escolher opcao ao pressionar enter
    return (*tecla == 10); 
}

//Exibe o nome do jogo
void printar_logo(int cor, int tamanho, char* lista){
    for(int i=0; i<tamanho; i++){
        attron(COLOR_PAIR(cor));
	    printw("%c", *lista);
        lista++;
        attroff(COLOR_PAIR(cor));
    }
}