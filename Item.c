#include "Item.h"
 
Item newItem(char*chave,int stock) /* Cria um novo Item */ 
{
    Item x = (Item)malloc(sizeof(struct produto));
    x->chave = strdup(chave);
    x->stock = stock;
    return x; 
}
 
void deleteItem(Item a) /* Remove o Item a */
{
    free(a->chave);
    free(a); 
}
 
void visitItem(Item a) /* Imprime o Item a */
{
    printf("%s %d\n",a->chave, a->stock);
}