#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "lib.h"

char *getStr() {
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

int getInt(int *m) {
	int check;
	check = scanf("%d", m);
	if (check <= 0 || *m <= 0) {
		return 1;
	}
	return 0;
}

int getFloat(float *m) {
	int check;
	check = scanf("%e", m);
	if (check <= 0) {
		return 1;
	}
	return 0;
}

int dialog(int N) {
	char **MSGS;
	int n;
	switch(N) {
		case 0:
			n = 5;
			MSGS = (char **)calloc(n, sizeof(char *));
			MSGS[0] = "1. Добавить элемент.";
			MSGS[1] = "2. Поиск элемента.";
			MSGS[2] = "3. Удаление элемента.";
			MSGS[3] = "4. Вывод таблицы.";
			MSGS[4] = "5. Выход из программы.\n";
			puts("\n*****МЕНЮ*****");
	        break;
		case 1:
			n = 2;
			MSGS = (char **)calloc(n, sizeof(char *));
			MSGS[0] = "1. Добавить элемент.";
			MSGS[1] = "2. Выйти в меню.\n";
			puts("\n*****Добавить элемент*****");
        	break;
        case 2:
        	n = 4;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Найти по ключу первого пространства.";
			MSGS[1] = "2. Найти по ключу второго пространства.";
			MSGS[2] = "3. Найти по составному ключу.";
			MSGS[3] = "4. Выйти в меню.\n";
			puts("\n*****Поиск элемента*****");
			break;
        case 3:
        	n = 4;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Удалить по ключу первого пространства.";
			MSGS[1] = "2. Удалить по ключу второго пространства.";
			MSGS[2] = "3. Удалить по составному ключу.";
			MSGS[3] = "4. Выйти в меню.\n";
			puts("\n*****Удаление элемента*****");
        	break;
        case 4:
        	n = 4;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Вывести как упорядоченную таблицу";
			MSGS[1] = "2. Вывести как хэш-таблицу.";
			MSGS[2] = "3. Все и сразу.";
			MSGS[3] = "4. Выйти в меню.\n";
			puts("\n*****Вывод таблицы*****");
			break;
		case 21: //Найти по ключу первого пространства
			n = 3;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Найти все версии элемента в первом пространстве.";
			MSGS[1] = "2. Найти определенную версию элемента в первом пространстве.";
			MSGS[2] = "3. Назад.\n";
			puts("\n*****Поиск элемента(1)*****");
			break;
		case 22: //Найти по ключу второго пространства.
			n = 3;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Найти все версии элемента во втором пространстве.";
			MSGS[1] = "2. Найти определенную версию элемента в втором пространстве.";
			MSGS[2] = "3. Назад.\n";
			puts("\n*****Поиск элемента(2)*****");
			break;
		case 31: //Удалить по ключу первого пространства.
			n = 3;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Удалить все версии элемента.";
			MSGS[1] = "2. Удалить конкретную версию элемента.";
			MSGS[2] = "3. Назад.\n";
			puts("\n*****Удаление элемента(1)*****");
			break;
		case 32: //Удалить по ключу второго пространства
			n = 4;
        	MSGS = (char **)calloc(n, sizeof(char *));
        	MSGS[0] = "1. Удалить все версии элемента.";
			MSGS[1] = "2. Чистка таблицы.";
			MSGS[2] = "3. Удалить конкретную версию.";
			MSGS[3] = "4. Назад.\n";
			puts("\n*****Удаление элемента(2)*****");
			break;
	}

	char *error = "";
    int choice = -1;

    do {
            printf("%s", error);
            error = "Поробуйте ёще раз. Выбирите существующий пункт.\n";
            //puts("*****МЕНЮ*****");
            for (int i = 0; i < n; ++i) {
                    printf("%s\n", MSGS[i]);
            }
            printf("Ваш выбор: ");
            //getInt(&choice);
            while(getInt(&choice)) {
				if (feof(stdin)) {
					free(MSGS);
					return n;
				}
				scanf("%*[^\n]");
				printf("Повторите ввод: ");
			}
        	while (getchar() != '\n') {}
    } while (choice <= 0 || choice > n);

	free(MSGS);
    return choice;
}

Table* create_table() {
	int m1, m2;
	Table *ptr;
	ptr = (Table *)calloc(1, sizeof(Table));
	if (!ptr) {
		return NULL;
	}

	printf("Введите максимальный размер 1-ого пространства ключей:\n");
	while(getInt(&m1)) {
		if (feof(stdin)) {
			free(ptr);
			return NULL;
		}
		scanf("%*[^\n]");
		printf("Повторите ввод: ");
	}
	while (getchar() != '\n');

	printf("Введите максимальный размер 2-ого пространства ключей:\n");
	while(getInt(&m2)) {
		if (feof(stdin)) {
			free(ptr);
			return NULL;
		}
		scanf("%*[^\n]");
		printf("Повторите ввод: ");
	}
	ptr->msize1 = m1;
	ptr->msize2 = m2;
	ptr->csize1 = 0;
	//ptr->csize2 = (int *)calloc(m2, sizeof(int));
	/*if (!ptr->csize2) {
		free(ptr);
		return NULL;
	}*/
	ptr->ks1 = (KeySpace1 *)calloc(m1, sizeof(KeySpace1));
	if (!ptr->ks1) {
		//free(ptr->csize2);
		free(ptr);
		return NULL;
	}
	ptr->ks2 = (KeySpace2 **)calloc(m2, sizeof(KeySpace2 *));
	if (!ptr->ks2) {
		free(ptr->ks1);
		//free(ptr->csize2);
		free(ptr);
		return NULL;
	}
	for (int i = 0; i < m2; i++) {
		ptr->ks2[i] = NULL;
		//ptr->csize2[i] = 0;
	}
	return ptr;
}

int delete_table(Table *table) {
	for (int i = 0; i < table->csize1; i++) {
		free(table->ks1[i].info->data->str);
		free(table->ks1[i].info->data);
		free(table->ks1[i].info->key2);
		free(table->ks1[i].info);
	}
	KeySpace2 *ptr, *temp;
	for (int i = 0; i < table->msize2; i++) {
		ptr = table->ks2[i];
		while (ptr) {
			temp = ptr->next;
			free(ptr);
			ptr = temp;
		}
	}
	//free(table->csize2);
	free(table->ks1);
	free(table->ks2);
	free(table);
	
	return 0;
}

Item* makeItem() {
	Item *ptr;
	ptr = (Item *)calloc(1, sizeof(Item));
	if (!ptr) {
		return NULL;
	}
	ptr->data = (Data *)calloc(1, sizeof(Data));
	if (!ptr->data) {
		free(ptr);
		return NULL;
	}

	printf("Введите ключ первого пространства элемента таблицы: ");
	while(getInt(&ptr->key1)) {
		if (feof(stdin)) {
			free(ptr->data);
			free(ptr);
			return NULL;
		}
		scanf("%*[^\n]");
		printf("Повторите ввод: ");
	}
	while (getchar() != '\n') {}

	//проверка на уникальность
	printf("Введите ключ второго пространства элемента таблицы: ");
	ptr->key2 = getStr();

	/*запрос ключа второго пространства*/

	printf("Заполните первое поле элемента(число): ");
	while(getFloat(&ptr->data->num1)) {
		if (feof(stdin)) {
			free(ptr->data);
			free(ptr->key2);
			free(ptr);
			return NULL;
		}
		scanf("%*[^\n]");
		printf("Повторите ввод: ");
	}
	while (getchar() != '\n') {}

	printf("Заполните второе поле элемента(число): ");
	while(getFloat(&ptr->data->num2)) {
		if (feof(stdin)) {
			free(ptr->data);
			free(ptr->key2);
			free(ptr);
			return NULL;
		}
		scanf("%*[^\n]");
		printf("Повторите ввод: ");
	}
	
	while (getchar() != '\n') {}
	printf("Заполните третье поле элемента(строка): ");
	ptr->data->str = getStr();
	
	return ptr;
}

int bin_search(Table *table, unsigned int key1) {
	int i = 0; 
	int m = table->csize1 - 1;
	int j;
	while (i <= m) {
		// 	printf("%d and %d", i, m);
		j = (i + m)/2;
		if (table->ks1[j].key == key1) {
			while (table->ks1[j].release != 1) {
				j--;
			}
			return j;
		} else if (table->ks1[j].key < key1) {
			i = j + 1;
		} else {
			m = j - 1;
		}
	}

	return -1;
}

int delete_item(Item *item) {
	free(item->data->str);
	free(item->data);
	free(item->key2);
	free(item);
	return 0;
}

int remove_item_ks1(Table *table, int index) {
	KeySpace2 *ks2 = NULL, *ptr;
	int hash;
	//key2 = (char *)calloc(1, sizeof(table->ks1[index].info->key2));
	//strncpy(key2, table->ks1[index].info->key2, strlen(table->ks1[index].info->key2));
	hash = get_hash(table->ks1[index].info->key2, table->msize2);
	
	ks2 = search_ks2(table, table->ks1[index].info->key2, ks2);
	while (ks2->info->key1 != table->ks1[index].key) {
		ks2 = search_ks2(table, table->ks1[index].info->key2, ks2);
	}
	printf("\nМы нашли: %s %d\n", ks2->key, ks2->release);
	ptr = table->ks2[hash];
	if (ptr != ks2) {
		while (ptr->next != ks2) {
			ptr = ptr->next;
		}
		ptr->next = ks2->next;
	} else {
		table->ks2[hash] = ks2->next;
	}
	

	delete_item(table->ks1[index].info);
	for (int i = index; i < table->csize1 - 1; i++) {
		table->ks1[i] = table->ks1[i + 1];
	}
	table->csize1--;

	
	free(ks2);
	return 0;
}

int remove_item_ks2(Table *table, KeySpace2 *ks2) {
	int index, hash;
	KeySpace2 *ptr;
	hash = get_hash(ks2->key, table->msize2);
	ptr = table->ks2[hash];
	index = bin_search(table, ks2->info->key1);

	/*while (table->ks1[index].release != 1) {
		index--;
	}*/
	while (strcmp(table->ks1[index].info->key2, ks2->key)) {
		index++;
	}

	if (ptr != ks2) {
		while (ptr->next != ks2) {
			ptr = ptr->next;
		}
		ptr->next = ks2->next;
	} else {
		table->ks2[hash] = ks2->next;
	}

	delete_item(table->ks1[index].info);
	for (int i = index; i < table->csize1 - 1; i++) {
		table->ks1[i] = table->ks1[i + 1];
	}
	table->csize1--;
	free(ks2);
	return 0;
	//remove_item_ks1(table, index);
}

int remove_item(Table *table) {
	int K, key1, ans, index, i;
	char *key2;
	KeySpace2 *ks2 = NULL, *ptr, *temp;
	do {
		K = dialog(3);
		switch(K) {
			case 1: //Удалить по ключу первого пространства
				do {
					ans = dialog(31);
					switch(ans) {
						case 1: //Удалить все версии элемента
							printf("Введите ключ для удаления: ");
							while(getInt(&key1)){
								if (feof(stdin)) {
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							index = bin_search(table, key1);
							if (index == -1) {
								printf("Элемент не найден.");
								break;
							}
							/*while (table->ks1[index].release != 1) {
								index--;
							}*/
							//printf("\nСейчас удалим: %d, %d\n", table->ks1[index].key, table->ks1[index].release);
							while (table->ks1[index].key == key1 && table->csize1) {
								remove_item_ks1(table, index);
								//index++;
							}
							//remove_item_ks1(table, key1);
							break;
						case 2: //Удалить конкретную версию элемента
							printf("Введите ключ для удаления: ");
							while(getInt(&key1)){
								if (feof(stdin)) {
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							index = bin_search(table, key1);
							if (index == -1) {
								printf("Элемент не найден.");
								break;
							}
							printf("Введите версию элемента: ");
							while(getInt(&i)){
								if (feof(stdin)) {
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							while (table->ks1[index].key == table->ks1[index + 1].key) {
								index++;
							}
							if (i > table->ks1[index].release) {
								printf("Данной версии элемента нет в таблице.");
								break;
							}
							while (table->ks1[index].release != i) {
								index--;
							}
							/*if (i > table->csize1) {
								printf("Данной версии элемента нет в таблице.");
								break;
							}
							if (table->ks1[index].release > i) {
								while (table->ks1[index].release != i) {
									index--;
								}
							} else if (table->ks1[index].release < i) {
								//printf("Pre-Start index: %d.\n", index);
								index++;
								//printf("Start index: %d.\n", index);
								while (table->ks1[index].release != i) {
									if (table->ks1[index].release == 1) {
										index == -1;
										break;
									}
									index++;
								}
							}
							if (index == -1) {
								printf("Данной версии элемента нет в таблице.");
								break;
							}*/
							remove_item_ks1(table, index);
							break;
					}
				} while (ans != 3);
				break;
			case 2: //Удалить по ключу второго пространства
				do {
					ans = dialog(32);
					switch(ans) {
						case 1: //Удалить все версии элемента
							printf("Введите ключ второго пространства элемента таблицы: ");
							key2 = getStr();
							if (!key2) {
								return 1;
							}
							ks2 = search_ks2(table, key2, ks2);
							if (!ks2) {
								printf("Элемента с таким ключом не найдено.");
								free(key2);
								break;
							}
							do {
								remove_item_ks2(table, ks2);
								ks2 = NULL;
							} while (ks2 = search_ks2(table, key2, ks2));
							
							/*while (ks2 = search_ks2(table, key2, ks2)) {
								//printf("\nПередаю на удаление: %ss %d\n", ks2->key, ks2->release);
								remove_item_ks2(table, ks2);
								ks2 = NULL;
							}*/
							ks2 = NULL;
							free(key2);
							break;
						case 2:
							printf("Чистка таблицы запущена...\n");
							for (int j = 0; j < table->msize2; j++) {
								ks2 = table->ks2[j];
								while (ks2)  {
									//index = get_release(ks2, ks2->key);
									//key2 = ks2->key;
									ptr = ks2->next;
									while (ptr) {
										if (!strcmp(ptr->key, ks2->key)) {
											temp = ptr->next;
											remove_item_ks2(table, ptr);
											ptr = temp;
										} else {
											ptr = ptr->next;
										}
									}
									ks2 = ks2->next;
								}
							}
							
							break;
						case 3: 
							printf("Введите ключ второго пространства элемента таблицы: ");
							key2 = getStr();
							if (!key2) {
								return 1;
							}
							ks2 = search_ks2(table, key2, ks2);
							if (!ks2) {
								printf("Элемента с таким ключом не найдено.");
								free(key2);
								break;
							}
							printf("Введите версию элемента таблицы: ");
							while(getInt(&index)){
								if (feof(stdin)) {
									free(key2);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							if (ks2->release < index) {
								printf("Элемента такой версии не найдено.");
								free(key2);
								break;
							}
							while (ks2) {
								if (ks2->release == index) {
									remove_item_ks2(table, ks2);
									//free(key2);
									break;
								}
								ks2 = search_ks2(table, key2, ks2);
							}
							free(key2);
							break;
					}
				} while (ans != 4);
				break;
			case 3: //Удалить по составному ключу
				printf("Введите ключ для удаления: ");
				while(getInt(&key1)){
					if (feof(stdin)) {
						return 1;
					}
					scanf("%*[^\n]");
					printf("Повторите ввод: ");
				}
				while (getchar() != '\n');
				printf("Введите ключ второго пространства элемента таблицы: ");
				key2 = getStr();
				if (!key2) {
					return 1;
				}
				if (check_key(table, key1, key2)) {
					printf("Элемента с таким составным ключом нет.");
					free(key2);
					break;
				}
				index = bin_search(table, key1);
				/*while (table->ks1[index].release != 1) {
					index--;
				}*/
				while (1) {
					if (!strcmp(table->ks1[index].info->key2, key2)) {
						remove_item_ks1(table, index);
						free(key2);
						break;
					}
					index++;
				}

				break;
		}
	} while (K != 4);

	return 0;
}

Table* create_search_table(int m1, int m2) {
	//int m1, m2;
	Table *ptr;
	ptr = (Table *)calloc(1, sizeof(Table));
	if (!ptr) {
		return NULL;
	}

	ptr->msize1 = m1;
	ptr->msize2 = m2;
	ptr->csize1 = 0;
	//ptr->csize2 = (int *)calloc(m2, sizeof(int));
	/*if (!ptr->csize2) {
		free(ptr);
		return NULL;
	}*/
	ptr->ks1 = (KeySpace1 *)calloc(m1, sizeof(KeySpace1));
	if (!ptr->ks1) {
		//free(ptr->csize2);
		free(ptr);
		return NULL;
	}
	ptr->ks2 = (KeySpace2 **)calloc(m2, sizeof(KeySpace2 *));
	if (!ptr->ks2) {
		free(ptr->ks1);
		//free(ptr->csize2);
		free(ptr);
		return NULL;
	}
	for (int i = 0; i < m2; i++) {
		ptr->ks2[i] = NULL;
		//ptr->csize2[i] = 0;
	}
	return ptr;
}

int delete_search_table(Table *table) {
	KeySpace2 *ptr, *temp;
	for (int i = 0; i < table->msize2; i++) {
		ptr = table->ks2[i];
		while (ptr) {
			temp = ptr->next;
			free(ptr);
			ptr = temp;
		}
	}
	//free(table->csize2);
	free(table->ks1);
	free(table->ks2);
	free(table);
	return 0;
}

KeySpace2* search_ks2(Table *table, char *key, KeySpace2 *ks2) {
	KeySpace2 *ptr;
	int index;
	if (!ks2) {
		index = get_hash(key, table->msize2);
		ptr = table->ks2[index];
		//printf("I am here: %s %d", table->ks2[index]->key, table->ks2[index]->release);
	} else {
		ptr = ks2->next;
	}
	while (ptr) {
		if (!strcmp(ptr->key, key)) {
			//printf("LOLOLOLOLOLO");
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

int search(Table *table) {
	int K, key1, ans, i, index;
	KeySpace2 *ks2 = NULL;
	char *key2;
	Table *s_table;
	do {
		K = dialog(2);
		switch(K) {
			case 1: //Найти по ключу первого пространства.
				do {
					ans = dialog(21);
					switch(ans) {
						case 1: //Найти все версии элемента в первом пространстве
							printf("Введите ключ для поиска: ");
							while(getInt(&key1)){
								if (feof(stdin)) {
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							index = bin_search(table, key1);
							if (index == -1) {
								printf("Элемент не найден.");
								break;
							}

							/*while (table->ks1[index].release != 1) {
								index--;
							}*/
							s_table = create_search_table(table->msize1, table->msize2);
							add_to_table(table->ks1[index].info, s_table);
							index++;
							while (table->ks1[index].release != 1 && table->ks1[index].key) {
								add_to_table(table->ks1[index].info, s_table);
								index++;
							}

							show_table_ks1(s_table);
							delete_search_table(s_table);
							break;
						case 2: //Найти определенную версию элемента в первом пространстве.
							printf("Введите ключ для поиска: ");
							while(getInt(&key1)){
								if (feof(stdin)) {
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							index = bin_search(table, key1);
							//printf("\nindex: %d.", index);
							if (index == -1) {
								printf("Элемент не найден.");
								break;
							}
							printf("Введите версию элемента: ");
							while(getInt(&i)){
								if (feof(stdin)) {
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							//printf("We have: %d. You need: %d.\n", table->ks1[index].release, i);
							//printf("We have: %d. You need: %d.\n", table->csize1, i);
							/*if (i > table->csize1) {
								printf("Данной версии элемента нет в таблице.");
								break;
							}*/
							while (table->ks1[index].key == table->ks1[index + 1].key) {
								index++;
							}
							if (i > table->ks1[index].release) {
								printf("Данной версии элемента нет в таблице.");
								break;
							}
							while (table->ks1[index].release != i) {
								index--;
							}

							
							/*if (table->ks1[index].release > i) {
								while (table->ks1[index].release != i) {
									index--;
								}
							} else if (table->ks1[index].release < i) {
								//printf("Pre-Start index: %d.\n", index);
								//index++;
								//printf("Start index: %d.\n", index);
								while (table->ks1[index].release != i) {
									if (table->ks1[index + 1].key != key1) {
										index == -1;
										break;
									}
									index++;
								}
							}*/
							/*if (index == -1) {
								printf("Данной версии элемента нет в таблице.");
								break;
							}*/
							s_table = create_search_table(1, table->msize2);
							add_to_table(table->ks1[index].info, s_table);
							show_table_ks1(s_table);
							delete_search_table(s_table);
							break;
					}
				} while (ans != 3);
				break;
			case 2: //Найти по ключу второго пространства.
				do {
					ans = dialog(22);
					switch(ans) {
						case 1: //Найти все версии элемента во втором пространстве
							printf("Введите ключ второго пространства элемента таблицы: ");
							key2 = getStr();
							if (!key2) {
								return 1;
							}
							ks2 = search_ks2(table, key2, ks2);
							if (!ks2) {
								printf("Элемента с таким ключом не найдено.");
								free(key2);
								break;
							}
							s_table = create_search_table(table->msize1, table->msize2);
							add_to_table(ks2->info, s_table);
							while (ks2 = search_ks2(table, key2, ks2)) {
								add_to_table(ks2->info, s_table);
								//printf("Элемент добавлен\n");
							}
							show_table_ks2(s_table);
							free(key2);
							delete_search_table(s_table);
							ks2 = NULL;
							break;
						case 2: //Найти определенную версию элемента в втором пространстве.
							printf("Введите ключ второго пространства элемента таблицы: ");
							key2 = getStr();
							if (!key2) {
								return 1;
							}
							ks2 = search_ks2(table, key2, ks2);
							if (!ks2) {
								printf("Элемента с таким ключом не найдено.");
								free(key2);
								break;
							}
							printf("Введите версию элемента таблицы: ");
							while(getInt(&index)){
								if (feof(stdin)) {
									free(key2);
									//free(ptr);
									return 1;
								}
								scanf("%*[^\n]");
								printf("Повторите ввод: ");
							}
							if (ks2->release < index) {
								printf("Элемента такой не найдено.");
								ks2 = NULL;
								free(key2);
								break;
							}
							//printf("We have: %d. You need: %d.\n", ks2->release, index);
							while (1) {
								if (ks2->release == index) { //&& !strcmp(ks2->key, key2)) {
									break;
								}
								//ks2 = ks2->next;
								ks2 = search_ks2(table, key2, ks2);
							}
							s_table = create_search_table(table->msize1, table->msize2);
							add_to_table(ks2->info, s_table);
							show_table_ks2(s_table);
							free(key2);
							delete_search_table(s_table);
							ks2 = NULL;
							break;
					}
				} while (ans != 3);
				break;
			case 3: //Найти по составному ключу
				printf("Введите ключ для поиска: ");
				while(getInt(&key1)){
					if (feof(stdin)) {
						return 1;
					}
					scanf("%*[^\n]");
					printf("Повторите ввод: ");
				}
				while (getchar() != '\n');
				printf("Введите ключ второго пространства элемента таблицы: ");
				key2 = getStr();
				if (!key2) {
					return 1;
				}
				if (check_key(table, key1, key2)) {
					free(key2);
					printf("Элемента с таким составным ключом нет.");
					break;
				}
				index = bin_search(table, key1);
				/*while (table->ks1[index].release != 1) {
					index--;
				}*/
				s_table = create_search_table(table->msize1, table->msize2);
				while (1) {
					if (!strcmp(table->ks1[index].info->key2, key2)) {
						add_to_table(table->ks1[index].info, s_table);
						break;
					}
					index++;
				}
				show_table_ks1(s_table);
				show_table_ks2(s_table);
				free(key2);
				delete_search_table(s_table);
				ks2 = NULL;
				break;
		}
	} while (K != 4);
	return 0;
}

int get_hash(char *str, int size) {
	int hash = INT_MAX;
	for (int i = 0; i < strlen(str); i++) {
		hash = 37 * hash + (int)str[i];
	}
	hash = abs(hash)%size; 
	return hash;
}

/*int  get_hash(char *S, int size) {
     int hash = 0;
     while(*S) {
         r += (int)(*S);
         S++;
     }
     hash = abs(hash)%size;
     return hash;
}*/

int get_release(KeySpace2 *ptr, char *key) {
	while (ptr) {
		if (!strcmp(ptr->key, key)) {
			return ptr->release + 1;
		}
		ptr = ptr->next;
	}
	return 1;
}

int check_key(Table *table, int key1, char *key2) {
	int index;
	KeySpace2 *ks2 = NULL;
	if (!table->csize1) {
		return 1;
	}
	index = bin_search(table, key1);
	//printf("\nindex_1: %d\n", index);
	if (index == -1) { //не нашли
		return 1;
	}
	/*while (table->ks1[index].release != 1) {
		index--;
	}*/
	while (table->ks1[index].key == key1) {
		if (!strcmp(table->ks1[index].info->key2, key2)) {
			return 0;
		}
		index++;
	}
	//ks2 = search_ks2(table, key2, ks2);
	//printf("ks2: %s\n", ks2->key);
	//if (!ks2) { //не нашли
	//	return 1;
	//}
	return 1;
}

int add_to_table(Item *item, Table *table) {
	int i = -1, index;
	if (table->msize1 == table->csize1) {
		printf("Таблица переполнена");
		delete_item(item);
		return 1;
	}
	//printf("Отправлякем на проверку: %d, %s\n", item->key1, item->key2);
	if (!check_key(table, item->key1, item->key2)) {
		printf("Элемент с таким составным ключом уже существует");
		delete_item(item);
		return 1;
	}
	if (!table->csize1) {
		table->ks1[0].key = item->key1;
		table->ks1[0].release = 1;
		table->ks1[0].info = item;
	} else {
		i = table->csize1;
	}
	//printf("i: %d, SIZE: %d", i, table->csize1);
	while (i != -1) {
		if (!i) {
			table->ks1[i].key = item->key1;
			table->ks1[i].info = item;
			table->ks1[i].release = 1;
			i--;
		} else if (table->ks1[i - 1].key > item->key1) {
			table->ks1[i] = table->ks1[i - 1];
			i--;
		} else {
			table->ks1[i].key = item->key1;
			table->ks1[i].info = item;
			if (table->ks1[i - 1].key < item->key1) {
				table->ks1[i].release = 1;
			} else {
				table->ks1[i].release = table->ks1[i - 1].release + 1;
			}
			i = -1;
		}
	}

	table->csize1++;

	KeySpace2 *ptr;
	ptr = (KeySpace2 *)calloc(1, sizeof(KeySpace2));
	ptr->key = item->key2;
	//ptr->release = 1;
	ptr->info = item;

	index = get_hash(item->key2, table->msize2);
	ptr->release = get_release(table->ks2[index], item->key2);
	//table->ks2[index] = (KeySpace2 *)realloc(table->ks2[index], (1 + table->csize2[index]) * sizeof(KeySpace2));
	ptr->next = table->ks2[index];
	table->ks2[index] = ptr;
	//table->csize2[index]++;

	return 0;
}

int write_to_table(Table *table) {
	int K = dialog(1);
	Item *item;
	while (K != 2) {
		item = makeItem();
		if (!item) {
			printf("Ошибка при создании записи.\n");
		} else {
			add_to_table(item, table);
		}
		K = dialog(1);
	}
	return 0;
}

void show_table_ks1(Table *table) {
	printf("***Упорядоченная таблица***\n");
	printf(" ---------------------------------------------------------\n");
    printf("|  №  |  key1/rel  |  number 1  |  number 2  |   string   |\n");
    printf(" ---------------------------------------------------------\n");

	for (int i = 0; i < table->csize1; i++) {
		printf("| %-4d| %-5d/%-5d| %-11f| %-11f| %-11s|\n", i + 1, table->ks1[i].key, table->ks1[i].release, table->ks1[i].info->data->num1, table->ks1[i].info->data->num2, table->ks1[i].info->data->str);
		printf(" ---------------------------------------------------------\n");
	}
}

void show_table_ks2(Table *table) {
	printf("***Хэш-таблица***\n");
	KeySpace2 *ptr;
	for (int i = 0; i < table->msize2; i++) {
		int j = 0;
		printf("|| %-2d||", i);
		ptr = table->ks2[i];
		while (ptr) {
			printf("  ==>  | %s/ %d | %f | %f | %s |", ptr->key, ptr->release, ptr->info->data->num1, ptr->info->data->num2, ptr->info->data->str);
			ptr = ptr->next;
			j++;
		}
		printf("\n");
	}
}

int show_table(Table *table) {
	int K;
	do {
		K = dialog(4);
		switch(K) {
			case 1:
				//printf("***Упорядоченная таблица***\n");
				show_table_ks1(table);
				break;
			case 2:
				//printf("***Хэш-таблица***\n");
				show_table_ks2(table);
				break;
			case 3:
				//printf("***Упорядоченная таблица***\n");
				show_table_ks1(table);
				//printf("***Хэш-таблица***\n");
				show_table_ks2(table);
				break;
		}
	} while (K != 4);

	return 0;
}
