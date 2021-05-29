#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "data.h"

void poplist(QUEUE_FOR_LIST* q, int time){
	stand_l* a = q->st;
	for (int r = 0; r < q->sts; r ++){
		while (a[r].lengh > 0 && a[r].time + a[r].first->ts == time){
			pas_l* p = a[r].first;
			a[r].first = p->next;
			a[r].lengh--;
			a[r].time = time;
			free(p);
			p = NULL;
			readlist(q, time);
		}
        }
}

QUEUE_FOR_LIST* initlist(QUEUE_FOR_LIST* q, int g){
	q->sts = g;
	q->st = (stand_l *)malloc(q->sts * sizeof(stand_l));
	for (int i = 0; i < g; i ++){
		q->st[i].lengh = 0;
		q->st[i].pass = (pas_l *)malloc(g*sizeof(pas_l));
	}
	return q;
}

void readlist(QUEUE_FOR_LIST* q, int time){
	printf("Time is №%d.\n", time);
	for (int i = 0; i < q->sts; i ++){
		printf("#%d: ", i + 1);
		if (q->st[i].lengh > 0){
			pas_l* pq = q->st[i].first;
			for (int j = 0; j < q->st[i].lengh; j ++){
				printf("%s ", pq->id);
				pq = pq->next;
			}	
		}
		printf("\n");
	}
	printf("\n");
}

int pushlist(QUEUE_FOR_LIST* q, dpas* pq, int time){
	int k = 100000, r;
        for (int l = 0; l < q->sts; l++){
                if (q->st[l].lengh < k){
                	k = q->st[l].lengh;
                  	r = l;
                }
        }
	printf("%s\n", pq->id);
	q->st[r].pass->id = pq->id;
	q->st[r].pass->ta = pq->ta;
	q->st[r].pass->ts = pq->ts;
	if (q->st[r].lengh == 0){
		q->st[r].first = q->st[r].pass;
		q->st[r].time = pq->ta;
	}
	q->st[r].lengh += 1;
	q->st[r].last = q->st[r].pass;
	q->st[r].pass->next = (pas_l *)malloc(sizeof(pas_l));
	q->st[r].pass = q->st[r].pass->next;
	readlist(q, time);
	return 0;
}

int checklist(QUEUE_FOR_LIST* q){
	for (int v = 0; v < q->sts; v ++){
			if (q->st[v].lengh > 0){
				return 1;
			}
	}
	return 0;
}

void deletelist(QUEUE_FOR_LIST* q){
	for (int i = 0; i < q->sts; i ++){
		free(q->st[i].first);
	}
	free(q->st);
	free(q);
}
