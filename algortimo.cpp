//PROJETO 2 P.A
//Leslye Esteves Gomes 3976
//Ana Clara Pereira Machado 4820
//Paulo Gomes 3687


#include <string.h>
#include<stdio.h>
#include<stdlib.h>

#define TAM 22500
#define QUAT_VERT 150

struct vertice {
    char no;
    int marca;
    struct vertice *prox;
    struct arco *arc;
};

struct arco {
    struct vertice *ver;
    int marca;
    int suma;
    int clave;
    struct arco *prox;
};
int vetorRotulos[QUAT_VERT];

typedef struct sArestas{
	int label;
	int vertice1;
	int vertice2;
	float distancia;
}Arestas;

//Não consegui fazer o algoritmo de PRIM funcionar e o algoritmo de Kruskle não dá o resultado esperado
/* 
void algoritmoPrim(){
	vertice *pri, *nue, *aux, *ult, *aux2;
	arco *nueArc, *auxArc, *arcMen, *auxArc2, *antArc;
	char auxNo, auxNo2, ban2, let;
	int ban, enlace, ban3, ban4, numVer;
	system("cls");    
    ban = 0;
	while (ban==0){
        aux=pri;
        while (aux != NULL){
			if (aux->no == auxNo){
			    ban = 1;
            }
                aux = aux->prox;
            }
        aux = pri;
        while (aux->no != auxNo){
            aux = aux->prox;
        }
        aux->marca = 1;
        auxArc = aux->arc;
        while (auxArc != NULL){
            auxArc->marca = 1;
            auxArc = auxArc->prox;
        }
        ban2 = 1;
        while (ban2 == 1){
            ban2 = 0;
            aux = pri;
            while (aux != NULL){
                if (aux->marca == 0){
                    ban2 = 1;
                }
                aux = aux->prox;
            }
    	}
    }
}
*/


make_set(int *vetorRotulos){
	int i;
	for(i=1;i<=QUAT_VERT;i++){
		vetorRotulos[i]=i;
	}
}

void imprimeArestas(Arestas *arestas){
		int i;
		for(i=0;i<TAM;i++){
			printf("\n%d %d %f", arestas[i].vertice1,arestas[i].vertice2,arestas[i].distancia );
		}
}

void insertionSort(Arestas *arestas){
	int i, j;
	float valorAtual;
 
	for( j=1; j < TAM; j++ ){
		valorAtual = arestas[j].distancia;
		int vert1 = arestas[j].vertice1;
		int vert2 =arestas[j].vertice2;
		i = j-1;
    	while(i >= 0 && arestas[i].distancia > valorAtual){
        	arestas[i+1].distancia = arestas[i].distancia;
        	arestas[i+1].vertice1 = arestas[i].vertice1;
        	arestas[i+1].vertice2 = arestas[i].vertice2;
        	i--;
    	} 
              
    	arestas[i+1].distancia = valorAtual;
    	arestas[i+1].vertice1 = vert1;
    	arestas[i+1].vertice2 = vert2;
   }
}

void kruskal(Arestas *arestas, int k_grupos){
	
	int i,j,aux,aux_k=QUAT_VERT;
	make_set(vetorRotulos);
	
	if(aux_k == k_grupos){
		printf("Aresta Peso");
		return;
	}
	
	insertionSort(arestas);
	
	for(i=0;i<TAM;i++){
		if(vetorRotulos[arestas[i].vertice1]!=vetorRotulos[arestas[i].vertice2]){			
			
			if(aux_k == k_grupos){			
				break;
			}
			aux_k--;
		  				
			aux=arestas[i].vertice2;
			vetorRotulos[arestas[i].vertice2] =vetorRotulos[arestas[i].vertice1];
			
			for(j=1;j<=QUAT_VERT;j++){
				if(vetorRotulos[j]==aux){
					vetorRotulos[j]=vetorRotulos[arestas[i].vertice1];
					
				}
			}
		}
	}	
}

int main(){
	int op, tamanho,k;
	int i;
	char dados[10];	
	FILE *f;

	Arestas *arestas;
		
	arestas = (Arestas*) malloc(TAM* sizeof(Arestas));

	sprintf(dados, "lista_adj.txt");	
	f = fopen(dados,"rt");	
	
	i=0;
	while(!feof(f)) {    
	    fscanf(f,"%d %d %f", &arestas[i].vertice1,&arestas[i].vertice2,&arestas[i].distancia);
	    arestas[i].label=0;
	    i++;
	}	
	
	imprimeArestas(arestas);		
	
	do{
		printf("\n Digite quantidade de grupos: \n");	
		scanf("%d",&k);
	}while(!(k >= 1 && k <= QUAT_VERT));
			    
	kruskal(arestas,k);	
	
	printf("\nROTULOS DOS AGRUPAMENTOS\n");
	printf("\n" );
	for(i=1;i<=QUAT_VERT;i++){
		printf("%d-",vetorRotulos[i]);
	}
		
	return 0;
}
