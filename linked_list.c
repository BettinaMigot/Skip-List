#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
/*
Node * createNode(int v)
{
    Node * n = (Node *) malloc(sizeof(Node));
    if (NULL == n)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
    n->val = v;
    n->next = NULL;
    return n;
}

Node * createListR(int * tab, int size)
{
    int i;

    if (size == 0)
    {
        return NULL;
    }

    Node * tete = createNode(*tab);
    tete->next = createListR(tab + 1, size - 1);
    return tete;
}

void printListR(Node * tete)
{
    
    if (tete == NULL)
    {
        printf("NIL \n");
        return;
    }

    printf("%d ", tete->val);
    printListR(tete->next);
}

int lengthListR(Node * tete)
{
 
    if (tete == NULL)
    {
        return 0;
    }

    return 1 + lengthListR(tete->next);
}
*/
/* ATTENTION il faut remettre le pointeur de la liste à NULL
*   donc passage de l'adresse du pointeur
*/
/*
void freeListR(Node ** tete)
{
   
    if (*tete == NULL)
    {
        return;
    }

    if ((*tete)->next != NULL)
    {
        freeListR((*tete)->next);
    }
    free(*tete);
    *tete = NULL;
}

Node * insertHead(Node * tete, int v)
{
    Node * new = createNode(v);
    new->next = tete;
    return new;
}



Node * insertToListR(Node * tete, int index, int v)
{

    if (tete == NULL)
    {
        if (index == 1)
        {
            return createNode(v);
        }
        fprintf(stderr,"Insertion impossible: Empty list or index too large!\n");
        exit(1);
    }
    if (index < 1)
    {
        fprintf(stderr,"Insertion impossible: index too small!\n");
        exit(1);
    }

    if (index == 1)
    {
        return insertHead(tete,v);
    }

    tete->next = insertToListR(tete->next,index - 1,v);
    return tete;
}

Node * removeHead(Node * tete)
{
    if (tete == NULL)
    {
        fprintf(stderr,"Removal impossible: Empty list!\n");
        exit(1);
    }

    Node * next = tete->next;
    free(tete);
    return next;
}


Node * removeFromListR(Node * tete, int index)
{
    if (tete == NULL)
    {
        fprintf(stderr,"Removal impossible: Empty list!\n");
        exit(1);
    }

    if (index == 1)
    {
        return removeHead(tete);
    }

    tete->next = removeFromListR(tete->next, index - 1);
    return tete;
}

void reversePrintListR(Node * tete)
{
    if (tete == NULL)
    {
        return;
    }

    if (tete->next != NULL)
    {
        reversePrintListR(tete->next);
    }
    printf("%d ", tete->val);
}

void test1()
{
    int tab[] = {11,12,13,14,15,16,17};
    Node * liste1 = createList(tab, sizeof(tab)/sizeof(tab[0]));
    Node * liste2 = createListR(tab, sizeof(tab)/sizeof(tab[0]));
    printList(liste1);
    printList(liste2);

    liste1 = insertHead(liste1,10);
    printList(liste1);

    liste1 = insertToList(liste1,1,1);
    liste1 = insertToList(insertToList(liste1,3,4),3,3);
    liste1 = insertToListR(liste1,5,20);
    liste1 = insertHead(liste1,10);
    liste1 = insertToListR(liste1,5,2015);
    printList(liste1);
    reversePrintList(liste1);

    printf("longueur : %d\n",lengthList(liste1));
    printf("longueurR : %d\n",lengthList(liste1));

    printf("\nREMOVE\n");
    printList(liste1);
    liste1 = removeFromList(liste1,2);
    printList(liste1);

    liste1 = removeFromList(liste1,3);
    printList(liste1);

    liste1 = removeFromList(liste1,1);
    printList(liste1);

    freeList(&liste1);
    printList(liste1);
    printListR(liste1);
}

void test2()
{
    Node * tete = NULL;

    tete = insertToList(NULL,1,2);
    tete = insertToList(tete,1,1);
    tete = insertToList(insertToList(tete,3,4),3,3);
    tete = insertToListR(tete,5,20);
    tete = insertHead(tete,10);

    printList(tete);
    printListR(tete);
    printf("longueur : %d\n",lengthList(tete));
    printf("longueurR : %d\n",lengthList(tete));

    reversePrintList(tete);
    reversePrintListR(tete);

    printf("\nREMOVE\n");
    tete = removeFromList(tete,2);
    printList(tete);

    tete = removeFromList(tete,3);
    printList(tete);

    tete = removeFromList(tete,1);
    printList(tete);

    freeListR(&tete);
    printList(tete);
}*/

/*
int main(int argc,char* argv[])
{
    test1();
    test2();
    return 0;
}*/
