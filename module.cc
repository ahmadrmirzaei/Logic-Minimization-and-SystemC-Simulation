#include "module.hh"

Module::Module(string name, vector<Wire*> wires, vector<Assign*> assigns, vector<string> ports_order)
    : name(name), wires(wires), assigns(assigns) {

    for(string port_name : ports_order) // making port order
        ports.push_back(get_wire_by_name(port_name, wires));

}

/*char Module::eval(string inputs) {
    assign_inputs(inputs);
    while(any_of(gates.begin(), gates.end(),
        [](Gate* gate){return !gate->is_stable();}))
        for(Gate* gate : gates) 
            gate->eval();
    return get_wire_by_type("output")[0]->value;
}*/

void Module::assign_inputs(string inputs) {
    int i = 0;
    for(auto &port : get_wire_by_type("input", wires))
        *port = inputs[i++];
}

void Module::reset() {
    for(auto &wire : wires)
        wire->reset();
}

ostream& operator<<(ostream &out, const Module &top_module) {
    for(auto &wire : top_module.wires)
        out << *wire << endl;
    for(auto &assign : top_module.assigns)
        out << *assign << endl;
    return out;
}