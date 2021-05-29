#include <stdio.h>
#include <stdlib.h>

#include <list_node.h>
#include <kdtree.h>

#define N 20

typedef uint64_t actual_list_value_t;

#define ACTUAL_LIST_VALUE_IS_NUMBER


//int cmp(const list_node_t * const a, const list_node_t * const b) {
int cmp(const LN_value_t * const a, const LN_value_t * const b, void*state) {
  if (!a || !b) return 0;

#ifdef LN_VALUE_IS_POINTER

  if (!*a || !*b) return 0;

#ifdef ACTUAL_LIST_VALUE_IS_NUMBER

  return ((**(actual_list_value_t**)(a)) - (**(actual_list_value_t**)(b)));

#else

  fprintf(stderr, "ERROR: ACTUAL_LIST_VALUE_IS_NUMBER is not defined (1)\n");
  return 0;

#endif

#else

#ifdef ACTUAL_LIST_VALUE_IS_NUMBER

  return (*a) - (*b);

#else

  fprintf(stderr, "ERROR: ACTUAL_LIST_VALUE_IS_NUMBER is not defined (2)\n");
  return 0;

#endif

#endif

}


int main () {
  list_node_t *p, *l=NULL;
  kdtree_node_t *kd = NULL;
  size_t i = 0;
  int ERR_CODE;
//  for (i=0; i<N; i++) {
//    actual_list_value_t *v = (uint64_t*)malloc(sizeof(uint64_t));
//    if (!v) {
//      fprintf(stderr, "ERROR: memory allocation error\n");
//      while(!LN_pop_back(&l)) {};
//    }
//    *v = N - i;
//    if ((ERR_CODE = LN_push_back(&l, v))) {
//      fprintf(stderr, "ERROR: LN_push_back returned %d\n", ERR_CODE);
//      while (!LN_pop_back(&l)) {};
//      return 0;
//    }
//  }
//
//  p = l;
//  while (p) {
//    printf("%lu ", *((actual_list_value_t*)(p->value)));
//    p = p->next;
//  }
//  printf("\n");
//
//  LN_sort(&l, cmp, NULL);
//
//  p = l;
//  while (p) {
//    printf("%lu ", *((actual_list_value_t*)(p->value)));
//    p = p->next;
//  }
//  printf("\n");
//
//  while(!LN_pop_back(&l)) {};


  for (i = 0; i < N; i++) {
    kdtree_key_value_pair_t *pair = (kdtree_key_value_pair_t*)malloc(sizeof(kdtree_key_value_pair_t));
    if (!pair) {
      fprintf(stderr, "ERROR: memory allocation error\n");
      while (!LN_pop_back(&l)) {};
      return 0;
    }
    pair->key.coordinates[0] = N-i;
    pair->key.coordinates[1] = i;
    pair->value = i*i;

    if ((ERR_CODE = LN_push_back(&l, pair))) {
      fprintf(stderr, "ERROR: LN_push_back returned %d\n", ERR_CODE);
      while (!LN_pop_back(&l)) {};
      return 0;
    }
  }

  kdtree_build(&kd, &l, 0);

  printf("\n\n---------------------\n\n");

  kdtree_print(kd);

  kdtree_free(&kd);

//  while(!LN_pop_back(&l)) {};

  return 0;
}

