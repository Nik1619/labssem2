#include "data.h"
#include <stdlib.h>
#include <stdio.h>

data* newdata(data* l){
	l = (data *)calloc(1, sizeof(data));
	dpas* p = (dpas *)malloc(sizeof(dpas));
	int i = 0, t = 0;
	char c;
	printf("Enter id/ta/ts: ");
	scanf("%c", &c);
	do{
		p->id = (char *)malloc(sizeof(char));
		while (c != '/'){
			p->id[i] = c;
			i++;
			p->id = (char *)realloc(p->id, i + 1);
			scanf("%c", &c);
		}
		if (t == 0){
			l->first = p;
			t = 1;
		}
		i = 0;
		scanf("%d%*c%d", &p->ta, &p->ts);
		scanf("%c", &c);
		if (c != '\n'){
			scanf("%c", &c);
			p->next = (dpas *)malloc(sizeof(dpas));
			p = p->next;
		}
		else{
			p->next = NULL;
		}
	}while (c != '\n');
	return l;
}

void deletedata(data* l){
	dpas* pq = l->first;
	dpas* pp;
	while(pq){
		pp = pq->next;
		free(pq->id);
    free(pq);
    pq = pp;
	}
  free(pq);
	free(l);
}
