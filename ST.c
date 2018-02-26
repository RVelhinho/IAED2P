#include "ST.h"

void traverse(link h) /* Vai visitar a raiz depois da sub-arvore esquerda e antes da direita */
{
    if (h == NULL) 
        return;
    traverse(h->l);
    visitItem(h->item);
    traverse(h->r);
}

void traverse_procura_maior(link h,int *maior_aux,char maior_chave[]) /* Tal como no traverse vai visitar a raiz depois da sub-arvore esquerda e antes da direita 
                                                                     mas em vez de imprimir vai comparar os stocks */
{
    if (h == NULL) 
        return;
    traverse_procura_maior(h->l,maior_aux,maior_chave);
    if ((h->item->stock>*maior_aux)){
        *maior_aux=h->item->stock;
        strcpy(maior_chave,h->item->chave);
    }
    traverse_procura_maior(h->r,maior_aux,maior_chave);
}
 
 
 
void STinit(link*head)  /* Inicializa a arvore */
{
    *head = NULL;
}
 
 
 
int height(link h){
    if (h == NULL) return 0;
    return h->height;
}
 
link rotL(link h)           /* Faz rotacao para a esquerda */
{
    int height_left, height_right;
    link x = h->r;
    h->r = x->l;
    x->l = h;
    height_left = height(h->l); height_right = height(h->r);
    h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    height_left = height(x->l); height_right = height(x->r);
    x->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    return x;
   }
 
   
link rotR(link h) /* Faz rotacao para a direita */
{
    int height_left, height_right;
    link x = h->l;
    h->l = x->r;
    x->r = h;
    height_left = height(h->l); height_right = height(h->r);
    h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    height_left = height(x->l); height_right = height(x->r);
    x->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    return x; 
}
 
 
link rotLR(link h)  /* rotacao dupla esquerda-direita */
{
    if (h==NULL) return h;
    h->l=rotL(h->l);
    return rotR(h);
}
 
 
link rotRL(link h) /* rotacao dupla direita-esquerda */
{
    if (h==NULL) return h;
    h->r=rotR(h->r);
    return rotL(h);
}
 
int Balance(link h) 
{
    if(h == NULL) return 0;
    return height(h->l)-height(h->r);
}
 
link AVLbalance(link h)    
{
    int balanceFactor;
    if (h==NULL) return h;
    balanceFactor= Balance(h);
    if(balanceFactor>1) {
        if (Balance(h->l)>=0) h=rotR(h);
        else h=rotLR(h);
    }
    else if(balanceFactor<-1){
         
        if (Balance(h->r)<=0) 
            h = rotL(h);
        else
            h = rotRL(h);
    }
    else {
        int height_left = height(h->l); 
        int height_right = height(h->r);
        h->height = height_left > height_right ?  height_left + 1 : height_right + 1;
    }
    return h; 
}

link NEW(Item item, link l, link r)   
{
    link x = (link)malloc(sizeof(struct STnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->height=1;
    return x; 
}
 
link insertR(link h, Item item) 
{
    if (h == NULL)
        return NEW(item, NULL, NULL);
         
    if (less(key(item), key(h->item)))
        h->l = insertR(h->l, item);
     
    else
        h->r = insertR(h->r, item);
         
    h = AVLbalance(h);
    return h;
}
 
 
void STinsert(link*head, Item item) /* Insere um novo no na arvore */
{
    *head = insertR(*head, item);
}
 
 
Item searchR(link h, Key v) 
{
    if (h == NULL)
        return NULL;
    if (eq(v, key(h->item)))
        return h->item;
    if (less(v, key(h->item)))
        return searchR(h->l, v);
    else
        return searchR(h->r, v);
}
 
Item STsearch(link head, Key v)   /* Procura por um determinado Item na arvore */
{
    return searchR(head, v);
} 
 
 
link max(link h) {
  if (h==NULL || h->r==NULL) 
    return h;
  else
    return max(h->r);
}
 
 
link min(link h) { 
  if (h==NULL || h->l==NULL) 
    return h;
  else
    return min(h->l);
}
 
 
link deleteR(link h, Key k) /* Remove k da arvore */
{
    if (h==NULL) return h;
    else if (less(k, key(h->item))) h->l=deleteR(h->l,k);
    else if (less(key(h->item), k)) h->r=deleteR(h->r,k) ;
    else {
        if (h->l !=NULL && h->r !=NULL){    /* caso em que ha ambos os filhos */                      
            link aux = max(h->l);
            {Item x; x=h->item; h->item=aux->item; aux->item=x;}
            h->l= deleteR(h->l, key(aux->item));
        }
        else {               /* casos em que nao ha filhos ou ha filho unico  */
            link aux=h;
            if ( h->l == NULL && h->r == NULL ) h=NULL;
            else if (h->l==NULL) h=h->r;                        
            else h=h->l;
            deleteItem(aux->item);
            free(aux);  
        } 
    }
    h=AVLbalance(h);
    return h;
}
 
void STdelete(link*head, Key k){
    *head = deleteR(*head, k);
}
 
 
link freeR(link h)
{
    if (h==NULL)
        return h;
    h->l=freeR(h->l);
    h->r=freeR(h->r);
    return deleteR(h,key(h->item));
}
 
 
void STfree(link*head) /* Liberta o espaco de memoria ocupado pela arvore */
{
    *head=freeR(*head);
}
 