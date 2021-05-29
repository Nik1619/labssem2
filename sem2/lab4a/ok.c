#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int bench(){
	int i = 10, f;
	srand(time(NULL));
	Node* node;
	for (; i <= 10; i *= 10){
		printf("%d nodes.\n", i);
		clock_t one;
		clock_t two;
		Tree* tree = create_tree(NULL);
		one = clock();
		for (int j = 1; j <= i; j ++){
			insert_tree(tree, j, NULL, NULL);
		}
		two = clock();
		printf("Time to insert %d nodes: %lf.\n", i,(double)(two - one) / CLOCKS_PER_SEC);\
		node = tree->root;
		f = rand() % i + 1;
		one = clock();
		search_tree(tree, f);
		two = clock();
		printf("Time to search node with number %d: %lf.\n", f, (double)(two - one) / CLOCKS_PER_SEC);
		f = rand() % i + 1;
		one = clock();
		search_tree(tree, f);
		two = clock();
		printf("Time to search node with number %d: %lf.\n", f, (double)(two - one) / CLOCKS_PER_SEC);
		f = rand() % i + 1;
		one = clock();
		delete_node(tree, node, f);
		two = clock();
		printf("Time to delete node with number %d: %lf.\n", f, (double)(two - one) / CLOCKS_PER_SEC);
		f = (f + rand() % i) % i + 1;
		one = clock();
		delete_node(tree, node, f);
		two = clock();
		printf("Time to delete node with number %d: %lf.\n", f, (double)(two - one) / CLOCKS_PER_SEC);
		clear_tree(tree);
		printf("\n");

	}
	return 0;
}
