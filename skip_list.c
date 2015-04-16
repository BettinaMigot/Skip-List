#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 4
#define PROBABILITY 0.5

typedef struct node
{
	int key;
	int val;
	int level;
    struct node **forward;
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


Node * makeNode(int level, int key, int value)
{
    Node * n = (Node *) malloc(sizeof(Node));
    if (NULL == n)
    {
        fprintf(stderr,"Not enough memory!\n");
        exit(1);
    }
    n->val = value;
    n->key = key;
    n->level = level;
    n->forward = NULL;
    return n;
}

Skiplist* newSkiplist(){
	int i;

	Skiplist* list = (Skiplist *)calloc(1,sizeof(Skiplist));
	
	list->level = 0;
	list->header = (Node*)calloc(1,(MAX_LEVEL+1)*sizeof(Node));
	
	list->header->forward = (Node**)calloc(1,(MAX_LEVEL+1)*sizeof(Node*));


	list->header->val = 0;
    list->header->key = 0;
    list->header->level = 0;
	for(i = 0; i<MAX_LEVEL-1; i++){
		list->header->forward[i] = NULL;
	
	}
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
	int level = 0;
	while(rand() < p && level < MAX_LEVEL){
		level = level + 1;
	}
	return level;
}


void insert(Skiplist* list, int key, int value){
	Node* tmp;
	int i;
	int level;
	Node* update[MAX_LEVEL];

	tmp = list->header;
	/* On parcourt la liste à partir du plus haut niveau et
	 on descend quand on trouve une clé 
	supérieur ou égal à la clé recherchée)*/
	for(i = (list->level)-1; i>=0; i--){
		printf("%d, %d\n", list->level,i );
		while( tmp->forward[i]->key < key) {
			tmp = tmp->forward[i];
		}
		update[i] = tmp;
	}
	tmp = tmp->forward[0];
	if(tmp->key == key) {
		tmp->val = value;
	}
	/*else {
		level = randomLevel(PROBABILITY);
		if( level > list->level) {
			for( i = (list->level)-1; i <=level; i++) {
				update[i] = list->header;
			}
			list->level = level;
		}
		tmp = makeNode(level, key, value);
		for(i = 0; i<level; i++) {
			tmp->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = tmp;
		}
	}*/
}

static void skiplist_dump(Skiplist *list)
{
    Node *x = list->header;/*
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->val);
        x = x->forward[1];
    }
    printf("NIL\n");*/
}

int main(int argc,char* argv[]){
	printf("test\n");

	Skiplist* skiplist = newSkiplist();

	int arr[] = {1,2,3,4,5,6,7};
	int i;

	printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
    	printf("insert\n");
        insert(skiplist, arr[i], arr[i]);
    }
/*
    skiplist_dump(skiplist);*/


	return 0;
}
