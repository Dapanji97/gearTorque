//Data management function.

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class students {
    public:
        string studentName;
        char grade;
        int age;
} student;
// Create array 'number[]' = student to keep track of list contents.

void dataWrite();
void dataRead();

int main() {
    int choice, i;

    while(choice != 3) {
        cout << "\n Welcome to my dang program. \n";
        cout << "[1] Create a new student profile." << endl;
        cout << "[2] List currently enrolled students." << endl;
        cout << "[3] Exit." << endl;
        cout << ">> "; cin >> choice;

        if(choice < 1 || choice > 3) {
            cout << "Error! " << choice << " is not a valid choice.";
            choice = 0;
        }
        else if(choice == 1)
          dataWrite();
        else if(choice == 2)
          dataRead();
    }
    cout << "Program terminated." << endl;
}

//Writes data to file.
void dataWrite() {
    char choice = '\0';

    cout << "New student enrollment function" << endl;
    cout << "\nStudent name: "; cin >> student.studentName;
    cout << "\nCurrent grade: "; cin >> student.grade;
    cout << "\nStudent age: "; cin >> student.age;

    while(choice != 'y' && choice != 'n') {
        cout << "Is this information correct (y/n)?\n>> "; cin >> choice;
        if(choice != 'y' && choice != 'n') {
            cout << "\nError: " << choice << " is not a valid choice" << endl;
        }

        if(choice == 'n');

        else if(choice == 'y') { //Should open the same file and append.
          ofstream file("studData.txt", ios::app);
          if(file.fail())
            cout << "Could not open file!" << endl;
          file << "Student name:  " << student.studentName << endl;
          file << "Current grade: " << student.grade << endl;
          file << "Age:           " << student.age << endl;
          file.close();
      }
   }
}

//Reads data from file.
void dataRead() {
  char choice;
  string line;
  ifstream file("studData.txt", ios::in);
  if(file.fail())
    cout << "Could not open file.";
  while(getline(file, line))
    cout << line << endl;
  file.close();
  while(choice != 'c') {
    cout << "Press 'c' to continue..." << endl; cout << ">> "; cin >> choice;
  }
}

