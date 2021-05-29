#include <stdio.h>
#include <stdlib.h>

#include <kdtree.h>

size_t KDTREE_MAX_NODE_SIZE = 5;

int kdtree_build(kdtree_node_t **root, list_node_t **list, uint32_t axis) {
  printf("%s BEGIN: { axis: %u }\n", __PRETTY_FUNCTION__, axis);
	size_t list_len;
  kdtree_node_t *kd_node_to_add = NULL;
  list_node_t *mean;
	if (!root) return 1;
  if (!list) return 2;
  if (!*list) return 3;
  list_len = LN_length(*list);
  if (!list_len) return 4;

	if (!*root) {
    if (list_len > KDTREE_MAX_NODE_SIZE) {
      mean = kdtree_find_mean(list, list_len, axis);
      if (!mean) return 5;
      if (!mean->prev) return 6;

      kd_node_to_add = (kdtree_node_t*)malloc(sizeof(kdtree_node_t));
      if (!kd_node_to_add) return 7;
      kd_node_to_add->parent = NULL;
      kd_node_to_add->left = NULL;
      kd_node_to_add->right = NULL;
      kd_node_to_add->values = NULL;
      kd_node_to_add->mean = ((kdtree_key_value_pair_t*)(mean->value))->key.coordinates[axis];
      kd_node_to_add->flag = axis;
      mean->prev->next = NULL;
      mean->prev = NULL;
      kdtree_build(&kd_node_to_add->left, list, (axis +1)%KDTREE_AXIS_NUMBER);
      kdtree_build(&kd_node_to_add->right, &mean, (axis +1)%KDTREE_AXIS_NUMBER);
      if (!kd_node_to_add->left) {
        fprintf(stderr, "%s: kd_node_to_add->left == NULL\n", __PRETTY_FUNCTION__);
        *root = kd_node_to_add;
        return 8;
      }
      if (!kd_node_to_add->right) {
        fprintf(stderr, "%s: kd_node_to_add->right == NULL\n", __PRETTY_FUNCTION__);
        *root = kd_node_to_add;
        return 9;
      }
      kd_node_to_add->left->parent = kd_node_to_add;
      kd_node_to_add->right->parent = kd_node_to_add;
      *root = kd_node_to_add;
      return 0;
    } else {
      if (LN_sort(list, kdtree_pair_cmp, &axis)) return 10;
      kd_node_to_add = (kdtree_node_t*)malloc(sizeof(kdtree_node_t));
      if (!kd_node_to_add) return 11;
      kd_node_to_add->values = *list;
      *root = kd_node_to_add;
      return 0;
    }
	} else {
    return 12;
	}
}

int kdtree_pair_cmp(const LN_value_t *v1, const LN_value_t *v2, void *state) {
  uint32_t axis;
  if (!v1 || !v2 || !state) return 0;
  axis = *(uint32_t*)state;
  uint64_t res = (*((const kdtree_key_value_pair_t**)v1))->key.coordinates[axis] - (*((const kdtree_key_value_pair_t**)v2))->key.coordinates[axis];
//  printf("%s: {res: %lu}\n", __PRETTY_FUNCTION__, res);
  return res;
}

list_node_t* kdtree_find_mean(list_node_t **list, size_t list_len, uint32_t axis) {
	list_node_t *p;
  size_t i = 0;
	if (!list || !*list || axis >= KDTREE_AXIS_NUMBER) return NULL;
  if(LN_sort(list, kdtree_pair_cmp, &axis)) {
    return NULL;
  }
  p = *list;
  while (i < (list_len>>1)) {p = p->next; i++;}
  return p;
}

void kdtree_free(kdtree_node_t **root) {
  kdtree_node_t *p, *p_old;
  list_node_t *l;
  if (!root) return;
  if (!*root) return;
  p = *root;
  while (p) {
    p_old = p;
    while (p->left) { p = p->left; }
    if (p->right) {p = p->right; }
    if (p_old == p) {
      p_old = p->parent;
      if (p_old) {
        if (p == p_old->right) p_old->right = NULL;
        else p_old->left = NULL;
      }
      l = p->values;
      while (!LN_pop_back(&l)) {};
      free(p);
      p = p_old;
    }
  }
  root = NULL;
}

void kdtree_print(const kdtree_node_t *root) {
  printf("%s BEGIN\n", __PRETTY_FUNCTION__);
  if (!root) return;
  if (root->values) {
    LN_KD_print(root->values);
  } else {
    printf("{axis: %u, mean: %ll}\n", root->flag, root->mean);
    kdtree_print(root->left);
    kdtree_print(root->right);
  }
  printf("%s END\n", __PRETTY_FUNCTION__);
}

