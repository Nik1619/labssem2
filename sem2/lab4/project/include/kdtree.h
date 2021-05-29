#pragma once

#include <inttypes.h>
#include <stddef.h>

#include <list_node.h>

extern size_t KDTREE_MAX_NODE_SIZE;

#define KDTREE_AXIS_NUMBER 2

typedef struct kdtree_key {
  int64_t coordinates[KDTREE_AXIS_NUMBER];
} kdtree_key_t;

typedef uint64_t kdtree_value_t;

typedef struct kdtree_key_value_pair {
	kdtree_key_t key;
	kdtree_value_t value;
} kdtree_key_value_pair_t;

typedef struct kdtree_node {
	struct kdtree_node *parent, *left, *right;
	list_node_t *values; // TODO: change type to kdtree_key_value_pair_t;
	uint64_t mean;
	uint32_t flag; //which axis 0~x, 1~y
} kdtree_node_t;

//typedef struct kdtree_leaf_node {
//	kdtree_node *parent;
//	list_node *values;
//} kdtree_leaf_node_t;

int kdtree_insert(kdtree_node_t *root, kdtree_key_value_pair_t *pair);

int kdtree_build(kdtree_node_t **root, list_node_t **list, uint32_t axis);
list_node_t* kdtree_find_mean(list_node_t **list, size_t list_len, uint32_t axis);
int kdtree_pair_cmp(const LN_value_t *v1, const LN_value_t *v2, void *state);
void kdtree_free(kdtree_node_t **root);

void kdtree_print(const kdtree_node_t *root);

