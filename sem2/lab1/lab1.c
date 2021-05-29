#include <stdio.h>
#include <stdlib.h>

typedef struct Line{
  int n; 
  double *a; 
} Line;

typedef struct Matrix{
  int lines;
  Line *matr;
} Matrix;

int getInt(int *);
int getDouble(double *);
int input(Matrix *a);
void output(const char *msg, Matrix a);
void erase(Matrix *a);
double minmax(Matrix a); 
double max(double a[], int m); 

int main(){
  Matrix matr = {0, NULL};
  double res;
  if (input(&matr) == 0){
    printf("%s\n", "End of file occured");
    return 1;
  }
  res = minmax(matr);
  output("Source matrix", matr);
  erase(&matr);
  return 0;
}

int getInt(int *a){
  int n;
  do{
    n = scanf("%d", a);
    if (n < 0) 
      return 0;
    if (n == 0){ 
      printf("%s\n", "Error! Repeat input");
      scanf("%*c");
    }
  } while (n == 0);
  return 1;
}

int getDouble(double *a){
  int n;
  do{
    n = scanf("%lf", a);
    if (n < 0) 
      return 0;
    if (n == 0){ 
      printf("%s\n", "Error! Repeat input");
      scanf("%*c");
    }
  } while (n == 0);
  return 1;
}

int input(Matrix *rm){
  const char *pr = ""; 
  int m; 
  int i, j;
  double *p;
  do{
    printf("%s\n", pr);
    printf("Enter number of lines: --> ");
    pr = "You are wrong; repeat, please!";
    if(getInt(&m) == 0)
      return 0; 
  } while (m < 1);
  rm->lines = m;
  rm->matr = (Line *)calloc(m, sizeof(Line));
  for (i = 0; i < rm->lines; ++i){
    pr = "";
    do{
      printf("%s\n", pr);
      printf("Enter number of items in line %d: --> ", i + 1);
      pr = "You are wrong; repeat, please!";
      if (getInt(&m) == 0){
        rm->lines = i; 
        erase(rm);
        return 0; 
      }
    } while (m < 1);
    rm->matr[i].n = m;
    p = (double *)malloc(sizeof(double)* m);
    rm->matr[i].a = p;
    printf("Enter items for matrix line #%d:\n", i + 1);
    for (j = 0; j < m; ++j, ++p)
      if (getDouble(p) == 0){
        rm->lines = i + 1;
        erase(rm);
        return 0;
      }
  }
  return 1;
}

void output(const char *msg, Matrix a){
  int i, j;
  double *p;
  printf("%s:\n", msg);
  for (i = 0; i < a.lines; ++i){
    p = a.matr[i].a;
    for (j = 0; j < a.matr[i].n; ++j, ++p)
    printf("%lf ", *p);
  printf("\n");
  }
}

void erase(Matrix *a){
  int i;
  for (i = 0; i < a->lines; ++i)
    free(a->matr[i].a);
  free(a->matr);
  a->lines = 0;
  a->matr = NULL;
}

double printvector(Matrix pm){
  double res;
  int *array, i;
  array = malloc(pm.lines * sizeof(int));
  for (i = 0; i < pm.lines; ++i){
    array[i] = max(pm.matr[i].a, pm.matr[i].n);
    printf("%d ", array[i]);
  }
  free(array);
  return 0;
}

double max(double a[], int m){
  int k, res = 0, r = 0;
  for (int i = 0; i < m; i++){
    k = 1;
    for(int j = 0; j < m; j++)
      if ((a[i]!=0) && (a[i] == a[j])) k++;
    if (k > res) res = k;
  }
  res--;
  return res;
}
