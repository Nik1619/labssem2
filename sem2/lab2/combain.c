#include "combain.h"
#include "data.h"
#include <stdlib.h>
#ifdef FLAG
	#include "list.h"
#else
	#include "vector.h"
#endif
void popqueue(UNITE* q, int time){
	#ifdef FLAG
		poplist(&q->cont, time);
	#else 
		popvector(&q->cont, time);
	#endif
}
void pushqueue(UNITE* q, dpas* pq, int time){
	#ifdef FLAG
		pushlist(&q->cont, pq, time);
	#else 
		pushvector(&q->cont, pq, time);
	#endif
}
void deletequeue(UNITE* q){
	#ifdef FLAG
		deletelist(&q->cont);
	#else
		deletevector(&q->cont);
	#endif
}
int checkqueue(UNITE* q){
	int z;
	#ifdef FLAG
		z = checklist(&q->cont);
	#else 
		z = checkvector(&q->cont);
	#endif
	return z;
}
UNITE* initqueue(UNITE* q, int g){
  q = (UNITE *)malloc(sizeof(UNITE));
	#ifdef FLAG
		q->cont = *initlist(&q->cont, g);
	#else 
		q->cont = *initvector(&q->cont, g);
	#endif
	return q;
}
void deletecont(UNITE* q){
	free(q);

}
