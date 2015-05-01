#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INT_MAX    2147483647
#define MAX_LEVEL 4
#define PROBABILITY RAND_MAX/2
#define TAILLE_MAX 100 // Tableau de taille 100 pour lire le fichier

typedef struct node
{
	int key;
	int val;
	int level;
    struct node *forward[MAX_LEVEL];
} Node;

typedef struct skiplist{
	int level;
	struct node *header;
} Skiplist;


Node * makeNode(int level, int key, int value);
Skiplist* newSkiplist();
void initializeFromFile(Skiplist* skiplist, char* f);
Node* search(Skiplist* list, int key);
int randomLevel(float p);
void insert(Skiplist* list, int key, int value);
void printSkipList(Skiplist * list);

Node * makeNode(int level, int key, int value)
{
    Node * n = malloc(sizeof(Node) + sizeof(Node)*level);
    if (NULL == n)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
    n->val = value;
    n->key = key;
    n->level = level;
    n->forward[0] = NULL;
    return n;
}

Skiplist* newSkiplist()
{
	
	int i;

	Skiplist* list = malloc(sizeof(Skiplist));
	if (NULL == list)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
	
	list->header = malloc(sizeof(Node) + (MAX_LEVEL)*sizeof(Node));
	if (NULL == list->header)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
	
    list->header->key = INT_MAX;
    list->header->val = 0;

	for(i = 0; i<=MAX_LEVEL; i++)
	{
		list->header->forward[i] = NULL;
	}
	list->level = 0;
  	return list;
}




Node* search(Skiplist* list, int key)
{
	Node* tmp;
	int i;

	tmp = list->header;
	for(i = (list->level)-1; i>=0; i--)
	{
		while(tmp->forward[i] != NULL && tmp->forward[i]->key < key )
			tmp = tmp->forward[i];
	}
	tmp = tmp->forward[0];
	if(tmp != NULL && tmp->key == key)
	{
		return tmp;
	}
	else return NULL;
}

int randomLevel(float p)
{
	int level = 1;
	while(rand() < p && level < MAX_LEVEL-1)
	{
		level = level + 1;
	}
	return level;
}


void insert(Skiplist* list, int key, int value)
{
	Node* tmp;
	int i;
	int level;
	Node* update[MAX_LEVEL-1];

	tmp = list->header;
	/* On parcourt la liste à partir du plus haut niveau et on descend quand on trouve 
	une clé supérieur ou égal à la clé recherchée)*/
	for(i = (list->level)-1; i>=0; i--)
	{
		while(tmp->forward[i] != NULL && tmp->forward[i]->key < key)
		{
			tmp = tmp->forward[i];
		}
		update[i] = tmp;
	}
	tmp = tmp->forward[0];
	if(tmp != NULL && tmp->key == key)
	{
		tmp->val = value;
	}
	else {
		level = randomLevel(PROBABILITY);
		if( level > list->level)
		{
			for( i = (list->level); i <level; i++)
			{
				update[i] = list->header;
			}
			list->level = level;
		}
		tmp = makeNode(level, key, value);
		for(i = 0; i<level; i++)
		{
			tmp->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = tmp;
		}
	}
}

void printSkipList(Skiplist *list)
{
 	printf("\n");
 	Node* x1;
 	Node* x2;
 	int i;

	for (i = list->level-1; i >= 0; i--)
	{	printf("[HEAD]");
		x1 = list->header->forward[i];
		x2 = list->header->forward[0];
		while(x1 != NULL)
		{	while (x1->key != x2->key)
			{
				printf("----");
				x2 = x2->forward[0];
			}
			printf("-[%d]",x1->val);
			x1 = x1->forward[i];
			x2 = x2->forward[0];
		}
		while(x2 != NULL)
		{
			printf("----");
			x2 = x2->forward[0];
		}
		printf("->NIL\n");
	}
	printf("\n");
}


void delete(Skiplist* list, int key)
{
	int i;
	int level;
	Node *tmp = list->header;
	Node* update[MAX_LEVEL-1];

	for( i = (list->level)-1; i>=0; i--)
	{
		while(tmp->forward[i] != NULL && tmp->forward[i]->key < key)
		{
			tmp = tmp->forward[i];
		}
		update[i] = tmp;
	}
	tmp = tmp->forward[0];
	level = list->level;
	if(tmp->key && tmp->key == key){
		for(i = 0; i < level; i++)
		{
			if((update[i]->forward[i]) != tmp) break;
			update[i]->forward[i] = tmp->forward[i];
		}
		free(tmp);
		while(level > 0 && list->header->forward[level-1] == NULL)
		{
			list->level = level-1;
			level = level-1;
		}
	}
}

void initializeFromFile(Skiplist* skiplist, char* f){

	FILE* fichier = NULL;
	char chaine[TAILLE_MAX] = "";
	int i=0, j = 0;
	char* str1;

	int* arr = malloc(sizeof(int));
	if (NULL == arr)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
    fichier = fopen(f, "r+");
    if (fichier != NULL)
    {
		/* On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"*/
		fgets(chaine, TAILLE_MAX, fichier);
	
		printf("chaine: %s\n", chaine);

		str1 = strtok(chaine,",");
		printf("str1: %s\n", str1 );
		while(str1 != NULL) {
			arr[i++] = atoi(str1);
			j++;

			printf("arr:%d\n",atoi(str1));
			str1 = strtok(NULL, ",");

			printf("str1: %s\n", str1 );
		}
		for(i=0;i<6;i++){
			printf("%d\n",arr[i] );
		}
		fclose(fichier); 
		for (i = 0; i < j; i++)
	    {
	        insert(skiplist, arr[i], arr[i]);
	    }
	}
	else
    {
        /* Si l'ouverture du fichier n'a pas fonctionné*/
        printf("Impossible d'ouvrir le fichier list.txt");
    }
}

int main(int argc, char* argv[])
{

	char* fichier = argv[1];
	srand((int)time(NULL));

	Skiplist* skiplist = newSkiplist();

	/*initialisation de la skiplist selon un fichier passer en paramètre*/
	initializeFromFile(skiplist, fichier);
    printf("\nPrint List \n");
   	printSkipList(skiplist);

   	/*test de search*/
	printf("Value searched: %d \n", search(skiplist,4)->val);

	/*test d'insert*/
	printf("\nInsertion of 8:\n");
	insert(skiplist, 8, 8);
	printSkipList(skiplist);

	/*test de delete*/
   	printf("\nDelete in List of 2\n");
    delete(skiplist, 2);
  	printSkipList(skiplist);

    return 0;
}