#include "driver.hh"

void driver::parse(string file) {
    location.initialize(&file);
    scan_begin(file);
    yy::parser parse(*this);
    parse();
    scan_end();
}

string driver::make_new_interconnect() {
    interconnect++;
    ports += "\tsc_signal<sc_logic> $"+to_string(interconnect)+";\n";
    return "$"+to_string(interconnect);
}

void driver::wbuff(string in, string out) {
    string callee = out+"_maker";
    string type = "Buff";
    up +="\t"+type+"* " + callee + ";" + "\n";
    down +="\t\t"+callee+" = new "+type+"(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+in+","+out+");\n";
}

void driver::wnot(string in, string out) {
    string callee = out+"_maker";
    string type = "Not";
    up +="\t"+type+"* " + callee + ";" + "\n";
    down +="\t\t"+callee+" = new "+type+"(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+in+","+out+");\n";
}

void driver::wand(string a, string b, string out) {
    string callee = out+"_maker";
    string type = "And";
    up +="\t"+type+"* " + callee + ";" + "\n";
    down +="\t\t"+callee+" = new "+type+"(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+a+","+b+","+out+");\n";
}

void driver::wor(string a, string b, string out) {
    string callee = out+"_maker";
    string type = "Or";
    up +="\t"+type+"* " + callee + ";" + "\n";
    down +="\t\t"+callee+" = new "+type+"(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+a+","+b+","+out+");\n";
}

void driver::wproduct(string a, string b, string c,string d, string out) {
    string callee = out+"_maker";
    string type = "Product";
    up +="\t"+type+"* " + callee + ";" + "\n";
    down +="\t\t"+callee+" = new "+type+"(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+a+","+b+","+c+","+d+","+out+");\n";    
}

void driver::wcond(string cond, string a, string b, string out) {
    string callee = out+"_maker";
    string type = "Cond";
    up +="\t"+type+"* " + callee + ";" + "\n";
    down +="\t\t"+callee+" = new "+type+"(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+cond+","+a+","+b+","+out+");\n";
}

void driver::wassign(int delay, string in, string out) {
    string callee = out+"_maker";
    string type = "Assignn";
    up +="\t"+type+"<"+to_string(delay)+">* " + callee + ";\n";
    down +="\t\t"+callee+" = new "+type+"<"+to_string(delay)+">(\""+callee+"\");\n";
    down +="\t\t(*"+callee+")("+in+","+out+");\n";

    for(string output : outputs)
        if(out == output) return;
    ports +="\tsc_signal<sc_logic> "+out+";\n";
}

void driver::add_port(string type, string name) {
    if(type == "input") type = "in";
    else type = "out";
    ports +="\tsc_"+type+"<sc_logic> "+name+";\n";
    if(type == "out") outputs.push_back(name);
}

void driver::make_systemc(string name) {
    all += "#include <systemc.h>\n";
    all += "#include \"primitive.hh\"\n";
    all += "SC_MODULE("+name+") {\n";
    all += ports;
    all += up;
    all +="\tSC_CTOR("+name+") {\n";
    all += down;
    all +="\t}\n";
    all += "};\n";
}