#include "data.h"
#include "combain.h"
#include <stdio.h>
int main(int argc, char const* argv[]){
	int g;
	data* l = newdata(l);
	dpas* pq = l->first;
	printf("Enter number of stands: ");
	scanf("%d", &g);
	if (g == 0) return 1;
	UNITE* q = initqueue(q, g); 
	int time = 1, z = 0;
    	while(pq || z){
		if (time > 1){
			popqueue(q, time);
		}
		while (pq && pq->ta == time){
			pushqueue(q, pq, time);
			pq = pq->next;
		}
		z = checkqueue(q);
		time ++;
	}
	deletedata(l);
	deletequeue(q);
	printf("Good bye\n");
	return 0;
}
