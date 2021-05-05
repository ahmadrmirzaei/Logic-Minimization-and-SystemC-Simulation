#include <iostream>
#include <string>
#include <vector>

#include "wire.hh"
#include "assign.hh"
#include "module.hh"

#include "driver.hh"

using namespace std;

int main() {
  driver drv;
  drv.parse("verilog.v");
  cout << *drv.top_module << endl;
}