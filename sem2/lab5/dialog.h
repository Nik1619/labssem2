#pragma once
#include "graph.h"
char* getStr();
char* getStr_file(FILE *fd);
int getInt(int *m);
int getNum(int *m);
int dialog();
int adding_vertex(Graph *graph);
int adding_edge(Graph *graph);
int deleting_vetrex(Graph *graph);
int deleting_edge(Graph *graph);
int genetating(Graph *graph);
int reading_file(Graph *graph);
int writing_file(Graph *graph);
int searching_in_depth(Graph *graph);
int searching_shortest_path(Graph *graph);
int searching_three_shortest_paths(Graph *graph);
Vertex *get_vertex();
Vertex *generate_vertex();
