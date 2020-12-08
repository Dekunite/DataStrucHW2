/* @Author
Student Name: Muhammet Derviş Kopuz
Student ID : 504201531
Date: <08/12/2020> */
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
  traverse = head;

  if (value > 0)
  {
    while (traverse)
    {
      if (strncasecmp(&traverse->group, group, 1) == 0)
      {
        //found = true;
        //traverse->quantity++;
        return traverse;
      }
      traverse = traverse->next;
    }
    return NULL;
  } else if (value < 0){

      while (traverse) {

        if (strncasecmp(&traverse->group, group, 1) == 0) 
        {
          //found = true;
          return traverse;
        }
        traverse = traverse->next;
      }
      return NULL;
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
  

  Resistor* predecessor = NULL;
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
    if (predecessor == NULL)
        {
          Circuit::head = newResistor;
        } else {
          predecessor->next = newResistor;
        }
  }
  
  
  

  //prev resistors next should point to newResistor
}

int Circuit::remove_resistor(char group, float value){

  Resistor* ptr = Circuit::head;
  int needsDeletion = 0;

  while (ptr->next != NULL && !(ptr->group == group) ) //&& !(ptr->value == value)
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

  Resistor* predecessor = NULL;
  Resistor* ptr = Circuit::head;

  while (ptr->next != NULL && !(ptr->group == group))
  {
    predecessor = ptr;
    ptr = ptr->next;
  }

  if (predecessor == NULL)
  {
    Circuit::head = ptr->next;
  } else
  {
    predecessor->next = ptr->next;
  }

  delete ptr;

}

void Circuit::circuit_info(){
  //circuit infoya başla
  Resistor* traverse = head;
  Resistor* predecessor;
  Resistor* infoTraverse;
  Circuit* infoCircuit = new Circuit;
  infoCircuit->head = NULL;

  float totalResistance = 0;

  while (traverse)
  {
    Resistor* newResistor = new Resistor;
    infoTraverse = infoCircuit->head;
    predecessor = NULL;

    newResistor->value = traverse->value;
    newResistor->quantity = traverse->quantity;
    newResistor->group = traverse->group;
    newResistor->next = NULL;

    if (infoTraverse == NULL)
    {
      traverse = traverse->next;
      infoCircuit->head = newResistor;
      totalResistance = totalResistance + (newResistor->value / newResistor->quantity);
      continue;
    }
    
    while (infoTraverse->next != NULL && infoTraverse->value < newResistor->value) {
        predecessor = infoTraverse;
        infoTraverse = infoTraverse->next;
      } 

      if (infoTraverse->value < newResistor->value) {

        infoTraverse->next = newResistor;
        totalResistance = totalResistance + (newResistor->value / newResistor->quantity);

      } 
      else if ( infoTraverse->value > newResistor->value) {

        newResistor->next = infoTraverse;
        if (predecessor == NULL) {
          infoCircuit->head = newResistor;
        } 
        else {
          predecessor->next = newResistor;
        }
        totalResistance = totalResistance + (newResistor->value / newResistor->quantity);

      } 
      else if (infoTraverse->value == newResistor->value) {

        infoTraverse->quantity = infoTraverse->quantity + newResistor->quantity;
        totalResistance = totalResistance + (newResistor->value / newResistor->quantity);
      }

    traverse = traverse->next;
  }
  //print infoCircuit
  infoTraverse = infoCircuit->head;
  while (infoTraverse)
  {
    cout << infoTraverse->value << ":" << infoTraverse->quantity << endl;
    infoTraverse = infoTraverse->next;
  }
  cout << "Total resistance=" << totalResistance << " ohm" << endl;
  
  Resistor* deletePtr;
  while (infoCircuit->head)
  {
    deletePtr = infoCircuit->head;
    infoCircuit->head = infoCircuit->head->next;
    delete deletePtr;
  }
    

}
  

void Circuit::clear(){
  Resistor* traverse;

  while (head)
  {
    traverse = head;
    head = head->next;
    delete traverse;
  }
  
}


int main(){

  //ifstream circuitFile("input.txt");
  std::fstream inputFile;
  inputFile.open("input.txt", fstream::in|fstream::binary);
  if (!inputFile.is_open())
  {
    inputFile.open("input.txt", fstream::out|fstream::binary);
    if (!inputFile.is_open())
    {
      cerr << "Cannot open file";
      exit(1);
    }
    
  }
  

  Circuit *circuit = new Circuit;
  circuit->create();
   
  char group;
  float value;
  //while (circuitFile >> group >> value)
  while (inputFile >> group >> value)
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

  inputFile.close();
  circuit->clear();
  return 0;
}




