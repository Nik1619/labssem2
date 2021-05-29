#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"
#include "vector.h"


QUEUE_FOR_VECTOR* initvector(QUEUE_FOR_VECTOR* q, int g){
	q->sts = g;
	q->st = (stand_v *)malloc(g * sizeof(stand_v));
	for (int i = 0; i < g; i ++){
		q->st[i].pass = (pas_v *)malloc(sizeof(pas_v) * 2);
		q->st[i].lengh = 0;
	}
	return q;
}

int pushvector(QUEUE_FOR_VECTOR* q, dpas* pq, int time){
	int k = 100000, r;
        for (int l = 0; l < q->sts; l++){
        	if (q->st[l].lengh < k){
                	k = q->st[l].lengh;
                  	r = l;
                }
        }

	if (q->st[r].lengh == 0) q->st[r].time = pq->ta;
	q->st[r].pass[q->st[r].lengh].id = pq->id;
	q->st[r].pass[q->st[r].lengh].ta = pq->ta;
	q->st[r].pass[q->st[r].lengh].ts = pq->ts;
	q->st[r].lengh ++;
	readvector(q, time);
	return 0;
}

void popvector(QUEUE_FOR_VECTOR* q, int time){
	for (int r = 0; r < q->sts; r ++){
		while (q->st[r].lengh > 0 && q->st[r].time + q->st[r].pass[0].ts == time){
			q->st[r].time = time;
			for (int i = 0; i < q->st[r].lengh - 1; i ++){
				q->st[r].pass[i] = q->st[r].pass[i + 1];
			}
			
			q->st[r].lengh --;
			readvector(q, time);
		}
  }
}

void readvector(QUEUE_FOR_VECTOR* q, int time){
	printf("Time is №%d.\n", time);
	for (int i = 0; i < q->sts; i ++){
		printf("#%d: ", i + 1);
		if (q->st[i].lengh > 0){
			for (int j = 0; j < q->st[i].lengh; j ++){
				printf("%s ", q->st[i].pass[j].id);
			}	
		}
		printf("\n");
	}
	printf("\n");
}

void deletevector(QUEUE_FOR_VECTOR* q){
	for (int i = 0; i < q->sts; i ++){
		free(q->st[i].pass);
	}
	free(q->st);
	free(q);
}

int checkvector(QUEUE_FOR_VECTOR* q){
	for (int v = 0; v < q->sts; v ++){
			if (q->st[v].lengh > 0){
				return 1;
			}
	}
	return 0;
}
