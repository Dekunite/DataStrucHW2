/* @Author
Student Name: <Muhammet Derviş Kopuz>
Student ID : <504201531>
Date: <date> */
#include <iostream>
#include <stdlib.h>
#include <strings.h>
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
  bool search(char*);
  void add_resistor(char, int);
  int remove_resistor(char, int);
  void delete_resistor(char);
  void circuit_info();
  void clear();
};

void Circuit::create(){
  head = NULL;
}

bool Circuit::search(char* group) {

  Resistor* traverse;
  int counter = 0;
  bool found = false;
  traverse = head;

  while (traverse)
  {
    counter++;
    if (strncasecmp(&traverse->group, group, 1) == 0)
    {
      found = true;
      cout << counter << ":" << traverse->group << endl;
      traverse->quantity++;
    }
    traverse = traverse->next;
  }
  return found;
}

void Circuit::add_resistor(char group, int value){
  Resistor *newResistor = new Resistor;
  
  Resistor* ptr = Circuit::head;
  while (ptr->next != Circuit::head)
  {
    /* code */
  }
  

  newResistor->group = group;
  newResistor->value = value;
  newResistor->quantity = 1;
  newResistor->next = NULL;
  //prev resistors next should point to newResistor
}

int Circuit::remove_resistor(char, int){
  return 0;
}

void Circuit::delete_resistor(char){

}

void Circuit::circuit_info(){

}

void Circuit::clear(){

}


int main(){

  ifstream circuitFile("input.txt");

  Circuit circuit;
  circuit.create();

  Resistor *resistor1 = new Resistor;
  char testGroup[] = "A";
  resistor1->group = *testGroup;
  resistor1->value = 3.5;
  resistor1->quantity = 1;
  resistor1->next = NULL;
  circuit.head = resistor1;

  /*fstream circuitInput;
  circuitInput.open("input.txt");
  circuitInput.open("input.txt", fstream::in | fstream::binary);
  if (!circuitInput.is_open())
	{
		circuitInput.open("input.txt", fstream::out | fstream::binary);
		if (!circuitInput.is_open())
		{
			cerr << "Cannot open file";
			exit(1);
		}
	}
  else{

    circuitInput >> group >> value;
    //while (!circuitInput.eof())
    //{
    //cout << *group << &value;
    //}
    
  }
  */
  
  
  int i = 0;
  char group[1];
  double value;
  while (circuitFile >> group >> value)
  {
    cout << group << value << endl;
    if (value > 0)
    {
      //traverse circuit by group
      //if group exists increase quantity by 1
      bool incResistorQuantity = circuit.search(group);

      //if group does not exist 
      if (!incResistorQuantity)
      {
        circuit.add_resistor(*group, value);

      }
      
      //circuit.add_resistor(); 


    } else if (value < 0)
    {
      /* code */
    } else
    {
      /* code */
    }
    
    
    
    newResistor->group = *group;
    newResistor->value = value;
    newResistor->quantity = 1;
    newResistor->next = circuit.head;

    cout << group << value << endl;
    cout << newResistor->group << endl;
    cout << newResistor->value << endl;
  }
  cout << "no while";
  
  
  
    
    
  
  
  

  return 1;
}




