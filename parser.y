%skeleton "lalr1.cc"
%require "3.7.6"

%defines
%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <iostream>
    #include <string>
    #include <vector>
    #include "util.hh"
    #include "wire.hh"
    #include "assign.hh"
    #include "module.hh"

    using namespace std;
    class driver;
}

%param {driver& drv}
%locations
%define parse.trace
%define parse.error detailed
%define parse.lac full

%code {
    #include "driver.hh"
}


%token
  MODULE 	"module"
  ENDMODULE "endmodule"
  ASSIGN    "assign"
  LPAREN	"("
  RPAREN  	")"
  COMMA		","
  SEMICOLON	";"
  NUMSIGN	"#"
  EQUAL     "="
  TILDE     "~"
  AND       "&"
  OR        "|"
  QUESTION  "?"
  COLON     ":"
;
%token <string> WIRETYPE "wire_type"
%token <string> WORD     "word"
%token <int>    NUMBER   "number"

%nterm <vector<string>> ports
%nterm <pair<bool,Wire*>> variable
%nterm <vector<pair<bool,Wire*>>> Hproduct
%nterm <vector<pair<bool,Wire*>>> product
%nterm <vector<vector<pair<bool,Wire*>>>> sop
%nterm <vector<Wire*>> condition

%%

%start unit;
unit:
	"module" "word" "(" ports ")" ";" lines "endmodule"
        { drv.make_module($2, $4); }
;


lines: 
	line line	{}	
|	lines line	{}
;

line:
    assign_statement ";" {}
;

assign_statement:
    "assign" "#" "number" "word" "=" sop {
        if(!get_wire_by_name($4, drv.wires))
            drv.add_wire("wire", $4);
        drv.add_sop($3, get_wire_by_name($4, drv.wires), $6);
    }
|   "assign" "#" "number" "word" "=" condition {
        if(!get_wire_by_name($4, drv.wires))
            drv.add_wire("wire", $4);
        drv.add_condition($3, get_wire_by_name($4, drv.wires), $6);
    }
;

condition:
    "word" "?" "word" ":" "word" {
        $$.push_back(get_wire_by_name($1, drv.wires));
        $$.push_back(get_wire_by_name($3, drv.wires));
        $$.push_back(get_wire_by_name($5, drv.wires));
    }
;

sop:
    product "|" product { $$.push_back($1); $$.push_back($3); }
|   sop "|" product     { $1.push_back($3); $$ = $1; }
;

product:
    Hproduct "~" "word" {
        Wire* wire = get_wire_by_name($3, drv.wires);
        $1.push_back(make_pair(true, wire));
        $$ = $1;
    }
|   Hproduct "word"     {
        Wire* wire = get_wire_by_name($2, drv.wires);
        $1.push_back(make_pair(false, wire));
        $$ = $1;
    }
;

Hproduct:
    variable variable   { $$.push_back($1); $$.push_back($2); }
|   Hproduct variable   { $1.push_back($2); $$ = $1; }
;

variable:
    "word" "&"  {
        Wire* wire = get_wire_by_name($1, drv.wires);
        $$ = make_pair(false, wire);
    }
|   "~" "word" "&" {
        Wire* wire = get_wire_by_name($2, drv.wires);
        $$ = make_pair(true, wire);
}
;

ports:
    "wire_type" "word" {
        $$.push_back($2);
        drv.add_wire($1, $2);
    }
|   ports "," "word" {
        $1.push_back($3);
        $$ = $1;
        drv.add_wire("input", $3);
    }
|   ports "," ports {
    $$ = $1;
    for(string port : $3)
        $$.push_back(port);
}
;

%%

void yy::parser::error (const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}