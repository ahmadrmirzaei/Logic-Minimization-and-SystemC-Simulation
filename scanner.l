%{
    #include "driver.hh"
    #include "parser.hh"
    using namespace std;
%}

%option noyywrap

word    [a-zA-Z][a-zA-Z_0-9]*
number  [0-9]+
blank   [ \t\r\n]

%%

%{
    yy::location& loc = drv.location;
    loc.step();
%}

{blank}+            loc.step();
"module"            return yy::parser::make_MODULE(loc);
"endmodule"         return yy::parser::make_ENDMODULE(loc);
"assign"            return yy::parser::make_ASSIGN(loc);
"("			        return yy::parser::make_LPAREN(loc);
")"        	        return yy::parser::make_RPAREN(loc);
","       	        return yy::parser::make_COMMA(loc);
";"       	        return yy::parser::make_SEMICOLON(loc);
"#"       	        return yy::parser::make_NUMSIGN(loc);
"="       	        return yy::parser::make_EQUAL(loc);
"~"       	        return yy::parser::make_TILDE(loc);
"&"       	        return yy::parser::make_AND(loc);
"|"       	        return yy::parser::make_OR(loc);
"?"       	        return yy::parser::make_QUESTION(loc);
":"       	        return yy::parser::make_COLON(loc);
"input"|"output"    return yy::parser::make_WIRETYPE(yytext, loc);
{word}              return yy::parser::make_WORD(yytext, loc);
{number}			return yy::parser::make_NUMBER(atoi(yytext), loc);
<<EOF>>             return yy::parser::make_YYEOF(loc);
.   throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));

%%

void driver::scan_begin(string file) {
    if(!(yyin = fopen(file.c_str(), "r"))) {
        exit(EXIT_FAILURE);
    }
}

void driver::scan_end() {
    fclose(yyin);
}