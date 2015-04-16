typedef struct node
{
	int key;
	int val;
	int level;
    struct node **forward;
} Node;


Node * createNode(int v);

Node * createListR(int * tab, int size);

void printListR(Node * tete);

int lengthListR(Node * tete);

void freeListR(Node ** tete);

Node * insertHead(Node * tete, int v);

Node * insertToListR(Node * tete, int index, int v);

Node * removeHead(Node * tete);

Node * removeFromListR(Node * tete, int index);

void reversePrintListR(Node * tete);

void test1();

void test2();











