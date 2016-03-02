#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define QTDCIDADE 10
#define QTDCROMOSSOMO 20
#define QTDPOP 10
#define QTDGERACAO 10

typedef struct{
	int sequencia[QTDCIDADE+1]; /* Sequencia de cidades */
	int distancia; /* Distancia total percorrida */
}Cromossomo;

typedef struct  {
	Cromossomo pop[QTDCROMOSSOMO];
}Populacao;

void popularMatriz(int cidades[QTDCIDADE][QTDCIDADE]){
	int i, j;
	for(i=0;i<QTDCIDADE;i++){
		for(j=0;j<QTDCIDADE;j++){
			cidades[i][j] = (rand()%10)+1;
			printf(" {%d} ",cidades[i][j]);
		}
		printf("\n");
	}
}

void calcularDistancia( Cromossomo *c, int cidades[QTDCIDADE][QTDCIDADE]){
	int aux, i;
	aux = 0;
	(*c).distancia = 0;
	for (i=1;i<QTDCIDADE+1;i++){
		aux = cidades[(*c).sequencia[i-1]][(*c).sequencia[i]];
		(*c).distancia += aux;
	}
}

void calcularMenorESegundoMenor(Populacao *p){
	int i, menor1, menor2;
	if((*p).pop[0].distancia <= (*p).pop[1].distancia){
		menor1 = 0;
		menor2 = 1;
	}else{
		menor1 = 1;
		menor2 = 0;
	}
	for(i=2;i<QTDCROMOSSOMO;i++){
		if((*p).pop[i].distancia < (*p).pop[menor1].distancia){
			menor2 = menor1;
			menor1 = i;
			
		}else if((*p).pop[i].distancia == (*p).pop[menor1].distancia){
			menor2 = i;
			
		}else if((*p).pop[i].distancia < (*p).pop[menor2].distancia){
			menor2 = i;
			
		}
	}
	Cromossomo aux;
	if(menor1 != 0){
		aux = (*p).pop[0];
		(*p).pop[0] = (*p).pop[menor1];
		(*p).pop[menor1] = aux;
	}
	if(menor2 != 1 && !(menor1 == 1 && menor2 == 0)){ //Segunda condição para caso os dois menores so estejam invertidos
		aux = (*p).pop[1];
		(*p).pop[1] = (*p).pop[menor2];
		(*p).pop[menor2] = aux;
	}
}

int verificarSeExiste(Cromossomo *aux, int cidades[QTDCIDADE][QTDCIDADE]){
	int a, certo;
	certo = 1;
	for (a=1;a<QTDCIDADE+1;a++){
		if(cidades[(*aux).sequencia[a-1]][(*aux).sequencia[a]] == 0){
			certo = 0;
		}
		
	}
	return certo;
}

int crossover(Populacao *p, int cidades[QTDCIDADE][QTDCIDADE]){
	int i, j, cont, existe;
	Cromossomo aux1, aux2;
	cont = 2;
	for(i=1;i<QTDCIDADE;i++){
		for(j=0;j<QTDCIDADE+1;j++){
			if(j<i){
				aux1.sequencia[j] = (*p).pop[0].sequencia[j];
				aux2.sequencia[j] = (*p).pop[1].sequencia[j];
			}else{
				aux1.sequencia[j] = (*p).pop[1].sequencia[j];
				aux2.sequencia[j] = (*p).pop[0].sequencia[j];
			}
		}
		existe = verificarSeExiste(&aux1, cidades);
		if (existe == 1 && cont < (QTDCROMOSSOMO*0.8)){
			(*p).pop[cont] = aux1;

			(*p).pop[cont+1] = aux2;
			cont += 2;
			printf("ENCONTROU CROSSOVER \n");
		}
	}
	return cont;
}

int verificarPossibilidadeDeMutacao(Cromossomo *c, int cidades[QTDCIDADE][QTDCIDADE], int *cidade1, int *cidade2, int *posicao1, int *posicao2){
	int aux = 0;
	if(*cidade1 == 0 || *cidade2 == 0){
		aux = 0;
	}
	if (*posicao1 == *posicao2){ //verifica se nao são as mesmas posições
		aux = 1;
	}else if(((*posicao1-*posicao2)>1 || ((*posicao1-*posicao2)*(-1))>1)&&(aux == 0)){ // Verifica se a diferença entre as posições é maior que 1, e trata essa condição 
		if(cidades[*cidade1][(*c).sequencia[*posicao2-1]] == 0){ // verifica se a cidade anterior possui conecção 
			aux = 1;	
		}
		else if(cidades[*cidade1][(*c).sequencia[*posicao2+1]] == 0 ){ // verifica se a cidade posterior possui conecção 
			aux = 1;	
		}
		else if(cidades[*cidade2][(*c).sequencia[*posicao1-1]] == 0 ){ // verifica se a cidade anterior possui conecção 
			aux = 1;
		}
		else if(cidades[*cidade2][(*c).sequencia[*posicao1+1]] == 0 ){ // verifica se a cidade posterior possui conecção 
			aux = 1;
		}
	}else if(aux == 0){ // Trata a verificação quando as posições são vizinhas 
		if((*posicao1-*posicao2)==1){ // condição para pisição 1 estar depois da posição 2 no vetor 
			if(cidades[*cidade1][(*c).sequencia[*posicao2-1]] == 0){ // verifica se a cidade anterior possui conecção 
				aux = 1;
			}
			else if(cidades[*cidade1][(*c).sequencia[*posicao2+2]] == 0 ){ // verifica se a cidade posterior possui conecção 
				aux = 1;
			}
			else if(cidades[*cidade2][(*c).sequencia[*posicao1-2]] == 0 ){ // verifica se a cidade anterior possui conecção 
				aux = 1;
			}
			else if(cidades[*cidade2][(*c).sequencia[*posicao1+1]] == 0 ){ // verifica se a cidade posterior possui conecção 
				aux = 1;
			}
		}else if (aux == 0){// condição para pisição 2 estar depois da posição 1 no vetor 
			if(cidades[*cidade1][(*c).sequencia[*posicao2-2]] == 0 ){ // verifica se a cidade anterior possui conecção 
				aux = 1;
			}
			else if(cidades[*cidade1][(*c).sequencia[*posicao2+1]] == 0 ){ // verifica se a cidade posterior possui conecção 
				aux = 1;	
			}
			else if(cidades[*cidade2][(*c).sequencia[*posicao1-1]] == 0 ){ // verifica se a cidade anterior possui conecção 
				aux = 1;
			}
			else if(cidades[*cidade2][(*c).sequencia[*posicao1+2]] == 0 ){ // verifica se a cidade posterior possui conecção 
				aux = 1;
			}
		}
	}
	return aux;
}

void mutacao (Populacao *p, int cidades[QTDCIDADE][QTDCIDADE], int inicio){
	int a, cidade1, cidade2, posicao1, posicao2, aux;

	for (a = inicio; a < QTDCROMOSSOMO; a++){
		aux = 1;
		while(aux == 1){ 
			posicao1 = (rand()%9)+1; //sorteia posição no cromossomo
			posicao2 = (rand()%9)+1; //sorteia posição no cromossomo
			cidade1 = (*p).pop[a].sequencia[posicao1]; //cidade da posição sorteada
			cidade2 = (*p).pop[a].sequencia[posicao2]; //cidade da posição sorteada
			aux = verificarPossibilidadeDeMutacao(&(*p).pop[a], cidades, &cidade1, &cidade2, &posicao1, &posicao2);
		}
		(*p).pop[a].sequencia[posicao1] = cidade1;
		(*p).pop[a].sequencia[posicao2] = cidade2;
	}
}

int main(){
	int cidades[QTDCIDADE][QTDCIDADE];
	int i, j, z;
	int aux;
	srand(time(NULL));
	
	popularMatriz(cidades);

	int cidadeAux, k;
	// Função feita para se criar possivei caminhos entre para o caixero viajante
	Populacao populacao[QTDPOP]; // Estrutura para se armazenar os possiveis caminhos, cromossomos e população 
	for(z=0;z<QTDPOP;z++){
		for(i=0;i<QTDCROMOSSOMO;i++){
			for(j=0;j<QTDCIDADE+1;j++){// Inicializa o cromossomo com 0, valor que o cromossomo nao devera possuir ao final 
				populacao[z].pop[i].sequencia[j]=0;		
			}
			for(k=1;k<QTDCIDADE;k++){
				aux = 1;
				while(aux == 1){
					aux = 0;
					cidadeAux = (rand()%QTDCIDADE-1)+1;// sorteia uma cidade que nao seja a 0 
					for(j=1;j<k;j++){
						if((populacao[z].pop[i].sequencia[j] == cidadeAux)){ // Verifica se a cidade ja esta no cromossomo 
							aux=1;
						}
					}
					if(cidades[populacao[z].pop[i].sequencia[k-1]][cidadeAux]==0){
						aux = 1;
					}

					if(aux == 0){// Se a cidadeAux nao for repetida ela é adicionana no croossomo e a sua distancia é somada tambem 
					populacao[z].pop[i].sequencia[k]=cidadeAux;
					}
				}
			}
			calcularDistancia(&populacao[z].pop[i],cidades);
		}
		calcularMenorESegundoMenor(&populacao[z]);
	}

	printf("POPULACAO FEITA \n");

	for (z=0;z<QTDPOP;z++){
		printf("Antes\n");
		for(i=0;i<QTDCROMOSSOMO;i++){
			printf("Cromossomo %d, Distancia %d \n", i, populacao[z].pop[i].distancia);
			for(j=0;j < QTDCIDADE+1; j++){
				printf(" {%d} ", populacao[z].pop[i].sequencia[j]);
			}
			printf("\n");
		}
		aux = crossover(&populacao[z], cidades);
		printf("Depois, aux = %d\n", aux);
		
		mutacao(&populacao[z], cidades, aux);
		
		
		for(i=0;i<QTDCROMOSSOMO;i++){
			calcularDistancia(&populacao[z].pop[i],cidades);
		}

		calcularMenorESegundoMenor(&populacao[z]);
		
		for(i=0;i<QTDCROMOSSOMO;i++){
			printf("Cromossomo %d, Distancia %d \n", i, populacao[z].pop[i].distancia);
			for(j=0;j < QTDCIDADE+1; j++){
				printf(" {%d} ", populacao[z].pop[i].sequencia[j]);
			}
			printf("\n");
		}
		
		//for(i=0;i<QTDCROMOSSOMO;i++){
		//	printf("Cromossomo %d, Distancia %d \n", i, populacao[z].pop[i].distancia);
		//}
	}
	return 0;
}