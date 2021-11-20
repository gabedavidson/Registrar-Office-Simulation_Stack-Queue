#include "RegistrarOffice.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
  string file;
  if (argc > 0){
    try{
      file = argv[1];
      RegistrarOffice office(file);
      office.simulate();
    }
    catch (...){
      cout << "\nThat file was not found. Running with default testing file." << endl;
      file = "default.txt"; // <<< if inputted file is not found, will run off of this file
      RegistrarOffice office(file);
      office.simulate();
    }
  }
  else {
    cout << "Please enter the location of your file as a command line argument." << endl;
  }
}
