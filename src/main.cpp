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
  Resistor* search(char*, double);
  void add_resistor(Circuit*, char, int);
  int remove_resistor(char, int);
  void delete_resistor(char);
  void circuit_info();
  void clear();
};

void Circuit::create(){
  head = NULL;
}

Resistor* Circuit::search(char* group, double value) {

  Resistor* traverse;
  int counter = 0;
  bool found = false;
  traverse = head;

  if (value > 0)
  {
    while (traverse)
    {
      counter++;
      if (strncasecmp(&traverse->group, group, 1) == 0)
      {
        found = true;
        cout << counter << ":" << traverse->group << endl;
        //traverse->quantity++;
        return traverse;
      }
      traverse = traverse->next;
    }
    return NULL;
  } else if (value < 0){

      while (traverse) {

        counter++;
        if (strncasecmp(&traverse->group, group, 1) == 0) 
        {
          found = true;
          cout << counter << ":" << traverse->group << endl;
          return traverse;
        }
        traverse = traverse->next;
      }
      return NULL;
  } else  //value = 0
  {
    
  }
  
  
  
}

void Circuit::add_resistor(Circuit* circuit,char group, int value){
  Resistor *newResistor = new Resistor;
  
  newResistor->group = group;
  newResistor->value = value;
  newResistor->quantity = 1;
  newResistor->next = NULL;

  Resistor* ptr = Circuit::head;
  while (ptr->next != NULL && ptr->group < newResistor->group) {
    ptr = ptr->next;
  }

  ptr->next = newResistor;
  
  

  //prev resistors next should point to newResistor
}

int Circuit::remove_resistor(char group, int value){

  Resistor* ptr = Circuit::head;
  int needsDeletion = 0;

  while (ptr->next != NULL && !(ptr->group == group) && !(ptr->value == value))
  {
    ptr = ptr->next;
  }
  
  if (ptr->quantity == 1)
  {
    needsDeletion = 1;
    return needsDeletion;
  } else{
    ptr->quantity--;
  }
  return needsDeletion;
}

void Circuit::delete_resistor(char group){

  Resistor* predecessor;
  Resistor* ptr = Circuit::head;

  while (ptr->next != NULL && !(ptr->group == group))
  {
    predecessor = ptr;
    ptr = ptr->next;
  }

  predecessor->next = ptr->next;
  delete ptr;


   
}

void Circuit::circuit_info(){
  //circuit infoya başla

}

void Circuit::clear(){

}


int main(){

  ifstream circuitFile("input.txt");

  Circuit *circuit = new Circuit;
  circuit->create();

  Resistor *resistor1 = new Resistor;
  char testGroup[] = "A";
  resistor1->group = *testGroup;
  resistor1->value = 3.5;
  resistor1->quantity = 1;
  resistor1->next = NULL;
  circuit->head = resistor1;

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
      Resistor* searchResponse = circuit->search(group, value);

      //if group does not exist 
      if (searchResponse == NULL)
      {
        circuit->add_resistor(circuit, *group, value);

      } else{
        searchResponse->quantity++;
      }
      

    } else if (value < 0){

      Resistor* searchResponse = circuit->search(group, value);
      
      if (searchResponse == NULL)
      {
        cout << "NO_RESISTOR" << endl;
      } else
      {
        int needsDeletion = circuit->remove_resistor(searchResponse->group, searchResponse->value);

        if (needsDeletion)
        {
          circuit->delete_resistor(searchResponse->group);
        }
        

      }
      
      

    } else if (*group == 'A' && value == 0)
    {
      circuit->circuit_info();
    }
    
    
  }
  cout << "no while";
  
  
  
    
    
  
  
  

  return 1;
}




