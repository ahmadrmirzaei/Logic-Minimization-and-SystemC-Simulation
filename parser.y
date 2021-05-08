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

%nterm <string> assign
%nterm <string> condition
%nterm <string> sop
%nterm <string> product
%nterm <string> ports

%%

%start unit;
unit:
	"module" "word" "(" ports ")" ";" lines "endmodule"
        {
            drv.make_systemc($2);
        }
;


lines: 
	assign assign {}	
|	lines assign {}
;

assign:
    "assign" "#" "number" "word" "=" sop ";"{
        drv.wassign($3, $6, $4);
        $$ = $4;
    }
|   "assign" "#" "number" "word" "=" condition ";"{
        drv.wassign($3, $6, $4);
        $$ = $4;
    }
;

condition:
    "word" "?" "word" ":" "word" {
        string out = drv.make_new_interconnect();
        drv.wcond($1, $3, $5, out);
        $$ = out;  
    }
;

sop:
    product {
        $$ = $1;
    }
|   sop "|" product {
        string out = drv.make_new_interconnect();
        drv.wor($1, $3, out);
        $$ = out;
    }
;

product:
    "word" {
        $$ = $1;
    }
|   "~" "word" {
        string out = drv.make_new_interconnect();
        drv.wnot($2, out);
        $$ = out;
    }
|   product "&" product "&" product "&" product {
        string out = drv.make_new_interconnect();
        drv.wproduct($1,$3,$5,$7,out);
        $$ = out;
    }
;

ports:
    "wire_type" "word" {
        drv.add_port($1, $2);
        $$ = $1;
    }
|   ports "," "word" {
        drv.add_port($1, $3);
        $$ = $1;    
    }
|   ports "," ports {
        $$ = $3;
    }
;

%%

void yy::parser::error (const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}