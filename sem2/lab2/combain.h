#ifndef common_h
#define common_h

#ifdef FLAG
	#include "list.h"
#else 
	#include "vector.h"
#endif

#include "data.h"

typedef struct UNITE{
	#ifdef FLAG
		QUEUE_FOR_LIST cont;
	#else
		QUEUE_FOR_VECTOR cont;
	#endif
}UNITE;

typedef struct{
	UNITE* conteiner;
}QUEUE;

void popqueue(UNITE* q, int time);

void pushqueue(UNITE* q, dpas* pq, int time);

UNITE* initqueue(UNITE* q, int g);

void deletequeue(UNITE* q);

int checkqueue(UNITE* q);

#endif
