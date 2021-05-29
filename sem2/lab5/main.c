#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "dialog.h"

int main() {
	Graph *graph = getGraph();
	int answer;
	do {
		answer = dialog();
		switch(answer) {
			case 0:
				delete_graph(graph);
			 	break;
			case 1:
				adding_vertex(graph);
			 	break;
			case 2:
				adding_edge(graph); 
				break;
			case 3:
				deleting_vetrex(graph);
			 	break;
			case 4:
				deleting_edge(graph);
				break;
			case 5:
				print_demo(graph);
			 	break;
			case 6:
				genetating(graph);
				break;
			case 7:
				reading_file(graph);
			 	break;
			case 8:
				writing_file(graph);
				break;
			case 9:
				searching_in_depth(graph);
				break;
			case 10:
				searching_shortest_path(graph);
				break;
			case 11:
				searching_three_shortest_paths(graph);
				break;
		}
	} while (answer);
	return 0;
}

