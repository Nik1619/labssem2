#pragma once

#define N 30
typedef struct Adj_vert Adj_vert;
typedef struct Vertex Vertex;

typedef struct Graph {
	Vertex *Adjacency_List[N];
	int u;
} Graph;

typedef struct Vertex {
	char *name;
	int x;
	int y;
	Adj_vert *adj_vert;
	struct Vertex *next;
} Vertex;

typedef struct Adj_vert {
	Vertex *vertex;
	int weight;
	struct Adj_vert *next;	
} Adj_vert;

typedef struct Search_Arrays {
	int u;
	int *time_1; //метка времени открытия вершины d
	int *time_2; //метка времени закрытия вершины f
	Adj_vert **Adj; //список смежности для вершины u
	Vertex **vertex; //массив вершин
	int *prev; 
	int *color; //0 - белый, 1 - серый, 2 - черный
} Search_Arrays;

typedef struct BF_Search_Arrays {
	int u;
	int *d;
	int *prev;
	Vertex **vertex;
} BF_Search_Arrays;
Graph *getGraph();
int add_vertex(Graph *graph, Vertex *vertex);
int add_edge(Graph *graph, int x_1, int x_2, int y_1, int y_2, int weight);
int delete_vetrex(Graph *graph, int x, int y);
int delete_edge(Graph *graph, int x_1, int x_2, int y_1, int y_2);
Vertex *define_vertex(Graph *graph, int x, int y);
int get_hash(int x, int y);
void print_demo(Graph *graph);
int generate_graph(Graph *graph, int k, int f);
int read_file(Graph *graph, FILE *fd);
int write_file(Graph *graph, FILE *fd);
int search_in_depth(Graph *graph, int x_1, int x_2, int y_1, int y_2);
Search_Arrays *get_Search_Arrays(int U);
int delete_Search_Arrays(Search_Arrays *search);
int DFS_visit(Search_Arrays *search, int *time, int i);
void print_path(Vertex **vertex, int *prev, int s, int f);
void getIndex(Search_Arrays *search, int x_1, int x_2, int y_1, int y_2, int *I_1, int *I_2);
int Bellman_Ford_Algorithm(Graph *graph, int x_1, int x_2, int y_1, int y_2);
BF_Search_Arrays* get_BF_Search_Arrays(int U);
int delete_BF_Search_Arrays(BF_Search_Arrays *search);
int** Floyd_Warshall_Algorithm(Graph *graph, int x_1, int x_2, int y_1, int y_2);
int delete_graph(Graph *graph);
