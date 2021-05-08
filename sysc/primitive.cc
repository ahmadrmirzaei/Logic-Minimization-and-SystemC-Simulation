#include "primitive.hh"

void Not::evl() {
    if(in->read() == SC_LOGIC_0) out->write(SC_LOGIC_1);
    else if(in->read() == SC_LOGIC_1) out->write(SC_LOGIC_0);
    else out->write(SC_LOGIC_X);
}

void Buff::evl() {
    out->write(in->read());
}

void And::evl() {
    if(a->read() == SC_LOGIC_1 && b->read() == SC_LOGIC_1) 
        out->write(SC_LOGIC_1);
    else if(a->read() == SC_LOGIC_0 || b->read() == SC_LOGIC_0)
        out->write(SC_LOGIC_0);
    else out->write(SC_LOGIC_X);
}

void Or::evl() {
    if(a->read() == SC_LOGIC_1 || b->read() == SC_LOGIC_1) 
        out->write(SC_LOGIC_1);
    else if(a->read() == SC_LOGIC_0 && b->read() == SC_LOGIC_0)
        out->write(SC_LOGIC_0);
    else out->write(SC_LOGIC_X);
}

void Cond::evl() {
    if(cond->read() == SC_LOGIC_1)
        out->write(a->read());
    else out->write(b->read());
}