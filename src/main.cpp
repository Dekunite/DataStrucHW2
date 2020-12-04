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
  float value;
  int quantity;
  Resistor *next;
};

struct Circuit{
  Resistor *head;
  void create();
  Resistor* search(char*, float);
  void add_resistor(Circuit*, char, float);
  int remove_resistor(char, float);
  void delete_resistor(char);
  void circuit_info();
  void clear();
};

void Circuit::create(){
  head = NULL;
}

Resistor* Circuit::search(char* group, float value) {

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
          return traverse;
        }
        traverse = traverse->next;
      }
      return NULL;
  } else  //value = 0
  {
    
  }
  
  
  return NULL;
}

void Circuit::add_resistor(Circuit* circuit,char group, float value){
  Resistor *newResistor = new Resistor;
  
  newResistor->group = group;
  newResistor->value = value;
  newResistor->quantity = 1;
  newResistor->next = NULL;

  if (head == NULL)
  {
    head = newResistor;
  }
  

  Resistor* predecessor = Circuit::head;
  Resistor* ptr = Circuit::head;
  while (ptr->next != NULL && ptr->group < newResistor->group) {
    predecessor = ptr;
    ptr = ptr->next;
  }

  if (ptr->group < newResistor->group)
  {
    ptr->next = newResistor;
  } else if (ptr->group > newResistor->group) {
    newResistor->next = ptr;
    predecessor->next = newResistor;
  }
  
  
  

  //prev resistors next should point to newResistor
}

int Circuit::remove_resistor(char group, float value){

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
  Resistor* traverse = head;
  Resistor* predecessor;
  Resistor* infoTraverse;
  Resistor* infoList = new Resistor;
  Circuit* infoCircuit = new Circuit;
  infoCircuit->head = NULL;

  while (traverse)
  {
    Resistor* newResistor = new Resistor;
    infoTraverse = infoCircuit->head;
    predecessor = NULL;

    newResistor->value = traverse->value;
    newResistor->quantity = traverse->quantity;
    newResistor->group = traverse->group;
    newResistor->next = NULL;

    if (infoCircuit->head == NULL)
    {
      predecessor = newResistor;
      traverse = traverse->next;
      infoCircuit->head = newResistor;
      continue;
    }
    
    while (infoTraverse->next != NULL && infoTraverse->value < newResistor->value) {
        predecessor = infoTraverse;
        infoTraverse = infoTraverse->next;

      } 

      if (infoTraverse->value < newResistor->value)
      {
        infoTraverse->next = newResistor;
      } else if ( infoTraverse->value > newResistor->value) {
        newResistor->next = infoTraverse;
        if (predecessor == NULL)
        {
          infoCircuit->head = newResistor;
        } else {
          predecessor->next = newResistor;
        }
        
      }

    traverse = traverse->next;
  }
  //print infoCircuit
  infoTraverse = infoCircuit->head;
  float totalResistance = 0;
  while (infoTraverse)
  {
    cout << infoTraverse->value << ":" << infoTraverse->quantity << endl;
    totalResistance = totalResistance + (infoTraverse->value / infoTraverse->quantity);
    infoTraverse = infoTraverse->next;
  }
  cout << "Total Resistance=" << totalResistance << " ohm" << endl;
  
    

}
  

void Circuit::clear(){

}


int main(){

  ifstream circuitFile("input.txt");

  Circuit *circuit = new Circuit;
  circuit->create();

  

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
  char group;
  float value;
  while (circuitFile >> group >> value)
  {
    //cout << group << " " << value << endl;
    
    if (value > 0)
    {
      //traverse circuit by group
      //if group exists increase quantity by 1
      Resistor* searchResponse = circuit->search(&group, value);

      //if group does not exist 
      if (searchResponse == NULL)
      {
        circuit->add_resistor(circuit, group, value);

      } else{
        searchResponse->quantity++;
      }
      

    } else if (value < 0){

      Resistor* searchResponse = circuit->search(&group, value);
      
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
      
      

    } else if (group == 'A' && value == 0)
    {
      circuit->circuit_info();
    }
    
    
  }
  cout << "no while";
  
  
  
    
    
  
  
  

  return 1;
}




