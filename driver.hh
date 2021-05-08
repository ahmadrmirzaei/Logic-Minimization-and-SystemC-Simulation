#ifndef __DRIVER__
#define __DRIVER__

#include <string>
#include <vector>
#include "parser.hh"

using namespace std;

#define YY_DECL yy::parser::symbol_type yylex (driver& drv)
YY_DECL;

class driver {
public:
    yy::location location;

    int interconnect;
    vector<string> outputs;
    string all;
    string ports;
    string up;
    string down;

    driver() : interconnect(0) {};

    string make_new_interconnect();

    void wbuff(string in, string out);
    void wnot(string in, string out);
    void wand(string a, string b, string out);
    void wor(string a, string b, string out);
    void wproduct(string a, string b, string c,string d, string out);
    void wcond(string cond, string a, string b, string out);
    void wassign(int delay, string in, string out);

    void add_port(string type, string name);
    void make_systemc(string name);

    void parse(string file);
    void scan_begin(string file);
    void scan_end();

};

#endif