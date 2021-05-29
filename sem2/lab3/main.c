#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main() {
	int answer;
	Table *table;
	table = create_table();
	if (!table) {return 1;}
	do {
		answer = dialog(0);
		switch(answer) {
			case 1:
				write_to_table(table);
				break;
			case 2:
				if (search(table)) {answer = 5;};
				break;
			case 3:
				remove_item(table);
				break;
			case 4:
				show_table(table);
				break;
			case 5:
				//delete_table(table);
				break;
		}
	} while (answer != 5);
	delete_table(table);
	return 0;
}
