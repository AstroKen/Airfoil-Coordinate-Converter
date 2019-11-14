#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{ 
  double *v;
  int dim;
} dvector;

void dvelloc(dvector*, size_t);
void freedvec(dvector*);

int main(int argc, char *argv[])
{
  FILE *fp, *sp;
  char *fileName;
  char *foilName;
  char command[256];
  int lineCount;
  char junk[256];

  dvector xv, yv, ans;

  if(argc != 3)
  {
    printf("Please input the file.\n");
    printf("You should type as\n\t$ ./airfoil naca4415.txt naca4415\n");
    exit(1);
  }

  fileName = argv[1];
  foilName = argv[2];
  sprintf(command, "wc -l %s > 010011101.txt\n", fileName);
  sp = popen(command, "w");
  if(sp == NULL)
  {
    printf("Couldn't count the line number of the file.\n");
    exit(1);
  }
  pclose(sp);
  fp = fopen("010011101.txt", "r");
  if(fp == NULL)
  {
    printf("Couldn't read the file.\n");
    exit(1);
  }
  fscanf(fp, "%d %s", &lineCount, junk);
  fclose(fp);
  fp = fopen("010011101.txt", "r");
  sp = popen("rm 010011101.txt\n", "r");
  pclose(sp);

  dvelloc(&xv, lineCount);
  dvelloc(&yv, lineCount);

  fp = fopen(fileName, "r");
  for(int i = 0; i < lineCount; i++)
  {
    fscanf(fp, "%lf\t%lf", &(xv.v[i]), &(yv.v[i]));
  }
  fclose(fp);

  for(int i = 13; i < 31; i++)
  {
    sprintf(command, "%s %d.txt", foilName, i * 2);
    fp = fopen(command, "w");
    for(int k = 0; k < lineCount; k++)
    {
      fprintf(fp, "%lf\t%lf\t0\n", xv.v[k] * i, yv.v[k] * i);
    }
    fclose(fp);
  }

  freedvec(&xv);
  freedvec(&yv);
  return 0;
}

void dvelloc(dvector *a, size_t dim)
{
  if(((*a).v = malloc(sizeof(double) * dim)) == NULL)
  {
    printf("Couldn't allocate memory\n");
    exit(1);
  }
  (*a).dim = dim;
}

void freedvec(dvector *a)
{
  free((*a).v);
} 


