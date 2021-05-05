#include "driver.hh"

driver::driver () {}

void driver::parse(string file) {
    location.initialize(&file);
    scan_begin(file);
    yy::parser parse(*this);
    parse();
    scan_end();
}

void driver::add_wire(string type, string name) {
    Wire* wire = new Wire(type, name);
    wires.push_back(wire);
}

void driver::add_sop(int delay, Wire* output, vector<vector<pair<bool,Wire*>>> sop) {
    Assign* assign = new SOP(delay, output, sop);
    assigns.push_back(assign);
}

void driver::add_condition(int delay, Wire* output, vector<Wire*> condition) {
    Assign* assign = new Condition(delay, output, condition);
    assigns.push_back(assign);
}

void driver::make_module(string name, vector<string> ports_order) {
    top_module = new Module(name, wires, assigns, ports_order);
}

void driver::log(vector<string> strs) {
    for(string str : strs)
        cout << str << " ";
    cout << endl;
}