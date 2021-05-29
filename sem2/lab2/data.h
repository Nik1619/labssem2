#ifndef data_h
#define data_h

typedef struct dpas{
	char* id;
	int ta;
	int ts;
	struct dpas* next;
}dpas;

typedef struct data{
	int lengh;
	dpas* first;
}data;

data* newdata(data* l);

void deletedata(data* l);

#endif 
