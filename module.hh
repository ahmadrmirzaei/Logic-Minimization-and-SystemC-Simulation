#ifndef __MODULE__
#define __MODULE__

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "util.hh"
#include "wire.hh"
#include "assign.hh"

using namespace std;

class Module
{
public:
	string name;
	vector<Wire*> wires;
	vector<Wire*> ports;
	vector<Assign*> assigns;

	Module(string name, vector<Wire*> wires, 
		vector<Assign*> assigns, vector<string> ports_order);
	
	//char eval(string inputs);
	void assign_inputs(string inputs);
	void reset();



	friend ostream& operator<<(ostream &out, const Module &top_module);
};

#endif