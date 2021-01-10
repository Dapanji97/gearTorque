//Display and compare actual and projected power outputs.

#include <stdio.h>
#include <stdlib.h>

void display(double torque, double force) {
  printf("== PEAK TORQUE ==================================================\n");
  printf("             SCENARIO 1          |           SCENARIO 2          \n");
  printf("=================================================================\n");
  printf("|G1|     %.3lfNm       %.3lfN    |                              |\n");
  printf("|G2|     %.3lfNm       %.3lfN    |                              |\n");
  printf("|G3|     %.3lfNm       %.3lfN    |                              |\n");
  printf("|G4|     %.3lfNm       %.3lfN    |                              |\n");
  printf("|G5|     %.3lfNm       %.3lfN    |                              |\n");
  printf("=================================================================\n");
}

//To be place in another function====================================
printf("Gear %d: %.2lfNm\n", i, Output.wheelTorque[i]);
printf("Wheel force: %lfN\n", Output.wheelForce[i]);
//===================================================================
