/A function that calculates engine power output.
//Given Torque, and crankshaft speed.
//Units are in metric, imperial later to be implented.
/* According to wikipedia...
   P = M * n / 9550
   Where P = power (kW)
         M = torque (Nm)
         n = crankshaft speed, also...
           n = angular velocity / (2*pi)
*/

int powerF(double m, double n) {
  int magicNumber = 9550;
  double pwr, pawn;

  pawn = m * n;
  pwr = pawn / magicNumber;

  return pwr;
}
