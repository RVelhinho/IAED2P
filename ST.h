#ifndef _ST_
#define _ST_
#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
 
 
typedef struct STnode* link;
struct STnode { 
    Item item; 
    link l, r;
    int height;
};
 
 
void STinit(link*);
Item STsearch(link,Key);
void STinsert(link*,Item);
void STdelete(link*,Key);
void STfree(link*);
void traverse(link h);
void traverse_procura_maior(link h,int *maior_aux,char maior_chave[]);
 
#endif