#include <iostream>
#include <string>
#include <vector>

#include "driver.hh"

using namespace std;

int main() {
  driver* drv = new driver();
  drv->parse("verilog.v");
  cout << drv->all;
}