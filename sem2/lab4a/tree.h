#ifndef tree_h
#define tree_h

typedef struct item{
	char* one;
	char* two;
	struct item* next;
}Item;

typedef struct node{
	Item* first;
	unsigned int key;
  	struct node* left;
  	struct node* right;
	struct node* prev;
	struct node* root;
	struct node* next;
}Node;

typedef struct tree{
	Node* root;
	int size;
	char* file;
}Tree;
Tree* create_tree(char* f);
void read_tree(Node* node, int key);
Item* search_tree(Tree* tree, int key);
Item* search_near_key_tree(Node* node, int key, int* qn, Item* it);
void file_tree(Tree* tree);
Tree* clear_tree(Tree* tree);
void clear_node(Node* node);
void insert_tree(Tree* tree, int key, char* one, char* two);
Node* delete_node(Tree* tree, Node* node, int key);

#endif
