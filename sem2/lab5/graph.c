#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include "dialog.h"
#include "graph.h"

Graph *getGraph() {
	Graph *graph;
	graph = (Graph *)calloc(1, sizeof(Graph));
	for (int i = 0; i < N; i++) graph->Adjacency_List[i] = NULL;
	graph->u = 0;
	return graph;
}

int add_vertex(Graph *graph, Vertex *vertex) {
	int hash = get_hash(vertex->x, vertex->y);
	Vertex **list = graph->Adjacency_List;
	Vertex *place = list[hash];
	if (!list[hash]) {
		list[hash] = (Vertex *)calloc(1, sizeof(Vertex));
		if (!list[hash]) {
			free(vertex->name);
			free(vertex);
			return 1;
		}
		*list[hash] = *vertex;
	} else {
		if ((place->x == vertex->x) && (place->y == vertex->y)) {
				free(vertex->name);
				free(vertex);
				return 2;
		} 
		while (place->next) {
			if ((place->x == vertex->x) && (place->y == vertex->y)) {
				free(vertex->name);
				free(vertex);
				return 2;
			}
			place = place->next;
		}
		place->next = (Vertex *)calloc(1, sizeof(Vertex));
		if (!place->next) {
			free(vertex->name);
			free(vertex);
			return 1;
		}
		place = place->next;
		*place = *vertex;
	}
	graph->u++;
	free(vertex);
	return 0;
}

int add_edge(Graph *graph, int x_1, int x_2, int y_1, int y_2, int weight) {
	Adj_vert *ptr;
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex_1, *vertex_2;
	if (!(vertex_1 = define_vertex(graph, x_1, y_1))) return 2;
	if (!(vertex_2 = define_vertex(graph, x_2, y_2))) return 2;

	Adj_vert *a_vert_1 = (Adj_vert *)calloc(1, sizeof(Adj_vert));
	if (!a_vert_1) return 1;
	Adj_vert *a_vert_2 = (Adj_vert *)calloc(1, sizeof(Adj_vert));
	if (!a_vert_2) {
		free(a_vert_1);
		return 1;
	}
	a_vert_1->vertex = vertex_2;
	a_vert_1->weight = weight;
	a_vert_2->vertex = vertex_1;
	a_vert_2->weight = weight;
	//printf("names: %s %s\n", vertex_1->name, vertex_2->name);
	if (!vertex_1->adj_vert) {
		vertex_1->adj_vert = a_vert_1;
	} else {
		ptr = vertex_1->adj_vert;
		if (ptr->vertex == vertex_2) {
			//printf("!!!!!!!!\n");
			free(a_vert_1);
			free(a_vert_2);
			return 3;
		}
		while (ptr->next) {
			//printf("%s %s\n", ptr->vertex->name, vertex_2->name);
			if (ptr->next->vertex == vertex_2) {
				//printf("!!!\n");
				free(a_vert_1);
				free(a_vert_2);
				return 3;
			}
			ptr = ptr->next;
		}
		ptr->next = a_vert_1;
	}

	if (!vertex_2->adj_vert) {
		vertex_2->adj_vert = a_vert_2;
	} else {
		ptr = vertex_2->adj_vert;
		while (ptr->next) ptr = ptr->next;
		ptr->next = a_vert_2;
	}

	return 0;
}

int delete_vetrex(Graph *graph, int x, int y) {
	Vertex **list = graph->Adjacency_List;
	int hash = get_hash(x, y);
	Vertex *vertex = list[hash];
	Vertex *prev_ver = NULL;
	Adj_vert *adj_vert, *temp_adj;

	if (!vertex) return 1;

	while (vertex->x != x || vertex->y != y) {
		//printf("!!!\n");
		if (!vertex->next) return 1;
		prev_ver = vertex;
		vertex = vertex->next;
	}

	//if (vertex == list[hash] && vertex->x != x && vertex->y != y) return 1;

	adj_vert = vertex->adj_vert;
	while (adj_vert) {
		temp_adj = adj_vert->next;
		delete_edge(graph, x, adj_vert->vertex->x, y, adj_vert->vertex->y);
		adj_vert = temp_adj;
	}

	if (!prev_ver) {
		list[hash] = vertex->next;
	} else {
		prev_ver->next = vertex->next;
	}
	graph->u--;
	free(vertex->name);
	free(vertex);

	return 0;
}

int delete_edge(Graph *graph, int x_1, int x_2, int y_1, int y_2) {
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex_1, *vertex_2;
	Adj_vert *adj_vert, *prev_adj_vert = NULL;
	int check_del = 0;
	if (!(vertex_1 = define_vertex(graph, x_1, y_1))) return 1;
	if (!(vertex_2 = define_vertex(graph, x_2, y_2))) return 1;

	adj_vert = vertex_1->adj_vert;
	while (adj_vert) {
		if (adj_vert->vertex == vertex_2) {
			if (!prev_adj_vert) {
				vertex_1->adj_vert = adj_vert->next;
			} else {
				prev_adj_vert->next = adj_vert->next;
			}
			free(adj_vert);
			check_del = 1;
			break;
		}
		prev_adj_vert = adj_vert;
		adj_vert = adj_vert->next;
	}

	if (!check_del) return 2;
	prev_adj_vert = NULL;

	adj_vert = vertex_2->adj_vert;
	while (adj_vert) {
		if (adj_vert->vertex == vertex_1) {
			if (!prev_adj_vert) {
				vertex_2->adj_vert = adj_vert->next;
			} else {
				prev_adj_vert->next = adj_vert->next;
			}
			free(adj_vert);
			break;
		}
		prev_adj_vert = adj_vert;
		adj_vert = adj_vert->next;
	}

	return 0;
}

Vertex *define_vertex(Graph *graph, int x, int y) {
	Vertex **list = graph->Adjacency_List;
	int hash = get_hash(x, y);
	Vertex *vertex = list[hash];
	if (!vertex) return NULL;
	while (vertex->x != x || vertex->y != y) {
		if (!vertex->next) return NULL;
		vertex = vertex->next;
	}
	return vertex;
}

int get_hash(int x, int y) {
	int hash = INT_MAX;
	char *p_x = (char *)&x;
	char *p_y = (char *)&y;
	for (int i = 0; i < 3; i++) {
		hash = 37 * hash + (int)p_x[i] - (i * y - x + 1)*(int)p_y[i];
	}
	hash = abs(hash)%N; 
	return hash;
}

void print_demo(Graph *graph) {
	printf("Количество вершин в графе: %d.\n", graph->u);
	Vertex **list = graph->Adjacency_List;
	Vertex *ptr;
	Adj_vert *adj_vert;
	for (int i = 0; i < N; i++) {
		printf("|| %-2d||", i);
		ptr = list[i];
		while (ptr) {
			printf("   ==>   %s(%d, %d)", ptr->name, ptr->x, ptr->y);
			adj_vert = ptr->adj_vert;
			printf(":[");
			while (adj_vert) {
				printf("%s(%d)", adj_vert->vertex->name, adj_vert->weight);
				adj_vert = adj_vert->next;
			}
			printf("]");
			ptr = ptr->next;
		}
		printf("\n");
	}
}

int generate_graph(Graph *graph, int k, int f) {
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex;
	int x, y, x_ver, y_ver;
	for (int i = 0; i < k; i++) {
		vertex = generate_vertex();
		if (!vertex) return 1;
		x_ver = vertex->x;
		y_ver = vertex->y;
		if (!i) {
			x = x_ver;
			y = y_ver;
		}
		add_vertex(graph, vertex);
		if (!(i%f)) {
			add_edge(graph, x, x_ver, y, y_ver, rand()%100);
		}
		if (i%f%3) {
			x = x_ver;
			y = y_ver;
		}
	}
	//graph->n += k;
	return 0;
}

int read_file(Graph *graph, FILE *fd) {
	Vertex **list = graph->Adjacency_List;
	char *str, check;
	char str_adj[] = "!!!adjacency!!!";
	Vertex *vertex;
	int x_vec, y_vec, weight, x, y;
	str = getStr_file(fd);
	if (!str) return 1; 
	while (strcmp(str, str_adj)) {
		vertex = (Vertex *)calloc(1, sizeof(Vertex));
		vertex->name = str;
		fscanf(fd, "%d", &vertex->x);
    	fscanf(fd, "%d", &vertex->y);
    	add_vertex(graph, vertex);
    	//printf("name: %s\n", str);
    	str = getStr_file(fd);
    	free(str);
		str = getStr_file(fd);
		if (!str) return 1;
	}
	free(str);

	while (!feof(fd)) {
		fscanf(fd, "%d", &x_vec);
    	fscanf(fd, "%d", &y_vec);
    	fscanf(fd, "%c", &check);
    	while (check == '|') {
    		fscanf(fd, "%d", &weight);
    		fscanf(fd, "%d", &x);
    		fscanf(fd, "%d", &y);
    		add_edge(graph, x_vec, x, y_vec, y, weight); 
    		fscanf(fd, "%c", &check);
    	}
	}
	return 0;
}

int write_file(Graph *graph, FILE *fd) {
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex;
	Adj_vert *adj_vert;
	char str_adj[] = "!!!adjacency!!!";
	for (int i = 0; i < N; i++) {
		vertex = list[i];
		while (vertex) {
			fprintf(fd, "%s\n", vertex->name);
			fprintf(fd, "%d %d\n", vertex->x, vertex->y);
			vertex = vertex->next;
		}
	}
	fprintf(fd, "%s\n", str_adj);
	for (int i = 0; i < N; i++) {
		vertex = list[i];
		while (vertex) {
			adj_vert = vertex->adj_vert;
			if (adj_vert) {
				fprintf(fd, "%d %d", vertex->x, vertex->y);
				while (adj_vert) {
					fprintf(fd, "| %d %d %d", adj_vert->weight, adj_vert->vertex->x, adj_vert->vertex->y);
					adj_vert = adj_vert->next;
				}
				fprintf(fd, "%c", '\n');
			}
			vertex = vertex->next;
		}
	}
	return 0;
}

int search_in_depth(Graph *graph, int x_1, int x_2, int y_1, int y_2) {
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex;
	Adj_vert *adj_vert;
	int time = 0, k = 0, s = -1, f = -1;

	Search_Arrays *search = get_Search_Arrays(graph->u);
	if (!search) return 1;

	for (int i = 0; i < N; i++) {
 		vertex = list[i];
 		while (vertex) {
 			search->Adj[k] = vertex->adj_vert;
 			search->vertex[k] = vertex;
 			search->color[k] = 0;
 			search->prev[k] = -1;
 			if (vertex->x == x_1 && vertex->y == y_1) {
 				s = k;
 			} else if (vertex->x == x_2 && vertex->y == y_2) {
 				f = k;
 			}
 			k++;
 			vertex = vertex->next;
 		}
 	}

 	/*for (int i = 0; i < graph->u; i++) {
		printf("%d: %s\n", i, search->vertex[i]->name);
	}*/

 	//getIndex(search, x_1, x_2, y_1, y_2, &s, &f);
 	//printf("%d %d\n", s, f);
 	if (s < 0 || f < 0) {
 		delete_Search_Arrays(search);
 		return 2;
 	}

 	for (int i = s; i < graph->u; i++) {
 		if (search->color[i] == 0) {
 			DFS_visit(search, &time, i);
 		}
 	}
 	for (int i = 0; i < s; i++) {
 		if (search->color[i] == 0) {
 			DFS_visit(search, &time, i);
 		}
 	}

 	/*printf("PREV:\n");
 	for (int i = 0; i < graph->u; i++) {
 		printf("%d: %d\n", i, search->prev[i]);
 	}*/
	
	print_path(search->vertex, search->prev, s, f);
	delete_Search_Arrays(search); 

	return 0;

}

Search_Arrays *get_Search_Arrays(int U) {
	Search_Arrays *search = (Search_Arrays *)calloc(1, sizeof(Search_Arrays));
	if (!search) return NULL;
	search->u = U;
	search->time_1 = (int *)calloc(U, sizeof(int));
	if (!search->time_1) {
		free(search);
		return NULL;
	}
	search->time_2 = (int *)calloc(U, sizeof(int));
	if (!search->time_2) {
		free(search->time_1);
		free(search);
		return NULL;
	}
	search->Adj = (Adj_vert **)calloc(U, sizeof(Adj_vert *));
	if (!search->Adj) {
		free(search->time_2);
		free(search->time_1);
		free(search);
		return NULL;
	}
	search->vertex = (Vertex **)calloc(U, sizeof(Vertex *));
	if (!search->vertex) {
		free(search->Adj);
		free(search->time_2);
		free(search->time_1);
		free(search);
		return NULL;
	}
	search->prev = (int *)calloc(U, sizeof(int));
	if (!search->prev) {
		free(search->vertex);
		free(search->Adj);
		free(search->time_2);
		free(search->time_1);
		free(search);
		return NULL;
	}
	search->color = (int *)calloc(U, sizeof(int));
	if (!search->color) {
		free(search->prev);
		free(search->vertex);
		free(search->Adj);
		free(search->time_2);
		free(search->time_1);
		free(search);
		return NULL;
	}
	return search;
}

int delete_Search_Arrays(Search_Arrays *search) {
	free(search->time_1);
	free(search->time_2);
	free(search->Adj);
	free(search->vertex);
	free(search->prev);
	free(search->color);
	free(search);
	return 0;
}

int DFS_visit(Search_Arrays *search, int *time, int i) {
	//printf("Рассматриваем вершину %s!\n", search->vertex[i]->name);
	search->color[i] = 1;
	*time++;
	search->time_1[i] = *time;
	Adj_vert *adj_vert = search->Adj[i];
	while (adj_vert) {
		int j = 0;
		//printf("Смежная вершина имя: %s", adj_vert->vertex->name);
		while (adj_vert->vertex != search->vertex[j]) j++;
		//printf(" индекс %d\n", j);
		if (search->color[j] == 0) {
			//printf("prev[%d] = %d\n", j, i);
			search->prev[j] = i;
			DFS_visit(search, time, j);
			//DFS_visit(U, j, time, time_1, time_2, Adj, S_vertex, prev, color);
		}
		adj_vert = adj_vert->next;
	}
	search->color[i] = 2;
	*time++;
	search->time_2[i] = *time;
	return 0;
}

void print_path(Vertex **vertex, int *prev, int s, int f) {
	if (f == s) {
		printf("%s(%d, %d)\n", vertex[s]->name, vertex[s]->x, vertex[s]->y);
		return;
	}
	if (prev[f] < 0) {
		printf("Путь отсутствует!\n");
		return;
	}
	printf("%s(%d, %d) -> ", vertex[f]->name, vertex[f]->x, vertex[f]->y);
	print_path(vertex, prev, s, prev[f]);
}

void getIndex(Search_Arrays *search, int x_1, int x_2, int y_1, int y_2, int *I_1, int *I_2) {
	int check = 0;
	for (int i = 0; i < search->u; i++) {
		if ((search->vertex[i]->x == x_1) && (search->vertex[i]->y == y_1)) {
			*I_1 = i;
			check++;
		}
		if ((search->vertex[i]->x == x_2) && (search->vertex[i]->y == y_2)) {
			*I_2 = i;
			check++;
		}
		if (check == 2) return;
	}
}

int Bellman_Ford_Algorithm(Graph *graph, int x_1, int x_2, int y_1, int y_2) {
	int k = 0, s = -1, f = -1;
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex;
	Adj_vert *adj_vert;

	BF_Search_Arrays *search = get_BF_Search_Arrays(graph->u);
	if (!search) return 1;

	for (int i = 0; i < N; i++) {
 		vertex = list[i];
 		while (vertex) {
 			search->vertex[k] = vertex;
 			search->d[k] = INT_MAX;
 			search->prev[k] = -1;
			if (vertex->x == x_1 && vertex->y == y_1) {
 				s = k;
 				search->d[k] = 0;
 			} else if (vertex->x == x_2 && vertex->y == y_2) {
 				f = k;
 			}
 			k++;
 			vertex = vertex->next;
 		}
 	}

 	if (s < 0 || f < 0) {
 		delete_BF_Search_Arrays(search);
 		return 2;
 	}

 	for (int i = 0; i < graph->u; i++) {
 		if (i == s) continue;
 		adj_vert = search->vertex[i]->adj_vert;
 		while (adj_vert) {
 			int j = 0;
 			while (adj_vert->vertex != search->vertex[j]) j++;
 			//printf("Edge %s-%s\n", search->vertex[i]->name, search->vertex[j]->name);
 			if ((search->d[j] != INT_MAX) && (search->d[i] > search->d[j] + adj_vert->weight)) {	
 				search->d[i] = search->d[j] + adj_vert->weight;
 				search->prev[i] = j;
 			}
 			adj_vert = adj_vert->next;
 		}
 	}
 	print_path(search->vertex, search->prev, s, f);
 	delete_BF_Search_Arrays(search);
	return 0;
}

BF_Search_Arrays* get_BF_Search_Arrays(int u) {
	BF_Search_Arrays *search;
	search = (BF_Search_Arrays *)calloc(1, sizeof(BF_Search_Arrays));
	if (!search) return NULL;
	search->u = u;
	search->d = (int *)calloc(u, sizeof(int));
	if (!search->d) {
		free(search);
		return NULL;
	}
	search->prev = (int *)calloc(u, sizeof(int));
	if (!search->prev) {
		free(search->d);
		free(search);
		return NULL;
	}
	search->vertex = (Vertex **)calloc(u, sizeof(Vertex *));
	if (!search->vertex) {
		free(search->prev);
		free(search->d);
		free(search);
		return NULL;
	}
	return search;
}

int delete_BF_Search_Arrays(BF_Search_Arrays *search) {
	free(search->vertex);
	free(search->prev);
	free(search->d);
	free(search);
	return 0;
}

int** Floyd_Warshall_Algorithm(Graph *graph, int x_1, int x_2, int y_1, int y_2) {
	Vertex *vertex[graph->u];
	int d[graph->u][graph->u];
	Adj_vert *adj_vert;
	int k = 0, s = -1, f = -1;
	for (int i = 0; i < N; i++) {
		Vertex *vert = graph->Adjacency_List[i];
		while (vert) {
			vertex[k] = vert;
			if (vert->x == x_1 && vert->y == y_1) {
				s = k;
			}
			if (vert->x == x_2 && vert->y == y_2) {
				f = k;
			}
			k++;
			vert = vert->next;
		}
	}
	if (s < 0 || f < 0) return NULL;

	for (int i = 0; i < graph->u; i++) {
		for (int j = 0; j < graph->u; j++) {
			d[i][j] = 0;
		}
	}
	for (int i = 0; i < graph->u; i++) {
		for (int j = 0; j < graph->u; j++) {
			if (i == j) continue;
			adj_vert = vertex[i]->adj_vert;
			while (adj_vert) {
				if (adj_vert->vertex == vertex[j]) {
					d[i][j] = adj_vert->weight;
					break;
				}
				adj_vert = adj_vert->next;
			}
		}
	}
	/*printf("  ");
	for (int i = 0; i < graph->u; i++) printf("%d ", i);
	printf("\n");
	for (int i = 0; i < graph->u; i++) {
		printf("%d ", i);
		for (int j = 0; j < graph->u; j++) {
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}*/
	for (int k = 0; k < graph->u; k++) {
		for (int i = 0; i < graph->u; i++) {
			for (int j = 0; j < graph->u; j++) {
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
				}
			}
		}
	}
	int res[3], lenght;
	for (int i = 0; i < 3; i++) res[i] = 0;
	for (int k = 0; k < graph->u; k++) {
		lenght = d[s][k] + d[k][f];
		if (lenght < res[2]) {
			if (lenght > res[1]) {
				res[2] = lenght;
			} else if (lenght > res[0]) {
				res[2] = res[1];
				res[1] = lenght;
			} else {
				res[2] = res[1];
				res[1] = res[0];
				res[0] = lenght;
			}
		} 
	}
	return res;
}

int delete_graph(Graph *graph) { 
	Vertex **list = graph->Adjacency_List;
	Vertex *vertex, *temp_vertex;
	Adj_vert *adj_vert, *temp_adj;
	for (int i = 0; i < N; i++) {
		vertex = list[i];
		while(vertex) {
			adj_vert = vertex->adj_vert;
			while (adj_vert) {
				temp_adj = adj_vert->next;
				free(adj_vert);
				adj_vert = temp_adj;
			}
			temp_vertex = vertex->next;
			free(vertex->name);
			free(vertex);
			vertex = temp_vertex;
		}
	}
	free(graph);
	return 0;
}
