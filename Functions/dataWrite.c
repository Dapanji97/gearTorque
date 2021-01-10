#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pTrain { //Power train specifications (actual)
  char name[30]; //Stack overflow warning!
  int peakTrk;
  double final; //Final drive or differential ratio.
} car1, car2;

void main() {
  char name[20];

  printf("Name your car: ");
  printf("\n");
  scanf("%s", car1.name);
  printf("Name your second car: ");
  printf("\n");
  scanf("%s", car2.name);

  printf("Peak torque: ");
  scanf("%d", &car1.peakTrk);
  printf("\n");
  printf("Final drive ratio: ");
  scanf("%lf", &car1.final);
  printf("\n");

  printf("Testing string variable number 1: %s \n", car1.name);
  printf("Testing string variable number 2: %s \n", car2.name);

  printf("Name of new file: ");
  scanf("%s", name);
  FILE *fp;
  fp = fopen(name, "w+");
  if(fp == NULL) {
    printf("ERROR: File could not be opened!\n");
    exit(1);
  }

  fprintf(fp, "Vehicle 1:%s\tPeak torque:%d\tFinal drive ratio:%lf", car1.name, car1.peakTrk, car1.final);

  printf("Vehicle: %s has been saved to file.\n", car1.name);
}
