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
Node* search(Skiplist* list, int key);
int randomLevel(float p);
void insert(Skiplist* list, int key, int value);
void printSkipList(Skiplist * list);
int stringToInt(char []);


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
		while( tmp->forward[i]->key < key )
			tmp = tmp->forward[i];
	}
	tmp = tmp->forward[0];
	if(tmp->key == key)
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
	for (int i = list->level-1; i >= 0; i--)
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
 
int stringToInt(char a[]) {
  int c, sign, offset, n;
 
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}

int main(int argc, char* argv[])
{
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX] = "";

	srand((int)time(NULL));

	Skiplist* skiplist = newSkiplist();

	int* arr = malloc(sizeof(int));
	if (NULL == arr)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }

	const char s[2] = ",";/* Caractère délimiteur */

	/*Pour découper la chaine*/
	char *str1,  *token;
    char *saveptr1;
    int j, n = 0, i;

    fichier = fopen("list.txt", "r+");

    if (fichier != NULL)
    {
		/* On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"*/
		fgets(chaine, TAILLE_MAX, fichier);
		printf("%s \n", chaine);

		/* Séparation des valeurs + mise dans un tableau avec la fonction strtok_r qui fonctionne bizarrement
		avec plein de pointeurs */

	    for (j = 0, str1 = chaine; ; j++, str1 = NULL) {
	        token = strtok_r(str1, ",", &saveptr1);
	        if (token == NULL)
	            break;
	        /*printf("%d: %s\n", j, token);*/

	            /*Pour mettre dans le tableau j'utilise la fonction stringToInt que j'ai copié au dessus
	            je l'ai trouvée sur internet, je trouvais rien de correct en fonction des librairies "standard"*/
	            arr[j] = stringToInt(token);
	            printf("arr[%d]=%d, ", j, arr[j]);

	    }
	    printf("\n");

		/* Fermeture du fichier */
		fclose(fichier); 

		printf("taille tableau : %d\n", j);

		printf("arr[0]=%d ,",arr[0]);
		printf("arr[1]=%d ,",arr[1]);
		printf("arr[2]=%d ,",arr[2]);
		printf("arr[3]=%d ,",arr[3]);
		printf("arr[4]=%d ,",arr[4]);
		printf("arr[5]=%d",arr[5]);
		printf("\n");

	    for (i = 0; i < j; i++)
	    {
	    	printf("arr[0]=%d ,",arr[0]);
			printf("arr[1]=%d ,",arr[1]);
			printf("arr[2]=%d ,",arr[2]);
			printf("arr[3]=%d ,",arr[3]);
			printf("arr[4]=%d ,",arr[4]);
			printf("arr[5]=%d",arr[5]);
	        printf("\nValeur insérée : arr[%d]=%d\n", i, arr[i]);
	        insert(skiplist, arr[i], arr[i]);
	    }

	    printf("\nPrint List \n");
	   	printSkipList(skiplist);

	   	/*printf("\nInsert in List \n");
	    insert(skiplist, 5, 5);
	    insert(skiplist, 8, 8);
	   	printSkipList(skiplist);

	   	printf("\nDelete in List\n");
	    delete(skiplist, 5);
	  	printSkipList(skiplist);*/
    }
    else
    {
        /* Si l'ouverture du fichier n'a pas fonctionné*/
        printf("Impossible d'ouvrir le fichier list.txt");
    }

    return 0;
}