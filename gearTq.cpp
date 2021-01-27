#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class vehicleProfile {
    public:
        string vName;
        int peakTrq;
        int rpm;
        double gear[6];
        double final;
        double wheelTq[6];
        double wheelForce[6];
} vehicle;

//Function prototypes.
void dataWrite();
void dataRead();
void wheelForce();
double wheelSize();
void powerCalc();
void display();

int main() {
  int i; //Used in for loop.
  int choice; //Reserved for main menu.

  cout << "==================================================================\n";
  cout << "|                        GEARTORQUE C++!                         |\n";
  cout << "|                        by metal.hp                             |\n";
  cout << "==================================================================\n";
  cout << "Welcome to gT, a c++ fork!" << endl;
  cout << "Once again, this program comes raw. ( ͡° ͜ʖ ͡°)" << endl;

  while(choice != 5) {
    cout << "|=======================| MAIN MENU |============================|\n";
    cout << "[1] Create a new vehicle profile.\n";
    cout << "[2] Read current vehicle data.\n";
    cout << "[3] Calculate engine power output.\n";
    cout << "[4] Calculate torque output.\n";
    cout << "[5] Exit\n";
    cout << ">> "; cin >> choice;
    if((choice < 1) || (choice > 5))
      cout << "Error: choice number " << choice << " is not valid!" << endl;
    else if(choice < 5) {
      if(choice  == 1)
        dataWrite();
      else if(choice == 2)
        dataRead();
      else if(choice == 3)
        powerCalc();
      else if(choice == 4)
        wheelForce();
    }
  }
  cout << "Bye-bye!\n";
}

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
  const int magicNumber = 9550;
  double pwr, pawn;

  cout << "\nEngine peak torque (Nm): "; cin >> vehicle.peakTrq;
  cout << "\nPeak torque at rpm: "; cin >> vehicle.rpm;

  pawn = vehicle.peakTrq * vehicle.rpm;
  pwr = pawn / magicNumber;

  cout << "Output: " << pwr << "kW" << endl;
}

//Function that calculates wheel radius based on tire marking input by user.
//Returns radio in millimeters.
double wheelSize() {
  int aspectRatio, tireWidth, rimDiameter;
  double height, wheelDiam;
  double radius, r;

  cout << "\nTire size marking: "; cin >> tireWidth;
  cout << "/"; cin >> aspectRatio; cout << "R"; cin >> rimDiameter;

  height = (aspectRatio * tireWidth) / 100;
  wheelDiam = (rimDiameter * 25.4) + 2 * height; //25.4 converts from in to mm.
  r = 0.95 * wheelDiam / 2; //Coefficient assumes 5% tire deformation.
  radius = r / 1000; //For meter output.

  return radius;
}

//Our main program, calculates torque and rolling force transmited from engine,
//through gear ratios.
void wheelForce() {
  int i;
  double wheelR, wheelF, Nm;

  wheelR = wheelSize();

  cout << "Max engine torque output (Nm): \n"; cin >> Nm;
  cout << "Input your gear ratios. \n";
  for(i = 1; i <= 5; i++) {
    cout << "Gear " << i << " ";
    cin >> vehicle.gear[i];
  }
  cout << "Final drive: "; cin >> vehicle.final;
  for(i = 1; i <= 5; i++) {
    //Torque at center hub.
    vehicle.wheelTq[i] = (vehicle.gear[i] * vehicle.final * Nm) / 2;
    //Torque on contact patch.
    vehicle.wheelForce[i] = (vehicle.gear[i] * vehicle.final * Nm) / (wheelR * 2);

  }
  display();
}

void display() {
  int i;
  cout << "Peak torque |=====================================================\n";
  for(i = 1; i <= 5; i++) {
    cout << "Gear " << i << ": " << vehicle.wheelTq[i] << "Nm\t" << vehicle.wheelForce[i] << "N\n";
  }
}

void dataWrite() {
  char choice = '\0';
  int i;

  cout << "======| New vehicle profile function |==============================" << endl;
  cout << "\nVehicle name: "; cin >> vehicle.vName;
  cout << "\nPeak torque: "; cin >> vehicle.peakTrq;
  cout << "\nTorque RPM: "; cin >> vehicle.rpm;
  cout << "\nGear ratios...\n";
  for(i = 1; i <= 5; i++) {
    cout << "Gear " << i << ": ";
    cin >> vehicle.gear[i];
  }
  cout << "\nFinal drive ratio: "; cin >> vehicle.final;

  while(choice != 'y' && choice != 'n') {
    cout << "Is this information correct (y/n)?\n>> "; cin >> choice;
    if(choice != 'y' && choice != 'n') {
      cout << "\nError: " << choice << " is not a valid choice" << endl;
    }

    if(choice == 'n');

    else if(choice == 'y') { //Should open the same file and append.
    ofstream file("vehicleData.txt", ios::app);
      if(file.fail())
        cout << "Could not open file!" << endl;
      file << "Stored vehicle data." << endl;
      file << "Vehicle name:      " << vehicle.vName << endl;
      file << "Peak torque:       " << vehicle.peakTrq <<endl;
      file << "Torque RPM:        " << vehicle.rpm << endl;
      file << "Gear ratios...     " << endl;
      for(i = 1; i <= 5; i++)
        file << "Gear " << i << ": " << vehicle.gear[i] << endl;
      file << "Final drive ratio: " << vehicle.final << endl;
      file.close();
      }
   }
}

//Reads data from file.
void dataRead() {
  char choice;
  string line;

  ifstream file("vehicleData.txt", ios::in);
  if(file.fail())
    cout << "Could not open file!\n";
  while(getline(file, line))
    cout << line << endl;
  file.close();
  while(choice != 'c') {
    cout << "Press 'c' to continue..." << endl; cout << ">> "; cin >> choice;
  }
}
