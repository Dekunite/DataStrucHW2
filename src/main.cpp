/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <date> */
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include <fstream>


using namespace std;
struct Resistor{
  char group;
  double value;
  int quantity;
  Resistor *next;
};

struct Circuit{
  Resistor *head;
  void create();
  void add_resistor(char, int);
  int remove_resistor(char, int);
  void delete_resistor(char);
  void circuit_info();
  void clear();
};

void Circuit::create(){
  head = NULL;
}

void Circuit::add_resistor(char, int){

}

int Circuit::remove_resistor(char, int){

}

void Circuit::delete_resistor(char){

}

void Circuit::circuit_info(){

}

void Circuit::clear(){

}


int main(){

  Circuit circuit;
  circuit.create();
  ifstream circuitFile("input.txt");
  char group[1];
  double value;

  int i = 0;
  while (circuitFile >> group >> value)
  {
    Resistor* resistor = new Resistor();
  }
  
  
  
    
    
  
  
  


}




