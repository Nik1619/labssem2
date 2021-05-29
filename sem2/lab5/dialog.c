#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "graph.h"
#include "dialog.h"

char* getStr() {
	char buf[81] = {0};
	char *res = NULL;
	char *check = NULL;
	int len = 0;
	int n = 0;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			if (!res) {
				return NULL;
			}
		} else if (n > 0) {
			int chunk_len = strlen(buf);
		    int str_len = len + chunk_len;
		    check = res;
		    res = realloc(res, str_len + 1);
		    if (!res) {
		    	free(check);
		    	return NULL;
		    }
		    memcpy(res + len, buf, chunk_len);
		    len = str_len;
		} else {
			scanf("%*c");
		}
	} while (n > 0);

	if (len > 0) {
		res[len] = '\0';
	} else {
		res = calloc(1, sizeof(char));
	}
	return res;
}

char* getStr_file(FILE *fd) {
    char buf[81] = {0};
    char *res = NULL;
    char *check = NULL;
    int len = 0;
    int n = 0;

    do {
        n = fscanf(fd, "%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                    return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            check = res;
            res = (char *)realloc(res, sizeof(char)*(str_len + 1));
            if (!res) {
            	free(check);
            	return NULL;
            }
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(fd, "%*c");
        }

    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
       	res = (char *)calloc(1, sizeof(char));
    }

    return res;
}

int getInt(int *m) {
	int check;
	check = scanf("%d", m);
	if (check <= 0) {// || *m < 0) {
		if (feof(stdin)) {
			return -1;
		}
		while (getchar() != '\n') {}
		return 1;
	}
	while (getchar() != '\n') {}
	return 0;
}

int getNum(int *m) {
	int flag;
	flag = getInt(m);
	while(flag) {
		if (flag == -1) {
			return 1;
		}
		printf("Повторите ввод: ");
		flag = getInt(m);
	}
	return 0;
}

int dialog() {
	int n = 12;
	char *MSGS[] = {"0. Выход.", "1. Добавить вершину.", "2. Добавить ребро.", "3. Удалить вершину.",
                        "4. Удалить ребро.", "5. Вывод графа.", "6. Генерация графа.",
                        "7. Загрузить граф из файла.", "8. Сохранить граф в файл.", "9. Поиск в глубину.",
                        "10. Поиск кратчайшего пути (алгоритм Беллмана — Форда).", 
                        "11. поиск первых трех кратчайших путей (алгоритм Флойда-Воршалла.\n"};
	char *error = "";
    int choice = -1;

    do {
        printf("%s", error);
        error = "Поробуйте ёще раз. Выберите существующий пункт.\n";
        puts("\n*****МЕНЮ*****");
        for (int i = 0; i < n; ++i) {
                printf("%s\n", MSGS[i]);
        }
        printf("Ваш выбор: ");
        if (getNum(&choice)) {
			return 0;
		}

    } while (choice < 0 || choice > n);

    return choice;
}

int adding_vertex(Graph *graph) {
	int res;
	Vertex *vertex;
	if (!(vertex = get_vertex())) return 1;
	res = add_vertex(graph, vertex);
	if (res == 1) return 1;
	if (res == 2) printf("Элемент с такими координатами уже существует!\n");
	return 0;
}

int adding_edge(Graph *graph) {
	int x_1, x_2, y_1, y_2, weight, res;

	printf("Координата x первой вершины: ");
	if (getNum(&x_1)) return 1;

	printf("Координата y первой вершины: ");
	if (getNum(&y_1)) return 1;
	
	printf("Координата x второй вершины: ");
	if (getNum(&x_2)) return 1;

	printf("Координата y второй вершины: ");
	if (getNum(&y_2)) return 1;

	printf("Вес грани: ");
	if (getNum(&weight)) return 1;

	res = add_edge(graph, x_1, x_2, y_1, y_2, weight);
	if (res == 1) return 1;
	if (res == 2) printf("Одной или двух вершин не существует в графе!\n");
	if (res == 3) printf("Между заданными вершинами уже существует грань!\n");

	return 0;
}

int deleting_vetrex(Graph *graph) {
	int x, y, res;
	printf("Координата x вершины: ");
	if (getNum(&x)) return 1;

	printf("Координата y вершины: ");
	if (getNum(&y)) return 1;

	res = delete_vetrex(graph, x, y);
	if (res) printf("Вершины не существует в графе!\n");
	
	return 0;
}

int deleting_edge(Graph *graph) {
	int x_1, x_2, y_1, y_2, res;

	printf("Координата x первой вершины: ");
	if (getNum(&x_1)) return 1;

	printf("Координата y первой вершины: ");
	if (getNum(&y_1)) return 1;
	
	printf("Координата x второй вершины: ");
	if (getNum(&x_2)) return 1;

	printf("Координата y второй вершины: ");
	if (getNum(&y_2)) return 1;

	res = delete_edge(graph, x_1, x_2, y_1, y_2);
	if (res == 1) printf("Одной или двух вершин не существует в графе!\n");
	if (res == 2) printf("Ребра между заданными вершинами не существует!\n");

	return 0;
}

int genetating(Graph *graph) {
	int k, f;
	printf("Количество вершин в графе: ");
	if (getNum(&k)) return 1;
	printf("Частота создания ребер: ");
	if (getNum(&f)) return 1;
	if (generate_graph(graph, k, f)) return 1;
	return 0;
}

int reading_file(Graph *graph) {
	char *f_name;
	printf("Имя файла: ");
	if (!(f_name = getStr())) return 1;
	FILE *fd = fopen(f_name, "r");
    if (!fd) {
        printf("Не удалось открыть файл %s(%s).\n", f_name, strerror(errno));
        free(f_name);
       	return 0;
    }
    read_file(graph, fd);
    fclose(fd);
    free(f_name);
	return 0;
}

int writing_file(Graph *graph) {
	char *f_name;
	printf("Имя файла: ");
	if (!(f_name = getStr())) return 1;	
	FILE *fd = fopen(f_name, "w");
    if (!fd) {
        printf("Не удалось открыть файл %s(%s).\n", f_name, strerror(errno));
        free(f_name);
       	return 0;
    }
    write_file(graph, fd);
    fclose(fd);
    free(f_name);
    return 0;
}

int searching_in_depth(Graph *graph) {
	int x_1, y_1, x_2, y_2, res;
 	printf("Координата x первой вершины: ");
	if (getNum(&x_1)) return 1;

	printf("Координата y первой вершины: ");
	if (getNum(&y_1)) return 1;

	printf("Координата x второй вершины: ");
	if (getNum(&x_2)) return 1;

	printf("Координата y второй вершины: ");
	if (getNum(&y_2)) return 1;
	res = search_in_depth(graph, x_1, x_2, y_1, y_2);
	if (res == 1) return 1;
	if (res == 2) printf("Одной или двух вершин не существует в графе!\n");
	return 0;
}

int searching_shortest_path(Graph *graph) {
	int x_1, y_1, x_2, y_2, res;
 	printf("Координата x первой вершины: ");
	if (getNum(&x_1)) return 1;

	printf("Координата y первой вершины: ");
	if (getNum(&y_1)) return 1;

	printf("Координата x второй вершины: ");
	if (getNum(&x_2)) return 1;

	printf("Координата y второй вершины: ");
	if (getNum(&y_2)) return 1;
	res = Bellman_Ford_Algorithm(graph, x_1, x_2, y_1, y_2);
	if (res == 1) return 1;
	if (res == 2) printf("Одной или двух вершин не существует в графе!\n");
	return 0;
}

int searching_three_shortest_paths(Graph *graph) {
	int x_1, y_1, x_2, y_2, res;
 	printf("Координата x первой вершины: ");
	if (getNum(&x_1)) return 1;

	printf("Координата y первой вершины: ");
	if (getNum(&y_1)) return 1;

	printf("Координата x второй вершины: ");
	if (getNum(&x_2)) return 1;

	printf("Координата y второй вершины: ");
	if (getNum(&y_2)) return 1;
	res = Floyd_Warshall_Algorithm(graph, x_1, x_2, y_1, y_2);
	if (res == 1) return 1;
	if (res == 2) printf("Одной или двух вершин не существует в графе!\n");
	return 0;
}

Vertex *get_vertex() {
	Vertex *vertex;
	vertex = (Vertex *)calloc(1, sizeof(Vertex));
	printf("Имя вершины: ");
	if (!(vertex->name = getStr())) {
		free(vertex);
		return NULL;
	}	
	printf("Координата x: ");
	if (getNum(&vertex->x)) {
		free(vertex->name);
		free(vertex);
		return NULL;
	}

	printf("Координата y: ");
	if (getNum(&vertex->y)) {
		free(vertex->name);
		free(vertex);
		return NULL;
	}
	return vertex;
}

Vertex *generate_vertex() {
	Vertex *vertex;
	vertex = (Vertex *)calloc(1, sizeof(Vertex));
	if (!vertex) {
		return NULL;
	}
	int str_len = abs(rand())%10 + 5;
	vertex->name = (char *)calloc(str_len + 1, sizeof(char));
	if (!vertex->name) {
		free(vertex);
		return NULL;
	}
	for (int i = 0; i < str_len; i++) {
        vertex->name[i] = (rand() % 26 + 49) + '0';
    }
    vertex->name[str_len] = '\0';
    vertex->x = rand()%10000;
	vertex->y = rand()%10000;
	return vertex;
}
