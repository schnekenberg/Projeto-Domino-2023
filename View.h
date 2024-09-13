/*
DOM_View.h
DOM - Projeto Domino
2023
*/

void funcMostraDomino();
int menugeral();
void apresentaPedra(int jvez); //mostra as pedras de determinado jogador
int submenuV(); //exibe na tela as opoees do submenuC e capta a opcao escolhida
char escolhePedra(); //capta a opcaoo de pedra que o usuario escolher
char escolheLado(); //capta a opcao de pedra que o usuario escolher
void apresentaMensagem(char mens[100]); //apresenta uma determinada mensagem na tela
void flush_in(); //limpa o buffer de entrada
void mostraRegras(); //mostra as regras
void mostraUltimaPedra(); //mostra a ultima pedra que foi colocada na mesa
