
#include <systemc.h>
#include <string>
#include <vector>

using namespace std;

class Primitive {
    string name;
};

SC_MODULE(Buff) {
    sc_in<sc_logic> in;
    sc_out<sc_logic> out;

    SC_CTOR(Buff) {
        SC_METHOD(evl);
        sensitive << in;
    }
    void evl();
};

SC_MODULE(Not) {
    sc_in<sc_logic> in;
    sc_out<sc_logic> out;

    SC_CTOR(Not) {
        SC_METHOD(evl);
        sensitive << in;
    }
    void evl();
};

SC_MODULE(And) {
    sc_in<sc_logic> a;
    sc_in<sc_logic> b;
    sc_out<sc_logic> out;

    SC_CTOR(And) {
        SC_METHOD(evl);
        sensitive << a << b;
    }
    void evl();
};

SC_MODULE(Or) {
    sc_in<sc_logic> a;
    sc_in<sc_logic> b;
    sc_out<sc_logic> out;

    SC_CTOR(Or) {
        SC_METHOD(evl);
        sensitive << a << b;
    }
    void evl();
};

SC_MODULE(Product) {
    sc_in<sc_logic> a;
    sc_in<sc_logic> b;
    sc_in<sc_logic> c;
    sc_in<sc_logic> d;
    sc_out<sc_logic> out;

    sc_signal<sc_logic> $1;
    sc_signal<sc_logic> $2;
    And* $1_maker;
    And* $2_maker;
    And* out_maker;

    SC_CTOR(Product) {
        $1_maker = new And("$1_maker");
            (*$1_maker)(a,b,$1);
        $2_maker = new And("$2_maker");
            (*$2_maker)(a,b,$2);
        out_maker = new And("out_maker");
            (*out_maker)($1,$2,out);
        
    }
};

SC_MODULE(Cond) {
    sc_in<sc_logic> cond;
    sc_in<sc_logic> a;
    sc_in<sc_logic> b;
    sc_out<sc_logic> out;

    SC_CTOR(Cond) {
        SC_METHOD(evl);
        sensitive << cond << a << b;
    }
    void evl();
};

template<int delay>
SC_MODULE(Assignn) {
    sc_in<sc_logic> in;
    sc_out<sc_logic> out;

    SC_CTOR(Assignn) {
        SC_METHOD(evl);
        sensitive << in;
    }
    void evl() {
        next_trigger(delay, SC_NS);
        out->write(in->read());
    }
};