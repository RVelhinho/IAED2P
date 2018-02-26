#ifndef _ITEM_
#define _ITEM_
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define key(a) (a != NULL ? a->chave : "")
#define less(a,b) (strcmp(a,b)<0)
#define eq(a,b) (strcmp(a, b)==0)
 
typedef char* Key;
 
typedef struct produto{
    char* chave; 
    int stock; 
}* Item;
 
Item newItem(char*chave,int stock);
void deleteItem(Item a);
void visitItem(Item a);
 
#endif

