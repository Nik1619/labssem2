#ifndef vector_h
#define vector_h

#include "data.h"

typedef struct passenger_v{
	char* id;
	int ta;
	int ts;

}pas_v;

typedef struct stand_v{
	int lengh;
	int time;
	pas_v* pass;

}stand_v;

typedef struct QUEUE_FOR_VECTOR{
	int sts;
	stand_v* st;
}QUEUE_FOR_VECTOR;

void deletevector(QUEUE_FOR_VECTOR* q);
void popvector(QUEUE_FOR_VECTOR* q, int time);
int pushvector(QUEUE_FOR_VECTOR* q, dpas* pq, int time);
void readvector(QUEUE_FOR_VECTOR* q, int time);
int checkvector(QUEUE_FOR_VECTOR* q);
QUEUE_FOR_VECTOR* initvector(QUEUE_FOR_VECTOR* q, int g);
#endif 
