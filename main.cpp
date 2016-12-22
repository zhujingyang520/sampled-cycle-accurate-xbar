#include <iostream>
#include <systemc.h>
#include "mac.h"
#include "testbench.h"
using namespace std;

// Main function 
int sc_main(int argc, char *argv[]) 
{
  cout << "----------------------------" << endl;
  cout << "- Simple simulation of MAC -" << endl;
  cout << "----------------------------" << endl;

  // TODO: hardcode clock period = 100ns 
  sc_clock clock("clock", 100, SC_NS);
  sc_signal<bool> reset;
  // TODO: hardcode 5x4 crossbar
  sc_signal<bool> mac_in_valid;
  sc_signal<int> mac_in[5];
  sc_signal<bool> mac_out_valid;
  sc_signal<int> mac_out[4];

  // TODO: hardcode 5x4 crossbar
  MAC *mac = new MAC("MAC", 5, 4, NULL, "MAC");
  mac -> clock(clock);
  mac -> reset(reset);
  mac -> in_valid(mac_in_valid);
  for (int i = 0; i < 5; ++i)
    mac -> in_values[i](mac_in[i]);
  mac -> out_valid(mac_out_valid);
  for (int i = 0; i < 4; ++i)
    mac -> out_values[i](mac_out[i]);
  // TODO: hardcode 5x4 testbench 
  Testbench *tb = new Testbench("Testbench", 5, 4, mac);
  tb -> clock(clock);
  tb -> reset(reset);
  tb -> mac_in_valid(mac_in_valid);
  for (int i = 0; i < 5; ++i)
    tb -> mac_in_values[i](mac_in[i]);
  tb -> mac_out_valid(mac_out_valid);
  for (int i = 0; i < 4; ++i)
    tb -> mac_out_values[i](mac_out[i]);

  sc_start();

  return 0;
}
