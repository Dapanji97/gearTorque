#include <stdio.h>
#include <stdlib.h>

double wheelSize();

void main() {
  double wheelr;

  wheelr = wheelSize();

  printf("wheelsize function returns: %lf \n", wheelr);

  return;
}

//Function that calculates wheel radius based on tire marking input by user.
//Returns radio in millimeters.
double wheelSize() {
  int aspectRatio, tireWidth, rimDiameter;
  double height, wheelDiam;
  double radius, r;

  printf("\n");
  printf("Tire size marking:"); //BUGGY! use conditional statement.
  scanf("%d%*c%d%*c%d", &tireWidth, &aspectRatio, &rimDiameter);
  printf("\n");

  height = (aspectRatio * tireWidth) / 100;
  wheelDiam = (rimDiameter * 25.4) + 2 * height; //25.4 convert from inches to mm
  r = wheelDiam / 2;
  radius = r / 1000; //For meter output.

  return radius;
}
