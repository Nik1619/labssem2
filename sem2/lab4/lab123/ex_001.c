#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef uint64_t LN_value_t;

struct list_node {
  struct list_node *prev, *next;
  LN_value_t value;
};

//int LN_add(list_node **l, LN_value v){
//  if (!l) return 1;
//  if (!*l) {
//    *l = (list_node*)malloc(sizeof(list_node));
//    if (!*l) return 2;
//    (*l)->prev = NULL;
//    (*l)->next = NULL;
//    l.prev
//  } else {
//  }
//  return 0;
//}

int main() {
//  list_node *l = NULL;
//  LN_add(&l, 10);
  struct list_node l1;
  struct list_node *l2 = (struct list_node*)malloc(sizeof(struct list_node));
  if (l2) {
    printf("Hello there\nl1.value = %llu\nl2->value = %llu\n", l1.value, l2->value);
    free(l2);
  }
	return 0;
}
