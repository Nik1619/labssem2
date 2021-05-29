#pragma once

#include <inttypes.h>
#include <stddef.h>

//typedef uint64_t LN_value_t;
//#define ACTUAL_LIST_VALUE_IS_NUMBER

#define LN_VALUE_IS_POINTER

typedef void* LN_value_t;

typedef struct list_node {
  struct list_node *prev, *next;
  LN_value_t value;
} list_node_t;

int LN_push_back(list_node_t **l, LN_value_t v);
int LN_pop_back(list_node_t **l);
int LN_sort(list_node_t **l, int (*cmp)(const LN_value_t*, const LN_value_t*, void* state), void* state); // a>b -> 1; a<b -> -1; a=b -> 0
void LN_swap (list_node_t *a, list_node_t *b);

size_t LN_length(const list_node_t * const l);

void LN_KD_print(const list_node_t * const l);

