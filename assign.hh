#ifndef _ASSIGN_
#define _ASSIGN_

#include <string>
#include <vector>
#include "wire.hh"

using namespace std;

class Assign {
public:
    int delay;
    Wire* output;
    
    Assign(int delay, Wire* output)
        : delay(delay), output(output) {}
    friend ostream& operator<<(ostream &out, const Assign &assign);
    virtual ostream& print(ostream& out) const = 0;
};

class SOP : public Assign {
public:
    vector<vector<pair<bool,Wire*>>> value;

    SOP(int delay, Wire* output, vector<vector<pair<bool,Wire*>>> value)
        : Assign(delay, output), value(value) {}

    ostream& print(ostream& out) const;
};

class Condition : public Assign {
public:
    vector<Wire*> value;

    Condition(int delay, Wire* output, vector<Wire*> value)
        : Assign(delay, output), value(value) {}
    ostream& print(ostream& out) const;
};

#endif