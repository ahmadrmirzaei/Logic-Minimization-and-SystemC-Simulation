#ifndef __DRIVER__
#define __DRIVER__

#include <string>
#include <vector>
#include "parser.hh"
#include "util.hh"
#include "wire.hh"
#include "assign.hh"
#include "module.hh"

using namespace std;

#define YY_DECL yy::parser::symbol_type yylex (driver& drv)
YY_DECL;

class driver {
public:
    yy::location location;

    vector<Wire*> wires;
    vector<Assign*> assigns;
    Module* top_module;

    driver();

    void parse(string file);
    void scan_begin(string file);
    void scan_end();

    void add_wire(string type, string name);
    void add_sop(int delay, Wire* output, vector<vector<pair<bool,Wire*>>> sop);
    void add_condition(int delay, Wire* output, vector<Wire*> condition);
    void make_module(string name, vector<string> ports_order);
    void log(vector<string> strs);
};

#endif