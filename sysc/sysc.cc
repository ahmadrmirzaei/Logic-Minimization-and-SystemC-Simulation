#include "sysc.hh"

int sc_main(int argc, char* argv[]) {
	sc_signal<sc_logic> a;
	sc_signal<sc_logic> b;
	sc_signal<sc_logic> c;
	sc_signal<sc_logic> d;
	sc_signal<sc_logic> s;
	sc_signal<sc_logic> o;
	sc_int<5> in;
	sc_lv<5> in2;

	mod2* TOP = new mod2 ("mod2");
	(*TOP)(a,b,c,d,s,o);

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("main");
	sc_trace(VCDFile, TOP->a, "a");
	sc_trace(VCDFile, TOP->b, "b");
	sc_trace(VCDFile, TOP->c, "c");
	sc_trace(VCDFile, TOP->d, "d");
	sc_trace(VCDFile, TOP->s, "s");
	sc_trace(VCDFile, TOP->o, "o");

	sc_start(0, SC_NS);
	in = 0;
	for(int i=0; i<32; i++) {
		in2 = in;
		a = in2[0];
		b = in2[1];
		c = in2[2];
		d = in2[3];
		s = in2[4];
		sc_start(30, SC_NS);
		in++;
	}

	sc_start(30, SC_NS);

  return 0;
}