#ifndef _UTIL_
#define _UTIL_

#include <iostream>
#include <vector>
#include <string>
#include "wire.hh"

using namespace std;

Wire* get_wire_by_name(string wire_name, vector<Wire*> wires);
vector<Wire*> get_wire_by_type(string type, vector<Wire*> wires);
string tobin(int value);

#endif