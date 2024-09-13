/*
DOM_View.cpp
DOM - Projeto Domino
2023
*/

#include <stdio.h>
#include "Dom_View.h"
#include <ctype.h>

int menugeral(){ //o menu que esta sendo executado
	int m;
	printf("\nEscolha uma opcao do menu: \n");
    printf("\nMENU DE OPCOES: \n");
    printf("1. Iniciar jogo (2 jogadores)\n");
	printf("2. Iniciar jogo (contra o computador)\n");
    printf("3. Retornar ao jogo interrompido\n");
    printf("4. Regras gerais do jogo\n");
    printf("5. Salvar o jogo\n");
    printf("6. Recuperar o jogo\n");
    printf("0. Sair\n");
    printf("Resposta: ");
    scanf("%d", &m);
	return m;
	
}

int submenuV(){
	int m;
	flush_in();
    printf("\n1. Jogar \n");
    printf("2. Comprar \n");
    printf("3. Passar \n");
    printf("4. Sair\n");
    printf("Resposta: ");
    scanf ("%d", &m);
    return m;
}

void flush_in() //limpa o buffer
 {
 int ch;
 while( (ch = fgetc(stdin)) != EOF && ch != '\n');
}

char escolhePedra(){ //qual pedra ele quer usar
	char p, op;
	flush_in();
    printf("\nJogador %d: escolha a pedra para jogar (0 para desistir): ", jvez);
    scanf("%c", &p);
    op =  tolower (p);
    return op;
}

char escolheLado(){ //qual lado ele escolhe
	char q, oq;
	flush_in();
	printf("\nEscolha o lado da mesa da Mesa: Esquerdo/Direito (E/D): ");
    scanf ("%c", &q);
    oq = tolower(q);
    return oq;
}

void funcMostraDomino(){ //mostra as pedras
    int i, j, k = 0;
    int L1, L2;
    printf("\n");
    for (i = 0; i <= 6; i++)
	{
        for (j = i; j <= 6; j++) 
		{
            printf("[%d|%d]\t", dom[k].L1, dom[k].L2);
            k++;
        }
        printf("\n");
    }
}

void apresentaPedra(int jvez){
	int i, j=0;
    printf ("Jogador %d  ", jvez);
	for (i=0; i<=27; i++){
		if (dom[i].status == jvez){
            printf ("%c.[%d|%d]  ", alfabeto[j], dom[i].L1, dom[i].L2);
            j++;
        }
			
	}
}

void apresentaMensagem(char mens[100]){
	printf("%s", mens);
}

void mostraMesa(){
int i;
printf ("\n=========\n");
printf ("M E S A: ");
for (i= 0; i < qtmesa; i++){
		printf ("[%d|%d]\t", mesa[i].ladoE, mesa[i].ladoD);
	}
printf ("\n=========\n");
}

void mostraRegras(){
    printf("\nREGRAS DO JOGO:\n\n");
    printf("\n1. Cada jogador recebe 7 pedras quando comeca a rodada, e as pedras restantes ficam no monte para serem compradas.\n");
    printf("\n2. O jogo comeca pelo jogador que tiver a pedra de de dois numeros iguais de maior valor, e no caso de nenhum jogador\n");
    printf("ter alguma dessas pedras em sua mao, comecara o jogador que tiver a pedra com a maior soma de seus valores.\n");
    printf("\n3. Cada jogador, no seu turno, obrigatoriamente, devera colocar uma de suas pedras na extremidade da mesa que tiver\n");
    printf("o numero igual o da extremidade da pedra, de modo que os numeros iguais coincidam. A unica excecao esta na regra 4.\n");
    printf("\n4. Se um jogador nao puder jogar, devera comprar do monte uma pedra e utiliza-la, se possivel. Os jogadores podem comprar\n");
    printf("quantas pedras quiserem em sua vez. Se nao houver pedras no monte, o jogador perde a vez e o turno passara para o jogador\n");
    printf("seguinte.\n");
    printf("\n5. Perdera o jogador que tiver mais pedras em sua mao no final da partida. Em caso de empate, perdera aquele que tiver\n");
    printf("a maior soma dos valores das pedras.\n");
}

void mostraUltimaPedra(){
    printf ("[%d|%d]\n\n", last_L1, last_L2);
}
