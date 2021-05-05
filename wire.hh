#ifndef __WIRE__
#define __WIRE__

#include <iostream>
#include <string>

using namespace std;

class Wire {
public:
	string type, name;
	char value;
	bool modified;
	int time;
	bool faultyWire;
	char faultValue;

public:
	Wire() : value('z'), time(0), modified(true), faultyWire(false), faultValue('z') {}

	Wire(string type, string name)
		: type(type), name(name), value('z'), time(0)
		, modified(true), faultyWire(false), faultValue('z') {}

	Wire(char value) : value(value), time(0), modified(true), faultyWire(false), faultValue('z') {}

	Wire(string type, string name, bool faultyWire, char faultValue)
		: type(type), name(name), value('z'), time(0)
		, modified(true), faultyWire(faultyWire), faultValue(faultValue) {}

	Wire(Wire* RHS);

	void operator=(Wire RHS);
	void operator&=(Wire* RHS);
	void operator|=(Wire* RHS);
	void operator==(Wire* RHS);
	void operator!=(Wire* RHS);
	void operator~();
	void operator=(char RHS);

	void reset();

	friend ostream& operator<<(ostream &out, Wire &wire);
};

#endif