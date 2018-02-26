/*=======================================================================================================*/
/*======================================PROJETO 2 - IAED 2016/2017=======================================*/
/*===========================================Ricardo Velhinho============================================*/
/*=============================================GRUPO AL087===============================================*/
/*=======================================================================================================*/


/*=======================================================================================================*/
/*=============================================BIBLIOTECAS===============================================*/
/*=======================================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

static int contador=0; 												/* Permite a contagem de quantos nos existem */

/*=======================================================================================================*/
/*=============================================CONSTANTES================================================*/
/*=======================================================================================================*/

#define TAM 8 														/* Tamanho limite de carateres para uma chave */

/*=======================================================================================================*/
/*================================================MAIN===================================================*/
/*=======================================================================================================*/


void altera_stock(Item t,int quantidade){							/* Funcao que altera o stock dependendo se a quantidade recebida vai ser superior ou inferior a 0 */
	if (quantidade!=0){
		t->stock+=quantidade;						
	}
	if (t->stock<0){
		t->stock=0; 											
	}
	return;
}

int main(){
	int maior=-1,*maior_aux,quantidade, command ;
	char sign, maior_chave[TAM+1],mensagem[TAM+1],mensagem_a_remover[TAM+1],*msg=mensagem,*msg_r=mensagem_a_remover;													
	link produtos;
	STinit(&produtos); 												/* Vai inicializar a arvore binaria */
	maior_aux=&maior;
	while (1){
		command = getchar();
		switch(command){
			case 'a':
				getchar(); 											/* livra se do primeiro espaco */
				scanf("%s",msg); 								
				scanf("%c%d",&sign,&quantidade); 				
				if(sign=='-'){
					quantidade=quantidade*-1;						/* Caso o sinal seja '-' vai tornar a quantidade um valor negativo */
				}					
				Item t = STsearch(produtos,msg); 					/* Vai procurar na arvore pela chave correspondente */
				if ( t == NULL && quantidade >= 0){ 				/* Caso nao encontre e a quantidade seja maior ou igual a 0 */
					Item novo = newItem(mensagem,quantidade); 		
					STinsert(&produtos,novo); 					
					contador++; 
					if ( (novo->stock > maior)|| (novo->stock==maior && strcmp(novo->chave,maior_chave)<0)){
						maior = novo->stock;
						strcpy(maior_chave,novo->chave);
					}						
				}
				else if ( t== NULL && quantidade < 0){ 				/* Caso nao encontre e o stock seja menor que 0 */
					quantidade = 0;
					Item novo = newItem(mensagem,quantidade); 
					STinsert(&produtos,novo); 
					contador++;
				}	
				else if (t!= NULL){									/* Caso encontre o produto */
					altera_stock(t,quantidade); 				
					if ( quantidade>0){								/* Se a quantidade for maior que 0 vai apenas comparar com o maior stock */
						if ( (t->stock > maior)|| (t->stock==maior && strcmp(t->chave,maior_chave)<0)){  
							maior = t->stock;
							strcpy(maior_chave,t->chave);
						}									
					}
					else if (quantidade<0){							/* Se houver diminuicao de algum stock vai se percorrer a arvore para encontrar o maior */
						maior=-1;
						traverse_procura_maior(produtos,maior_aux,maior_chave);									
					}	
				}
				break;
			case 'l':
				traverse(produtos);	
				break;
			case 'm':
				if ( contador == 0) {  								/* Caso a arvore esteja vazia */
					break;
				}
				else {
					printf("%s %d\n",maior_chave,*maior_aux);
					break;
				}
			case 'r': 
				getchar();
				scanf("%s",msg_r); 								
				Item no_a_remover = STsearch(produtos,msg_r); 		/* Verifica se esse no se encontra na arvore */
				if ( no_a_remover != NULL){ 						/* Caso se encontre na arvore vai apagar dessa */		
					STdelete(&produtos,msg_r);					
					if (strcmp(msg_r,maior_chave)==0 ){				/* Caso a chave seja igual a chave maior, vai percorrer a arvore a procura da nova chave maior */
						maior=-1;
						traverse_procura_maior(produtos,maior_aux,maior_chave);
					}
					contador--; 								
				}
				break;
			case 'x':
				printf("%d\n",contador); 						/* Imprime a variavel global que conta o numero de nos existentes */ 
				STfree(&produtos); 								/* Liberta todos os elementos da arvore */ 
				return EXIT_SUCCESS; 							
		}
	}	
	return EXIT_FAILURE;
}

