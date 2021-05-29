#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "ok.h"
#include "queen.h"
//yt pfgecrfnm
int getMenuItem() {
    printf("№0 exit...\n");
    printf("№1 generate a random graph\n");
    printf("№2 add vertex\n");
    printf("№3 add an edge\n");
    printf("№4 remove vertex\n");
    printf("№5 remove an edge\n");
    printf("№6 graph output\n");
    printf("№7 поиск в ширину(цикл)\n");
    printf("№7.1 поиск в ширину (рекурсия)\n");
    printf("№8 shortest way\n");
    printf("№9 acyclicity check\n");
    printf("№10 topological sort\n");
    printf("Вы выбрали: № ");
    int menu;
    menu = getInt();
    return menu;
}

int main() {
    Graph *graph = NULL;
    int menu;
    char *name1;
    char *name2;
    double x, y;
    clock_t t;
    Path *path;
    ShortestPath *spath;
    unsigned int n, m;
    printf("Enter the file name: ");
    char *filename = get_str(stdin);
    FILE *file = fopen(filename, "rt");
    if (!file || !(graph = inputFromFile(file))) {
        printf("Failed. Try again\n");
        graph = initGraph();
    }
    if (file) {
        fclose(file);
    }
    do {
        menu = getMenuItem();
        switch (menu) {
            case 1:
                removeGraph(graph);
                printf("Enter the number of vertices: ");
                n = getInt();
                if (n == 0) {
                    printf("Empty graph created\n");
                    graph = initGraph();
                }
                else {
                    printf("Enter the number of edges: ");
                    m = getInt();
                    t = clock();
                    graph = makeRand(n, m);
                    t = clock() - t;
                    printf("timee: %.15lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                }
                break;
            case 2:
                printf("Enter Name: ");
                name1 = get_str(stdin);
                printf("Enter coordinates: ");
                x = getFloat();
                y = getFloat();
                t = clock();
                addNode(graph, name1, x, y);
                t = clock() - t;
                printf("Time: %.15lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                break;
            case 3:
                printf("Enter the name of the first vertex: ");
                name1 = get_str(stdin);
                printf("Enter the name of the second vertex: ");
                name2 = get_str(stdin);
                t = clock();
                addEdge(graph, name1, name2);
                t = clock() - t;
                printf("Time: %.15lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                free(name2);
                break;
            case 4:
                printf("Enter Name: ");
                name1 = get_str(stdin);
                t = clock();
                removeNode(graph, name1);
                t = clock() - t;
                printf("Time: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                break;
            case 5:
                printf("Enter the name of the first vertex");
                name1 = get_str(stdin);
                printf("Enter the name of the second vertex");
                name2 = get_str(stdin);
                t = clock();
                removeEdge(graph, name1, name2);
                t = clock() - t;
                printf("Time: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                free(name2);
                break;
            case 6:
                t = clock();
                print(graph);
                t = clock() - t;
                printf("Time: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                break;
            case 7:
                printf("Enter the name of the first vertex");
                name1 = get_str(stdin);
                printf("Enter the name of the second vertex");
                name2 = get_str(stdin);
                t = clock();
                path = BFS(graph, name1, name2);
                t = clock() - t;
                if (path) {
                    printPath(path);
                }
                else {
                    printf("Way not found\n");
                }
                printf("Время: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                free(name2);
                removePath(path);
                break;
            case 71:
                printf("Enter the name of the first vertex");
                name1 = get_str(stdin);
                printf("Enter the name of the second vertex");
                name2 = get_str(stdin);
                t = clock();
                path = BFSRecursive(graph, name1, name2);
                t = clock() - t;
                if (path) {
                    printPath(path);
                }
                else {
                    printf("Way not found\n");
                }
                printf("Time: %.15lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                free(name2);
                removePath(path);
                break;
            case 8:
                printf("Enter the name of the first vertex ");
                name1 = get_str(stdin);
                printf("Enter the name of the second vertex");
                name2 = get_str(stdin);
                t = clock();
                spath = BellmanFord(graph, name1, name2);
                t = clock() - t;
                if (spath) {
                    printf("The shortest way is%lf\n", spath->dist);
                    for (int i = spath->size-1; i >= 0; i--) {
                        printf("%s", spath->path[i]);
                        if (i == 0) {
                            printf("\n");
                        }
                        else {
                            printf(" -> ");
                        }
                    }
                    free(spath->path);
                    free(spath);
                }
                else {
                    printf("Way not found\n");
                }
                printf("time: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                free(name1);
                free(name2);
                break;
            case 9:
                t = clock();
                if (isCycle(graph)) {
                    printf("The graph is not acyclic\n");
                }
                else {
                    printf("The graph is acyclic\n");
                }
                t = clock() - t;
                printf("Time: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                break;
            case 10:
                t = clock();
                path = sorting(graph);
                t = clock() - t;
                if (path) {
                    printPath(path);
                    removePath(path);
                }
                else {
                    printf("Топологической сортироки,к сожалению, нет\n");
                }
                printf("Time: %.2lf мс\n", (double)t/CLOCKS_PER_SEC * 1000);
                break;
            default:
                break;
        }
    } while (menu != 0);
    file = fopen(filename, "wt");
    outputToFile(file, graph);
    fclose(file);
    printf("The graph is saved to a file %s\n", filename);
    removeGraph(graph);
    free(filename);
    return 0;
}

