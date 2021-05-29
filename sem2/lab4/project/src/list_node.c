#include <stdio.h>
#include <stdlib.h>

#include <list_node.h>
#include <kdtree.h>

int LN_push_back(list_node_t **l, LN_value_t v){
  list_node_t *ptr, *p;
  if (!l) return 1;
  if (!*l) {
    *l = (list_node_t*)malloc(sizeof(list_node_t));
    if (!*l) return 2;
    (*l)->prev = NULL;
    (*l)->next = NULL;
    (*l)->value = v;
    return 0;
  } else {
    ptr = (list_node_t*)malloc(sizeof(list_node_t));
    if (!ptr) return 3;
    ptr->value = v;
    p = *l;
    while(p->next) p = p->next;
    p->next = ptr;
    ptr->prev = p;
    ptr->next = NULL;
    return 0;
  }
}

int LN_pop_back(list_node_t **l){
  list_node_t *p;
  if (!l) return 1;
  if (!*l) return 2;
  p = *l;
  while (p->next) p = p->next;
  if (p->prev) {
    p->prev->next = NULL;
  } else {
    *l = NULL;
  }
#ifdef LN_VALUE_IS_POINTER
  free(p->value);

#endif
  free(p);
  return 0;
}

int LN_sort(list_node_t **l, int (*cmp)(const LN_value_t*, const LN_value_t*, void* state), void* state) {
//  printf("%s BEGIN: {axis: %u}\n", __PRETTY_FUNCTION__, *(uint32_t*)state);
  list_node_t *p, *b, *e;
  int check;
  if (!l || !*l){
  return 1;
  }
  b = *l;
//  LN_KD_print(*l);
  do {
    check = 0;
    p = b;
    while(p->next) {
      if (cmp(&p->value, &p->next->value, state) > 0) {
//        printf("%s: above: { p->value: %lu, p->next->value: %lu }\n", __PRETTY_FUNCTION__,
//            ((kdtree_key_value_pair_t*)(p->value))->key.coordinates[*(uint32_t*)state],
//            ((kdtree_key_value_pair_t*)(p->next->value))->key.coordinates[*(uint32_t*)state]);
        LN_swap(p, p->next);
        if (!check) {

#ifdef LN_VALUE_IS_POINTER

          if (p->prev) {
            b = p->prev;
            check = 1;
          }

#else

          if (p->prev->prev) { // p->prev exists since it was previously p->next
            b = p->prev->prev;
            check = 1;
          } else {
            *l = p->prev;
          }

#endif

        }

#ifdef LN_VALUE_IS_POINTER

        p = p->next;

#else

  // p and p->next has been already exchanged and p has already advanced

#endif

      } else {
//        printf("%s: less or equal: { p->value: %lu, p->next->value: %lu }\n", __PRETTY_FUNCTION__,
//            ((kdtree_key_value_pair_t*)(p->value))->key.coordinates[*(uint32_t*)state],
//            ((kdtree_key_value_pair_t*)(p->next->value))->key.coordinates[*(uint32_t*)state]);
        p = p->next;
      }
    }
//    LN_KD_print(*l);
  } while(check);

//  printf("%s END: {axis: %u}\n", __PRETTY_FUNCTION__, *(uint32_t*)state);

  return 0;
}

void LN_swap (list_node_t *a, list_node_t *b) {
#ifdef LN_VALUE_IS_POINTER

  LN_value_t tmpv;

#else

  list_node_t *tmp;

#endif

  if (!a || !b) return;

#ifdef LN_VALUE_IS_POINTER

  tmpv = a->value;
  a->value = b->value;
  b->value = tmpv;

#else

  if (a->prev) a->prev->next = b;
  if (b->next) b->next->prev = a;
  tmp = b->prev;
  b->prev = a->prev;
  a->prev = tmp;
  tmp = a->next;
  a->next = b->next;
  b->next = tmp;

#endif

}

size_t LN_length(const list_node_t * const l) {
  size_t len = 0;
  const list_node_t *p = l;
  while (p) { len++; p = p->next; }
  return len;
}

void LN_KD_print(const list_node_t * const l) {
  const list_node_t * p = l;
  char *str = NULL;
  printf("%s: BEGIN\n", __PRETTY_FUNCTION__);
  while (p) {
    printf("{ key: { coordinates: [%lu, %lu]}, value: %lu}\n",
        ((const kdtree_key_value_pair_t*)(p->value))->key.coordinates[0],
        ((const kdtree_key_value_pair_t*)(p->value))->key.coordinates[1],
        ((const kdtree_key_value_pair_t*)(p->value))->value);
    p = p->next;
  }
  printf("%s: END\n", __PRETTY_FUNCTION__);
}

