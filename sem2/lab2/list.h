#ifndef list_h
#define list_h

#include "data.h"


typedef struct passenger_l{
	char* id;
	int ta;
	int ts;
	struct passenger_l* next;
}pas_l;

typedef struct stand_l{
	int lengh;
	int time;
	pas_l* pass;
	pas_l* first;
	pas_l* last;
}stand_l;

typedef struct QUEUE_FOR_LIST{
	int sts;
	stand_l* st;
}QUEUE_FOR_LIST;

int pushlist(QUEUE_FOR_LIST* q, dpas* pq, int time);

void poplist(QUEUE_FOR_LIST* q, int time);

void readlist(QUEUE_FOR_LIST* q, int time);

void deletelist(QUEUE_FOR_LIST* q);

QUEUE_FOR_LIST* initlist(QUEUE_FOR_LIST* q, int g);

int checklist(QUEUE_FOR_LIST* q);

#endif
