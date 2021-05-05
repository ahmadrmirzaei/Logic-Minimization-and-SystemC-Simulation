#include "wire.hh"

Wire::Wire(Wire* RHS) {
	type = RHS->type;
	name = RHS->name;
	value = RHS->value;
	time = RHS->time;
	faultyWire = RHS->faultyWire;
	faultValue = RHS->faultValue;
	RHS->modified = false;
}

void Wire::operator=(Wire RHS) {
	if (this == &RHS) return;
	value = RHS.value;
	time = RHS.time;
	modified = true;
}

void Wire::operator&=(Wire* RHS) {
	if (value == '0' || RHS->value == '0')
		value = '0';
	else if (value == '1' && RHS->value == '1')
		value = '1';
	else value = 'x';
	time = max(time, RHS->time);
	RHS->modified = false;
}

void Wire::operator|=(Wire* RHS) {
	if (value == '1' || RHS->value == '1')
		value = '1';
	else if (value == '0' && RHS->value == '0')
		value = '0';
	else value = 'x';
	time = max(time, RHS->time);
	RHS->modified = false;
}

void Wire::operator==(Wire* RHS) {
	if (RHS->value == 'z' || RHS->value == 'x'
		|| value == 'z' || value == 'x') value = 'x';
	if (value == RHS->value) value = '1';
	else value = '0';
	time = max(time, RHS->time);
	RHS->modified = false;
}

void Wire::operator!=(Wire* RHS) {
	if (RHS->value == 'z' || RHS->value == 'x'
		|| value == 'z' || value == 'x') value = 'x';
	if (value == RHS->value) value = '0';
	else value = '1';
	time = max(time, RHS->time);
	RHS->modified = false;
}

void Wire::operator~() {
	if (value == '1') value = '0';
	else if(value == '0') value = '1';
}

ostream& operator<<(ostream &out, Wire &wire) {
	out << wire.name << "\t\t" << wire.value;
	return out;
}

void Wire::operator=(char RHS) {
	value = RHS;
	modified = true;
}

void Wire::reset() {
	value = 'z';
	modified = true;
	time = 0;
}