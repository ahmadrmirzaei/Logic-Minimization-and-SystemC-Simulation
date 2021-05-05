#include "util.hh"

Wire* get_wire_by_name(string wire_name, vector<Wire*> wires) {
    for(auto &wire : wires)
        if(wire->name == wire_name)
            return wire;
    return nullptr;
}

vector<Wire*> get_wire_by_type(string type, vector<Wire*> wires) {
    vector<Wire*> founded;
    for(auto &wire : wires)
        if(wire->type == type)
            founded.push_back(wire);
    return founded;
}

string tobin(int value) {
    string out;
    if(value > 1) out += tobin(value/2);
    out += to_string(value % 2);
    return out;
}