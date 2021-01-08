//gearTork calculates and tracks torque within an automotive power train.
//Program takes in motor (electric or gas) peak torque output, amount of gears
//and their respective ratios.
//Dec 27, 2020
//B, metalHp.

#include <stdio.h>
#include <stdlib.h>

struct pTrain { //Power train specifications (actual)
  int peakTrk;
  int rpm; //This is the rpm where max torque occurs, not max rpm.
  double g[6]; //g1-5 is for each gear in a 5 speed transmission.
  double final; //Final drive or differential ratio.
} pTrain;

struct Output { //Force output per gear.
  double wTorque[6];
  double wForce[6];
} Output;

//Function prototypes.
void wheelForce();
double wheelSize();
void powerCalc();
void display();

void main() {
  int i; //Used in For-loop.
  int choice; //Main menu choice.

  printf("=================================================================\n");
  printf("||                          GEARTORK2                          ||\n");
  printf("||                          By metalHp                         ||\n");
  printf("=================================================================\n");
  printf("Welcome user, to gearTork alpha!\n");
  printf("Here, our program focuses on its main purpose... doing math!\n");
  printf("This version will be rough and simple. Hope it helps!\n");
  printf("Bare in mind, values are received and given in metric standard!\n");

  while(choice != 3) {
    printf("|========================= Main menu =========================|\n");
    printf("[1] Calculate engine power output.\n");
    printf("[2] Calculate torque at the wheel.\n");
    printf("[3] Exit.\n");
    scanf("%d", &choice);

    if((choice < 1) && (choice > 3))
      printf("Error: number %d is not a valid choice.\n", choice);
    else if(choice < 3) {
      if(choice == 1)
        powerCalc();
      else if(choice == 2)
        wheelForce();
    } //conditional
  } //loop
  printf("Goodbye!!\n");
} //main

//A function that calculates engine power output.
//Given Torque, and crankshaft speed.
//Units are in metric, imperial later to be implented.
/* Knowing that...
   P = M * n / 9550
   Where P = power (kW)
         M = torque (Nm)
         n = crankshaft speed, also...
           n = angular velocity / (2*pi)
*/
void powerCalc() {
  int magicNumber = 9550;
  double pwr, pawn;

  printf("\n");
  printf("Engine peak torque Nm: ");
  scanf("%d", &(pTrain.peakTrk));
  printf("Peak torque speed RPM: ");
  scanf("%d", &(pTrain.rpm));

  pawn = pTrain.peakTrk * pTrain.rpm;
  pwr = pawn / magicNumber;

  printf("Output: %.2lfkW \n", pwr);
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
  wheelDiam = (rimDiameter * 25.4) + 2 * height; //25.4 convert from inches to mm.
  r = 0.95 * wheelDiam / 2;//Coefficient assumes 5% deformation due to curb weight.
  radius = r / 1000; //For meter output.

  return radius;
}

//Our main program, calculates torque and rolling force transmited from engine,
//through gear ratios.
void wheelForce() {
  int i;
  double wheelR, wheelF, Nm;

  printf("Max engine torque output (Nm): ");
  scanf("%lf", &Nm);
  printf("\n");
  printf("Input your gear ratios (5 speed only)\n");
  for(i = 1; i <= 5; i++) {
    printf("Gear %d: ", i);
    scanf("%lf", &pTrain.g[i]);
  }
  printf("Final drive: ");
  scanf("%lf", &pTrain.final);

  wheelR = wheelSize();

  for(i = 1; i <= 5; i++) {
    //Torque at the center hub.
    Output.wTorque[i] = (pTrain.g[i] * pTrain.final * Nm) / 2;
    //Force applied to contact patch.
    Output.wForce[i] = (pTrain.g[i] * pTrain.final * Nm) / (wheelR * 2);
  }
  display();
}

//Display and compare torque outputs.
void display() {
  printf("== PEAK TORQUE ===============================================|\n");
  printf("      SCENARIO 1                   SCENARIO 2             \n");
  printf("==============================================================|\n");
  printf("|G1|   %.3lf Nm   %.3lf N                                 \n", Output.wTorque[1], Output.wForce[1]);
  printf("|G2|   %.3lf Nm   %.3lf N                                 \n", Output.wTorque[2], Output.wForce[2]);
  printf("|G3|   %.3lf Nm   %.3lf N                                 \n", Output.wTorque[3], Output.wForce[3]);
  printf("|G4|   %.3lf Nm   %.3lf N                                 \n", Output.wTorque[4], Output.wForce[4]);
  printf("|G5|   %.3lf Nm   %.3lf N                                 \n", Output.wTorque[5], Output.wForce[5]);
  printf("==============================================================|\n");
}
