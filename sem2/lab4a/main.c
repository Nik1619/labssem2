#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "f.h"
#include "ok.h"

int main() {
	Tree* tree = NULL;
	int h;
	void (*actions[8])(Tree** tree) = {&create_t, &insert_t, &search_t, &search_n_t, &delete_t, &read_t, &clear_t, NULL};
	do{
		h = info();
		if (actions[h]) actions[h](&tree);
	}while (h < 7);
	clear_t(&tree);
	printf("Check time (0-no/1-yes)?\n");
	h = int_data("Your choise: ");
	if (h) bench();
	printf("Bye.\n");
	return 0;
}
