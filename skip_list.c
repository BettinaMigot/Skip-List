#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_MAX    2147483647
#define MAX_LEVEL 4
#define PROBABILITY RAND_MAX/2

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
static void skiplist_dump(Skiplist *list);
void PrintSkipList(Skiplist * L);


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

Skiplist* newSkiplist(){
	
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

	for(i = 0; i<=MAX_LEVEL; i++){
		list->header->forward[i] = NULL;
	}
	list->level = 0;
  	return list;
}


Node* search(Skiplist* list, int key) {
	Node* tmp;
	int i;

	tmp = list->header;
	for(i = (list->level)-1; i>=0; i--){
		while( tmp->forward[i]->key < key ) {
			tmp = tmp->forward[i];
		}
	}
	tmp = tmp->forward[0];
	if(tmp->key == key) {
		return tmp;
	}
	else return NULL;
}

int randomLevel(float p){
	int level = 1;
	while(rand() < p && level < MAX_LEVEL){
		level = level + 1;
	}
	return level;
}


void insert(Skiplist* list, int key, int value){
	Node* tmp;
	int i;
	int level;
	Node* update[MAX_LEVEL-1];

	tmp = list->header;
	/* On parcourt la liste à partir du plus haut niveau et on descend quand on trouve 
	une clé supérieur ou égal à la clé recherchée)*/
	for(i = (list->level)-1; i>=0; i--)
		{
		while(tmp->forward[i] != NULL && tmp->forward[i]->key < key) {
			tmp = tmp->forward[i];
		}
		update[i] = tmp;
	}
	tmp = tmp->forward[0];
	if(tmp != NULL && tmp->key == key) {
		tmp->val = value;
	}
	else {
		level = randomLevel(PROBABILITY);
		printf("level:%d\n", level);
		if( level > list->level) {
			for( i = (list->level); i <level; i++) {
				update[i] = list->header;
			}
			list->level = level;
		}
		tmp = makeNode(level, key, value);
		for(i = 0; i<level; i++) {
			tmp->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = tmp;
		}
	}
}

static void skiplist_dump(Skiplist *list)
{
    Node *x = list->header;

    while (x && x->forward[0] != list->header) {
    	if(x->forward[0]) {
    		printf("%d[%d]->", x->forward[0]->key, x->forward[0]->val);
    	}
    	x = x->forward[0];
    }
    printf("NIL\n");
}


void delete(Skiplist* list, int key){
	int i;
	int level;
	Node *tmp = list->header;
	Node* update[MAX_LEVEL-1];

	for( i = (list->level)-1; i>=0; i--){
		while(tmp->forward[i] != NULL && tmp->forward[i]->key < key) {
			tmp = tmp->forward[i];
		}
		update[i] = tmp;
	}
	tmp = tmp->forward[0];
	level = list->level;
	if(tmp->key && tmp->key == key){
		for(i = 0; i < level; i++){
			if((update[i]->forward[i]) != tmp) break;
			update[i]->forward[i] = tmp->forward[i];
		}
		free(tmp);
		while(level > 0 && list->header->forward[level-1] == NULL){
			list->level = level-1;
			level = level-1;
		}
	}
}

int main(int argc,char* argv[]){

	srand((int)time(NULL));
	rand();

	Skiplist* skiplist = newSkiplist();

	int arr[] = {1,7,3,5,6,2};
	int i;

	printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    	       
    	printf("insert %d\n", arr[i]);
        insert(skiplist, arr[i], arr[i]);


    }
    insert(skiplist,4,4);
   	skiplist_dump(skiplist);

    delete(skiplist, 5);
  	skiplist_dump(skiplist);

	return 0;
}