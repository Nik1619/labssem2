#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tree.h"
#include "f.h"

int check_tree(Tree** tree){
	if (*tree){
		return 1;
	}
	else{
		printf("No tree in memory.\n");
		return 0;
	}
}

char* str_data(char d[]){
	printf("%s", d);
	char buf[20] = {0};
	char* res = NULL;
	int len = 0;
	int n = 0;
	do{
		n = scanf("%20[^\n]",buf);
		if(n < 0){
			if(!res) return NULL;	
		} else if(n > 0){
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res,str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		} else{
			scanf("%*c");
		}
	}while(n > 0);

	if(len > 0) res[len] = '\0';
	else res = calloc(1,sizeof(char));
	return res;
}

unsigned int int_data(char* k){
	int n = 1, g;
	do{
		if (n != 1) scanf("%*s");
		printf("%s", k);
		n = scanf("%d%*c", &g);
	}while (g <= 0 || n != 1);
	return g;
}

void insert_t(Tree** tree){
	if (check_tree(tree) == 0) return ;
	int n = int_data("Keyboard input (1) or file (1>): ");
	unsigned int key;
	char* one = NULL;
	char* two = NULL;
	//int n = 1;
	if (n == 1){
		key = int_data("Enter your key: ");
		one = str_data("Enter first string: ");
		two = str_data("Enter second string: ");
	}
	else{
		int s1, s2;
		FILE* f = fopen((*tree)->file, "rb");
		if (f){
		fread(&key, sizeof(unsigned int), 1, f);
		fread(&s1, sizeof(int), 1, f);
		fread(one, s1, 1, f);
		fread(&s2, sizeof(int), 1, f);
		fread(two, s2, 1, f);}
		else{
			printf("No file in memory.\n");
			return ;
		}

	}
	insert_tree(*tree, key, one, two);
}

void read_t(Tree** tree){
	Node* node = (*tree)->root;
	int key = int_data("Enter max key: ");
	read_tree(node, key);
}

void search_t(Tree** tree){
	int key = int_data("Enter your key: ");
	Item* it = search_tree(*tree, key);
	if (it){
		printf("First string: %s\n", it->one);
		printf("Second string: %s\n", it->two);
	}
	else{
		printf("No node in memory.\n");
	}
}

void search_n_t(Tree** tree){
	int key = int_data("Enter your key: ");
	int n = 100000;
	int *qn = &n;
	Item* it;
	it = search_near_key_tree((*tree)->root, key, qn, it);
	int h = 1;
	if (it->next)
		h = int_data("Enter number of item: ");
	for (int i = 0; i < h - 1; i ++){
		it = it->next;
	}
	printf("Key: %d.\n", key + *qn);
	if (*qn < 0) *qn *= (-1);
	printf("Difference between keys is %d.\n", *qn);
	printf("First string: %s\n", it->one);
	printf("Second string: %s\n", it->two);
}

void delete_t(Tree** tree){
	int key = int_data("Enter your key: ");
	Node* node = (*tree)->root;
	delete_node(*tree, node, key);
}

void clear_t(Tree** tree){
	if (check_tree(tree) == 1){
	puts("HH");
	*tree = clear_tree(*tree);}

}

void create_t(Tree** tree){
	if(*tree){
		printf("No need in creating a tree, it is already created.\n");
	}
	else{
		char* f = str_data("Enter name of input file: ");
		*tree = create_tree(f);
		printf("Tree was successfully created.\n");
	}
}

int info(){
	int g, n = 1;
	do{
		if (n != 1) scanf("%*s");
		printf("\nChoose any  option.\n");
		printf("0) Create tree.\n");
		printf("1) Insert info.\n");
		printf("2) Search for info.\n");
		printf("3) Search for nearest key.\n");
		printf("4) Delete info.\n");
		printf("5) Read tree.\n");
		printf("6) Remove tree.\n");
		printf("7) Leave...\n");
		printf("Your choice: ");
		n = scanf("%d%*c", &g);
	}while (g < 0 || g > 7 || n != 1);
	return g;
}
