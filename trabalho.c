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
	for(i=2;i<QTDPOP;i++){
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

void verificarPossibilidadeDeMutacao(Cromossomo *c, int cidades[QTDCIDADE][QTDCIDADE], int *cidade1, int *cidade2, int *posicao1, int *posicao2){
	int aux = 1;
	while(aux == 1){
		aux = 0;
		*posicao1 = (rand()%9)+1; //sorteia posição no cromossomo
		*posicao2 = (rand()%9)+1; //sorteia posição no cromossomo
		*cidade1 = (*c).sequencia[*posicao1]; //cidade da posição sorteada
		*cidade2 = (*c).sequencia[*posicao2]; //cidade da posição sorteada
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
	}
}

int main(){
	int cidades[QTDCIDADE][QTDCIDADE];
	int i, j;
	int aux;
	srand(time(NULL));
	
	for(i=0;i<QTDCIDADE;i++){
		for(j=0;j<QTDCIDADE;j++){
			cidades[i][j] = (rand()%10)+1;
		}
	}

	int cidadeAux, k, z;
	// Função feita para se criar possivei caminhos entre para o caixero viajante
	Populacao populacao[QTDPOP]; // Estrutura para se armazenar os possiveis caminhos, cromossomos e população 
	for(z=0;z<QTDPOP;z++){
		for(i=0;i<QTDCROMOSSOMO;i++){
			for(j=0;j<QTDCIDADE+1;j++){// Inicializa o cromossomo com 0, valor que o cromossomo nao devera possuir ao final 
				populacao[z].pop[i].sequencia[j]=0;		
			}
			printf("ENTREI\n");
			for(k=1;k<QTDCIDADE;k++){
				aux = 1;
				while(aux == 1){
					aux = 0;
					cidadeAux = (rand()%QTDCIDADE-1)+1;// sorteia uma cidade que nao seja a 0 
					for(j=1;j<k;j++){
						if((populacao[z].pop[i].sequencia[j] == cidadeAux)){ // Verifica se a cidade ja esta no cromossomo 
							printf("ENTREI1 aux = %d\n", aux);
							aux=1;
						}
					}
					if(cidades[populacao[z].pop[i].sequencia[k-1]][cidadeAux]==0){
						aux = 1;
						printf("ENTREI2\n");
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

	for (z=0;z<QTDGERACAO;z++){
		printf("Populaçao %d \n", z);
		for(i=0;i<QTDCROMOSSOMO;i++){
			printf("Cromossomo %d \n", i);
			int cidade1, cidade2, posicao1, posicao2;
			verificarPossibilidadeDeMutacao(&populacao[z].pop[i], cidades, &cidade1, &cidade2, &posicao1, &posicao2);
			printf("Encontrei cidade \nSequencia antiga \n");
			for (j=0;j<QTDCIDADE+1;j++){
				printf(" {%d} ", populacao[z].pop[i].sequencia[j]);
			}
			printf("\n");
			// Realizando mutação 
			populacao[z].pop[i].sequencia[posicao1] = cidade2;
			populacao[z].pop[i].sequencia[posicao2] = cidade1;
			printf("Ditancia antiga %d \n",populacao[z].pop[i].distancia);
			populacao[z].pop[i].distancia = 0;
			calcularDistancia(&populacao[z].pop[i],cidades);
			printf("Cidades Trocadas, ditancia %d \n, nova sequencia \n",populacao[z].pop[i].distancia);
			for (j=0;j<QTDCIDADE+1;j++){
				printf(" {%d} ", populacao[z].pop[i].sequencia[j]);
			}
			printf("\n");
		}
		calcularMenorESegundoMenor(&populacao[z]);
	}
	return 0;
}