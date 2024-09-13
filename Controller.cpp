/*
DOM_Controller.cpp
DOM - Projeto Domino
2023
*/

#include "Dom_Controller.h"
#include "Dom_View.cpp"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void executarMenu(){ //executa o menu de opcoes
while(1){
	
	playerAuto = 2;
	int op;
	op = menugeral();
	
	 switch(op){
            case 1: //iniciar novo jogo
				system("cls");
            	resetar();
				jogcomp = 0;
                iniciarJogo();
                Jogo();
                break;
			
            case 2: //iniciar jogo contra o computador
				system("cls");
				resetar();
				jogcomp = 1;
				apresentaMensagem ("\nO computador e' o jogador 2!\n");
				iniciarJogo();
                Jogo();
                break;

            case 3: //retornar ao jogo
        		Jogo();
        	   	break;
        	   
        	case 4: //mostrar regras do jogo
        	system ("cls");
        		mostraRegras();
        		break;
        	
        	case 5: //salvar jogo
        		gravaCadastro();
        		break;
        	
        	case 6: //iniciar jogo salvo
        		recuperarCadastro();
        		Jogo();
        		break;
        	
        	case 0: //sair
        		return;
        		 
        }
}
}

void IniciarPedras(){ //cria as pedras
int i, j, k = 0; //o i e o j sao os numeros de cada lado da pedra. o k e' uma variavel auxiliar de contagem da pedra
int m; //opcao escolhida no menu 
   	for (i = 0; i <= 6; i++)
		for (j = i; j <= 6; j++)
		{
			dom[k].L1 = i;
			dom[k].L2 = j;
			dom[k].status = 0; //coloca o status de todas as pedras como nao utilizadas (no monte)
			k++;
		}
}

void funcEmbaralhaPedras() //embaralha as pedras do domino
{ 
  int k_rand, i;
    tipoPedra aux;//variavel auxiliar
    srand(time(NULL)); //o randomizador usa como base o horario
    //troca de lugar a pedra de indice i com a pedra de indice k_rand
    for(i=0; i<=27; i++)
	{
        k_rand = rand()%28; //define um numero aleatorio menor que 28
        aux = dom[i];
        dom[i] = dom[k_rand];
        dom[k_rand] = aux;
    }
}

void iniciarJogo() // inicia o jogo: embaralha e distribui as pedras, e faz o primeiro lance automatico
{
	int i;
	funcEmbaralhaPedras();
		
	for (i=0; i<=6; i++)
		dom[i].status = 1;  //as 7 primeiras pedras sao designadas para o jogador 1
	
	for (i=7; i<=13; i++)
		dom[i].status = 2; //as 7 primeiras pedras sao designadas para o jogador 2

	primeiroLance();
}

void Jogo(){ //loop em que as rodadas acontecem
	while(1){

	int x = vencedor();
				
	if(jogar(jvez)== 4){
		apresentaMensagem("SAINDO DO JOGO...");
		break;
		}
	}
}

void trocaJogador(){ //realiza a troca de jogadores
	if (jvez == 1)
		jvez = 2;
	else
		jvez = 1;
}

void primeiroLance(){ //define o primeiro jogador e realiza o primeiro lance automaticamente
	int i, pj, dupla;
	pj = -1; //posicao da pedra encontrada
	dupla = -1;
	//pesquisa primeiramente entre as pedra com lado1 = lado2
	for(i = 0; i < 14; i++){
		if (dom[i].L1 == dom[i].L2)
		{
			if (dom[i].L1 > dupla)
			{
				dupla = dom[i].L1;
				pj = i;
			}
		}
}
	//se nao encontrou, escolhe a pedra com a maior soma
	if (pj == -1){
	dupla = 0;
	for(i = 0; i < 14; i++){
		if (dom[i].L1 + dom[i].L2 > dupla)
 		{
		dupla = dom[i].L1 + dom[i].L2;
		pj = i;
 		}
 	}
 }
 
	//descobre qual o jogador que jogou essa primeira pedra
	jvez = dom[pj].status;
	//carrega a mesa com a primeira peca na posicao 0 
	mesa[0].ladoE = dom[pj].L1;
	mesa[0].ladoD = dom[pj].L2;
	
	mesaE = dom[pj].L1;
	mesaD = dom[pj].L2;

	last_L1 = mesaE; //ultima pedra que foi jogada lado 1
	last_L2 = mesaD; //ultima pedra que foi jogada lado 2
	
	dom[pj].status = 9; //muda o status da pedra para 9 = "Mesa"
	qtmesa++;
	passou = 0;
	trocaJogador();

}

int jogar(int jvez){
	submenuC();
	return 4; //retornar quatro e' uma condicao para sair do loop na funcao Jogar
}

void submenuC(){
	int op;

		apresentaMensagem("\nO primeiro lance e' realizado automaticamente!\n");
		if (jvez == 1)
			apresentaMensagem("\nO primeiro a jogar foi o jogador 2!\n\n");
		else if (jvez == 2)
			apresentaMensagem("\nO primeiro a jogar foi o jogador 1!\n\n");

	while(op!=4 && win==0){	 //enquanto a opcao for diferente de 4 e ninguem tiver ganhado o jogo
	if(jogcomp==0 || (jogcomp==1 && jvez != playerAuto)){

	mostraMesa(); //continua se nao houver um vencedor
	if (jvez == 1){
		apresentaMensagem("\nO lance anterior foi do jogador 2\n");
	}
	else{
		apresentaMensagem("\nO lance anterior foi do jogador 1\n");
	}
	apresentaMensagem("\nA ultima pedra jogada foi:");
	mostraUltimaPedra();
	apresentaPedra(jvez);

	op = submenuV();


		switch(op){
            case 1: //realizar jogada
            	system ("cls");
            	mostraMesa();
            	apresentaPedra(jvez);
                executaJogada();
                break;
			
            case 2: //comprar pedra
            	system ("cls");
           		comprarPedra(jvez);
           		
                break;

        	case 3: //passar vez
        		system ("cls");
               	if(passarVez()){
				   	passou++; //se um jogador passar a vez, adiciona ao contador
				   	if(vencedor()){
				   		win = 1; //se um jogador ganhar, encerra o jogo
					   }
					if(win==0){ //se nenhum jogador tiver ganhado, a pedra e prossegue normalmente
						trocaJogador();
               		
					}
				}
				else{
					apresentaMensagem("\nDigite uma opcao valida! Voce nao pode passar essa jogada.\n");
				}
        	   	break;
		}
		}
		else{
			executaJogada();
		}
    }
}

void executaJogada(){ //descobre onde esta' a pedra que o jogador escolheu e executa a jogada
int i, j, k, u, r;
int qtmesaAntes = qtmesa; //quantidade de pedras na mesa antes de executar uma jogada
int x = 0;
int p_jogador = 0; 
char opcP, opcL; 
int lado;
int p_valida;
int jogadorInicioDaFuncao = jvez;
int q = 0;
int pedras_mao = 0;

	if ((jogcomp == 1) && (jvez == playerAuto)){ //esses dados apenas sao necessarios para que seja executado o if abaixo, e tem sua importancia apenas quando nao e' o computador que esta' jogando
		p_jogador = i;
		q = 1; //computador
		int z;
		z = CompEscolhePedra();
		if(z == -1){
		 //se CompEscolhePedra retornou -1, significa que o computador precisa passar a vez
			passou++;
			trocaJogador();
		}
		else{
			j = z; //posicao no array dom da pedra a ser jogada
		}	
	}

	else{ /*so' precisa descobrir a posicao no array dom da pedra se tiver 2 jogadores, 
	ou se o o jogo for contra o computador, e estiver na vez de uma pessoa(jvez != playerAuto), se for vez do computador(jvez == playerAuto), jÃ¡ se tem essa informacao.*/
	q = 2; //jogador e' uma pessoa 
	opcP = escolhePedra(); //opcao de pedra
	
	/*descobre a pedra que o usuario digitou: varre o alfabeto, e descobre o indice i da opcao digitada. Depois, varre todas as pedras do domino e ve  
	quais estao com o status do jogador, se estiver soma no contador p_jogador, e faz isso ate que seja encontrado o indice j da pedra no
    array dom, que, na visao do jogador, esta na posicao p_jogador. */
	for (i = 0; i <= 25; i++){ 
	
		if(alfabeto[i] != opcP){ //serve para descobrir futuramente se opcP pertence ao alfabeto
			x++;
		}

		if (alfabeto[i] == opcP){
			i++;
			break; //descobre qual a posicao da letra do alfabeto correspondente a pedra
		}
	}

	for(j=0; j<=27; j++) { //descobre a posicao da pedra no array dom em relacao a sua posicao na mao do jogador
		if(dom[j].status == jvez){
			p_jogador++;
			if(p_jogador == i){
				break;
			}
		}
	}
	
}
	if (jogadorInicioDaFuncao == jvez){
		
	
	if((x < 26) && (i == p_jogador) || (q == 1)){ //se o contador x for menor que 26(opcP estiver no alfabeto) e se a pedra pertencer a mao do jogador, realiza a jogada normalmente
	//descobre em qual lado jogar e realiza a jogada
	p_valida = VerificaPedra(j); //sera igual a 1 se a pedra for valida
	
	if(p_valida){ //se a pedra for valida, realiza a jogada

	lado = descobreLadoMesa(j);
	
	if(!pedraIgualMesa(j)){ // se a pedra nao tiver os lados iguais aos da mesa, descobre o unico lado possivel e coloca a funcao respectiva
		if(lado == 1)
			carregaMesaE(j);
		if(lado == 2)
			carregaMesaD(j);
	}
	else if ((pedraIgualMesa(j) && jogcomp == 0)||(pedraIgualMesa(j) && jogcomp == 1 && jvez != playerAuto)){
		//apenas entra aqui se a pedra tiver os lados iguais aos da mesa e se for um jogo multiplayer, ou se for singleplayer e se for a vez do jogador
		do{
			opcL = escolheLado(); //opcao de lado
			if((opcL!= 'E' )&&(opcL!= 'e')&&(opcL!= 'D')&&(opcL!= 'd')){
				apresentaMensagem("\nDigite uma opcao valida!\n");
			}
		}while((opcL!= 'E' )&&(opcL!= 'e')&&(opcL!= 'D')&&(opcL!= 'd')); //repete ate obter um lado valido

		if (opcL == 'E' || opcL == 'e')
			carregaMesaE(j);
			//se selecionar uma das opcos, carrega o lado esquerdo
		else
			carregaMesaD(j);
			//se selecionar uma das opcos, carrega o lado esquerdo
	}
	else if(pedraIgualMesa(j) && jogcomp == 1 && jvez == playerAuto){
		carregaMesaE(j);
				}
			}
		}

		for(u=0; u<28 ;u++){ //descobre quantas pedras o jogador tem
			if(dom[u].status == jvez){
				pedras_mao++;
			}
		}

		for(r=0; r < 26; r++){ //descobre a pedra que o usuario digitou, para saber se pertence a sua mao
			if(alfabeto[r] == opcP){
				break;
			}
		}
	}
	

	if((!win && jogcomp==0) || (!win && jogcomp == 1 && jvez != playerAuto)){
		system("cls");

		if(opcP=='0')	//se a opcao for 0, ele nao mostra a mensagem
			apresentaMensagem("\n\nEscolha uma nova pedra!\n\n");

		else if ((r+1 > pedras_mao)&&(qtmesa == qtmesaAntes)&&(jogadorInicioDaFuncao == jvez))
			apresentaMensagem("\nDigite uma opcao valida, essa pedra nao pertence a sua mao!\n\n");
			
		else if ((!p_valida) && (dom[j].status == jvez))
			apresentaMensagem("\nDigite uma opcao valida, essa pedra nao pode ser jogada!\n\n");
	}
	
	if(vencedor()){
		win = 1;
	}	

}


int VerificaPedra(int k){ //verifica se a pedra e valida
	if((dom[k].L1 == mesaE)||(dom[k].L1 == mesaD)||((dom[k].L2 == mesaE)||(dom[k].L2 == mesaD))){
		return 1;
	}
	else
		return 0;
}

int descobreLadoMesa(int k){ //descobre em qual lado da mesa sera jogada a pedra
	if((dom[k].L1 == mesaE)||(dom[k].L2 == mesaE)){
		return 1; //lado esquerdo da mesa;
	}
	if((dom[k].L1 == mesaD)||(dom[k].L2 == mesaD)){
		return 2; //lado direito da mesa
	}
	else
		return 0;
}

int pedraIgualMesa(int k){ //e' verdadeira se tiver mais de um lado da mesa possivel para realizar a jogada
	if(((dom[k].L1 == mesaE)||(dom[k].L2 == mesaE))&&((dom[k].L1 == mesaD)||(dom[k].L2 == mesaD))){
		return 1; //as duas extremidades da pedra sao iguais as extremidades da mesa
	}
	else if(((dom[k].L1 == mesaE)&&(dom[k].L1 == mesaD)) || ((dom[k].L2 == mesaE)&&(dom[k].L2 == mesaD))){ 
		return 1; //se os dois lados da mesa forem iguais a apenas um lado da pedra
	}
	else
		return 0;
}

void carregaMesaE(int k){
	for(int i = qtmesa; i > 0; i--) //deslocamento de toda a mesa para abrir a primeira posicao "0"
		mesa[i] = mesa[i-1];
	//verifica se sera necessario inverter a pedra a ser jogada e joga na posicao 0 da mesa
	if (dom[k].L2 == mesaE){
		mesa[0].ladoE = dom[k].L1;
		mesa[0].ladoD = dom[k].L2;
		last_L1 = mesa[0].ladoE;
		last_L2 = mesa[0].ladoD;
		}
	else{
 		mesa[0].ladoE = dom[k].L2;
 		mesa[0].ladoD = dom[k].L1;
		last_L1 = mesa[0].ladoE;
		last_L2 = mesa[0].ladoD;
	}
	//atualiza a variavel global mesaE com o ladoE agora atualizado
	mesaE = mesa[0].ladoE;

	qtmesa++; //incrementa a quantidade de pedras na mesa
	dom[k].status = 9; //atualiza o status da pedra jogada
	passou = 0;
	if(vencedor()){ //se passar a vez for verdadeiro, troca de jogador
		win = 1;
	}
	trocaJogador();
}

void carregaMesaD(int k){
	if (dom[k].L2 == mesaD){
		mesa[qtmesa].ladoD = dom[k].L1;
		mesa[qtmesa].ladoE = dom[k].L2;
		last_L1 = mesa[qtmesa].ladoE;
		last_L2 = mesa[qtmesa].ladoD;
		}
	else{
 	mesa[qtmesa].ladoE = dom[k].L1;
 	mesa[qtmesa].ladoD = dom[k].L2;
	last_L1 = mesa[qtmesa].ladoE;
	last_L2 = mesa[qtmesa].ladoD;
	}
	//atualiza a variavel global mesaD com o ladoD agora atualizado
	mesaD = mesa[qtmesa].ladoD;
	qtmesa++; //incrementa a quantidade de pedras na mesa
	dom[k].status = 9; //atualiza o status da pedra jogada
	passou = 0;
	if(vencedor()){ //se passar a vez for verdadeiro, troca de jogador
		win = 1;
	}
	trocaJogador();
}

void comprarPedra(int jvez){
int i;	
	for (i=14; i < 28; i++){ //varre as pedras para ver se ha uma disponivel
		if (dom[i].status == 0){
			dom[i].status = jvez;
			if(jogcomp == 0 || (jogcomp == 1 && jvez !=playerAuto)){ //mostra apenas se o jogo for multiplayer ou se for singleplayer na vez da pessoa (nao e' a vez do computador)
				apresentaMensagem("\nVoce comprou uma pedra!\n");
			}
			break;
		}
	}
	if ((i >= 28 && jogcomp == 0)||(i>=28 && jogcomp == 1 && jvez != playerAuto)){
		apresentaMensagem("\nNao ha mais pedras para serem compradas!\n");
	}
}

int passarVez(){ //retorna 1 se o jogador precisa passar a vez
	int comprar = 0; //pedras que ainda restam para serem compradas
	int p_mao = 0; //pedras validas que o jogador tem na mao
	for(int i=0; i<28; i++){//verifica se ainda tem pedras para serem compradas
		if(dom[i].status == 0){
			comprar++;
		}
		if(dom[i].status == jvez){ //nas pedras do determinado jogador
			if((dom[i].L1==mesaE)||(dom[i].L1==mesaD)||(dom[i].L2==mesaD)||(dom[i].L2==mesaE)){//verifica se algum lado for igual a extremidade de alguma pedra
				p_mao++;
			}
		}
	}
	if((comprar==0)&&(p_mao==0)){ //se nao ha pedras validas na mao do jogador nem para comprar, entao e' preciso passar a vez
		if(jvez == 1)
			apresentaMensagem("\nO jogador 1 esta sem pedras validas e pulou a jogada!");
		else
			apresentaMensagem("\nO jogador 2 esta sem pedras validas e pulou a jogada!");
			
		return 1;
	}
	else
		return 0;
}

int vencedor(){ //verifica se ha' um vencedor, se tiver, mostra uma mensagem e retorna 1, caso contrario, retorna zero
	int comprar = 0;
	int p_restantes = 0;
	int qtd_pedras_1 = 0, qtd_pontos_1 = 0;
	int qtd_pedras_2 = 0, qtd_pontos_2 = 0;

	//vencedor "bateu o jogo"
	for(int i=0; i<28; i++){ //verifica se ainda tem pedras para serem compradas
		if(dom[i].status == 0){
			comprar++;
			break;
		}
		if(dom[i].status == jvez){
			p_restantes++;
			break;
		}
	}
	if(comprar == 0 && p_restantes == 0){
		if(jvez ==1){
			apresentaMensagem("\nO jogador 1 bateu o jogo! Parabens pela vitoria!\n");
			return 1;
		}
		else{
			apresentaMensagem("\nO jogador 2 bateu o jogo! Parabens pela vitoria!\n");
			return 1;
		}
	}
	
	/* Ha uma variavel global "passou" que e' incrementada de 1 cada vez que e' preciso passar a vez, e resetada para zero
    cada vez que um jogador executa uma jogada. Assim, se for preciso passar a vez 2 vezes consecutivas, a variavel
    sera' maior que 1 e indicara' que o jogo esta' fechado (nenhum dos jogadores tem condicoes de jogar), o que marca o fim do jogo.
    Portanto, nessa situacao os pontos ja' deverao ser contabilizados, em numero de pedras e, caso necessario, em valor da soma
    dos lados das pedras. */

	//conta as pedras e os pontos dos jogadores
	if (passou > 1){
		for(int k=0;k<28; k++){
			if(dom[k].status == 1){
				qtd_pedras_1++;
				qtd_pontos_1 += dom[k].L1 + dom[k].L2;
			}
			if(dom[k].status == 2){
				qtd_pedras_2++;
				qtd_pontos_2 += dom[k].L1 + dom[k].L2;
			}
		}

		if((qtd_pedras_1 == qtd_pedras_2)&&(qtd_pontos_1 < qtd_pontos_2)){
			apresentaMensagem("\nO vencedor, por quantidade de pontos, e' o jogador 1!\n");
		}
		else if((qtd_pedras_1 == qtd_pedras_2)&&(qtd_pontos_2 < qtd_pontos_1)){
			apresentaMensagem("\nO vencedor, por quantidade de pontos, e' o jogador 2!\n");
		}
		else if(qtd_pedras_1 < qtd_pedras_2){
			apresentaMensagem("\nO vencedor, por quantidade de pedras, e' o jogador 1!\n");
		}
		else if(qtd_pedras_2 < qtd_pedras_1){
			apresentaMensagem("\nO vencedor, por quantidade de pedras, e' o jogador 2!\n");
		}
	return 1;
	}
	return 0;
}

void resetar(){ //reseta tudo ate o fim de jogo
	win=0;
	IniciarPedras();
	passou = 0;
	qtmesa = 0;
}

void gravaCadastro(){ ///salva o cadastro do jogo
	if(qtmesa == 0){
		apresentaMensagem("\nSem jogo a ser gravado\n");
		return; //se nao tiver nenhuma pedra no jogo (o jogo nao comecou) entao mostra uma mensagem
	}

	if (win){
		apresentaMensagem("\nJogo terminado nao pode ser gravado\n");
		return; //se tiver um vencedor, mostra uma mensagem
		}

 	int i;
 	FILE *fp;
 	FILE *fpm;
 	FILE *fps; //definindo os documentos onde os dados serao armazenados.

	//todos os dados que serao salvos:
 	sitJogo.qtmesaJogo = qtmesa;
 	sitJogo.jvezJogo = jvez;
 	sitJogo.jogadorComp = jogcomp;
 	sitJogo.mesaDJogo = mesaD;
 	sitJogo.mesaEJogo = mesaE;
 	
 	//se os documentos estiverem vazios, entao nao podem ser abertos para cadastro
	if((fp = fopen("CAD_DOMINO", "w")) == NULL){
		apresentaMensagem("\nO arquivo CAD_DOMINO nao pode ser aberto para cadastrar\n");
		return;
 		}
 	if((fpm = fopen("CAD_MESA", "w")) == NULL){
		apresentaMensagem("\nO arquivo CAD_MESA nao pode ser aberto para cadastrar\n");
		return;
 		}
 	if((fps = fopen("CAD_JOGO", "w")) == NULL){
		apresentaMensagem("\nO arquivo CAD_JOGO nao pode ser aberto para cadastrar\n");
	return;
		}

	//se os dados nos documentos nao coincidirem com os do struct original, ocorre um erro
 	for(i = 0; i < 28; i++){
 		if (fwrite(&dom[i], sizeof(struct stpedra), 1, fp) != 1){
			apresentaMensagem("\nErro na gravacao do arquivo CAD_DOMINO\n");
			break;
 			}
 		}
 	for (i = 0; i < 28; i++){
 		if (fwrite(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1){
 			apresentaMensagem("\nErro na gravacao do arquivo CAD_MESA\n");
 			break;
			}
 		}
 	if (fwrite(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
 		apresentaMensagem("\nErro na gravacao do arquivo CAD_JOGO\n");
 		
	fclose(fps);
	fclose(fpm);
	fclose(fp); 
	//fecha os documentos apos armazenar os dados
	apresentaMensagem("\nGravados os arquivos CAD_DOMINO, CAD_MESA e CAD_JOGO\n");
}


void recuperarCadastro(){ //recupera o jogo
	int i;
 	FILE *fp;
	FILE *fpm;
 	FILE *fps;

 	if((fp = fopen("CAD_DOMINO", "r")) == NULL){
		apresentaMensagem("\nO arquivo CAD_DOMINO nao pode ser aberto\n");
		return;
		}
 	if((fpm = fopen("CAD_MESA", "r")) == NULL){
		apresentaMensagem("\nO arquivo CAD_MESA nao pode ser aberto\n");
		return;
		}
 	if((fps = fopen("CAD_JOGO", "r")) == NULL){
		apresentaMensagem("\nO arquivo CAD_JOGO nao pode ser aberto\n");
		return;
		}
		
 	for(i = 0; i < 28; i++){
		if (fread(&dom[i], sizeof(struct stpedra), 1, fp) != 1){
			apresentaMensagem("\nErro na leitura do arquivo CAD_DOMINO\n");
 			break;
 			}
		}
 	for(i = 0; i < 28; i++){
		if (fread(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1){
 			apresentaMensagem("\nErro na leitura do arquivo CAD_MESA\n");
 			break;
 			}
		}

	if (fread(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
		apresentaMensagem("\nErro na leitura do arquivo CAD_JOGO\n");
	//mesmos testes que anteriormente na funcao gravaCadastro
	fclose(fps);
	fclose(fpm);
	fclose(fp);
	//recupera os dados salvos no cadastro
	qtmesa = sitJogo.qtmesaJogo;
	jvez = sitJogo.jvezJogo;
	jogcomp = sitJogo.jogadorComp;
	mesaD = sitJogo.mesaDJogo;
	mesaE = sitJogo.mesaEJogo;
	apresentaMensagem("\nRetornando ao jogo recuperado\n");
}

int CompEscolhePedra(){ // retorna o indice da pedra para jogar, se nao tiver nenhuma para jogar, retorna -1(e' um indicativo para a funcao executaJogada)
	int x = 0;
	int comprar = 0; //pedras que existem no monte para comprar
	do{
		for(int k=0; k<28; k++){
			if(passarVez()){ //se o monte tiver alguma pedra disponivel para comprar, adiciona no contador
				k = -1;
				return k;
			}
			if (dom[k].status == playerAuto && VerificaPedra(k)){ // se a pedra for do jogador (computador) e for valida, retorna o indice
				x=1;//avisa quando achou k
				return k;
			}
		}
		comprarPedra(playerAuto);
	}while(x != 1);
}

