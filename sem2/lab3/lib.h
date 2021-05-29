#pragma once 

typedef struct {
	float num1;
	float num2;
	char *str;
} Data;

typedef struct {
		Data *data;
		
		unsigned int key1;
		char *key2;
		//int index1;
} Item;

typedef struct {
		unsigned int key;			/* ключ элемента				*/
		unsigned int release;		/* номер версии элемента			*/
		Item *info;			/* указатель на информацию			*/
} KeySpace1;

typedef struct KeySpace2 {
		char *key;		/* ключ элемента	*/
		unsigned int release;	/* номер версии элемента	*/
		Item *info;		/* указатель на информацию	*/
		struct KeySpace2 *next;	/* указатель на следующий элемент	*/
} KeySpace2;

typedef struct {
		KeySpace1 	*ks1;
		KeySpace2 	**ks2;

		int msize1;
		int msize2;

		int csize1;
		//int *csize2;
} Table;

char* getStr();

int getInt(int *m);

int getFloat(float *m);

int dialog(int N);

Table* create_table();

int delete_table(Table *table);

Item* makeItem();

int bin_search(Table *table, unsigned int key1);

int delete_item(Item *item);

int remove_item_ks1(Table *table, int index);

int remove_item_ks2(Table *table, KeySpace2 *ks2);

int remove_item(Table *table);

Table* create_search_table(int m1, int m2);

int delete_search_table(Table *table);

KeySpace2* search_ks2(Table *table, char *key, KeySpace2 *ks2);

int search(Table *table);

int get_hash(char *str, int size);

int get_release(KeySpace2 *ptr, char *key);

int check_key(Table *table, int key1, char *key2);

int add_to_table(Item *item, Table *table);

int write_to_table(Table *table);

void show_table_ks1(Table *table);

void show_table_ks2(Table *table);

int show_table(Table *table);
