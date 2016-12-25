#include "testbench.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
 * Implementation notes: Constructor
 * ----------------------------------
 */
Testbench::Testbench(sc_module_name module_name, const int& M, const int& N,
    const Module* const system)
  : sc_module(module_name), system_(system) 
{
  M_ = M;
  N_ = N;
  mac_in_values = new sc_out<int> [M_];
  mac_out_values = new sc_in<int> [N_];

  // Source & Sink process
  SC_CTHREAD(Source, clock.pos());
  SC_CTHREAD(Sink, clock.pos());
}

/*
 * Implementation notes: Destructor
 * ---------------------------------
 */
Testbench::~Testbench()
{
  delete [] mac_in_values;
  delete [] mac_out_values;
}

/*
 * Implementation notes: Source
 * -----------------------------
 * TODO: Souce generates the simple synthetic MAC input digital voltage
 * in a for loop.
 */
void Testbench::Source() 
{
  // TODO: hardcode reset for 2 CCs
  reset.write(1);
  mac_in_valid.write(0);
  wait(2);
  reset.write(0);
  wait();

  // TODO: simple data pattern
  for (int i = 0; i < 50; ++i) {
    mac_in_valid.write(1);
    for (int j = 0; j < M_; ++j)
      mac_in_values[j].write(i % 4);
    wait();
  }

  mac_in_valid.write(0);
}

/*
 * Implementation notes: Sink
 * ---------------------------
 * TODO: Check the functionality and record the latency & throughput 
 * here.
 */
void Testbench::Sink()
{
  // Stop the simulation after 70 CCs
  for (int i = 0; i < 70; ++i)
    wait();
  sc_stop();

  // LOG info
  cout << "--------------------------" << endl;
  cout << "- Statistics Report      -" << endl;
  cout << "--------------------------" << endl;
  cout << "- Area: " << system_ -> Area() << endl;
  cout << "- Power: " << system_ -> Power() << endl;
  cout << "- Critical Path: " << system_ -> CriticalPath() << endl;
  cout << "--------------------------" << endl;
}
