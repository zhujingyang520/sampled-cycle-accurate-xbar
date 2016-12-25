#include "mac.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
 * Implementation notes: Constructor
 * ----------------------------------
 */
MAC::MAC(sc_module_name module_name, const int& M, const int& N,
    Module *parent, const string& name)
  : sc_module(module_name), Module(parent, name)
{
  M_ = M;
  N_ = N;
  in_values = new sc_in<int> [M_];
  out_values = new sc_out<int> [N_];
  
  InitMAC();
}

/*
 * Implementation notes: Destructor
 * ---------------------------------
 */
MAC::~MAC()
{
  delete [] in_values;
  delete [] out_values;
  delete [] dac_values;
  delete [] crossbar_values;
  
  for (int i = 0; i < N_; ++i)
    delete adcs_[i];
  delete [] adcs_;

  for (int i = 0; i< M_; ++i)
    delete dacs_[i];
  delete [] dacs_;

  delete crossbar_;
}

/*
 * Implementation notes: InitMAC
 * ------------------------------
 * Initialize the MAC with the interconnection of ADCs, DACs, and 
 * Crossbar.
 */
void MAC::InitMAC()
{
  // initialize the interconnection wires
  dac_values = new sc_signal<double> [M_];
  crossbar_values = new sc_signal<double> [N_];

  // dummy (floating) wires, workaround for system C
  dummy1 = new sc_signal<bool> [M_];
  dummy2 = new sc_signal<bool> [N_];

  // initialize the DACs
  dacs_ = new DAC* [M_];
  for (int i = 0; i < M_; ++i) {
    char dac_name[32];
    sprintf(dac_name, "DAC_%d", i);
    // TODO: hardcode nbits = 2, vref = 1
    dacs_[i] = new DAC(dac_name, 2, 1, this, dac_name);
    dacs_[i] -> clock(clock);
    dacs_[i] -> reset(reset);
    dacs_[i] -> in_valid(in_valid);
    dacs_[i] -> in_digital(in_values[i]);
    dacs_[i] -> out_analog(dac_values[i]);
    if (i == 0) dacs_[i] -> out_valid(dac_values_valid);
    else dacs_[i] -> out_valid(dummy1[i]);
  }

  // initialize the crossbar
  char crossbar_name[32];
  sprintf(crossbar_name, "XBAR");
  crossbar_ = new Crossbar(crossbar_name, M_, N_, this, crossbar_name);
  crossbar_ -> clock(clock);
  crossbar_ -> reset(reset);
  crossbar_ -> in_valid(dac_values_valid);
  for (int i = 0; i < M_; ++i)
    crossbar_ -> wordline_voltage[i](dac_values[i]);
  crossbar_ -> out_valid(crossbar_values_valid);
  for (int i = 0; i < N_; ++i)
    crossbar_ -> bitline_voltage[i](crossbar_values[i]);

  // initialize the DACs
  adcs_ = new ADC* [N_];
  for (int i = 0; i < N_; ++i) {
    char adc_name[32];
    sprintf(adc_name, "ADC_%d", i);
    // TODO: hardcode nbits = 2, vref = 1
    adcs_[i] = new ADC(adc_name, 2, 1, this, adc_name);
    adcs_[i] -> clock(clock);
    adcs_[i] -> reset(reset);
    adcs_[i] -> in_valid(crossbar_values_valid);
    adcs_[i] -> in_analog(crossbar_values[i]);
    adcs_[i] -> out_digital(out_values[i]);
    if (i == 0) adcs_[i] -> out_valid(out_valid);
    else adcs_[i] -> out_valid(dummy2[i]);
  }
}

/*
 * Implementation notes: CriticalPath
 * -----------------------------------
 * Critical path of crossbar is the maximum (i.e. longest) delay among 
 * all modules.
 */
double MAC::CriticalPath() const
{
  double result = 0.0;
  for (vector<Module *>::const_iterator iter = children_.begin();
      iter != children_.end(); ++iter) {
    if (result < (*iter) -> CriticalPath())
      result = (*iter) -> CriticalPath();
  }
  return result;
}

/*
 * Implementation notes: Area
 * ---------------------------
 * Area is the sum of all the components.
 */
double MAC::Area() const
{
  double result = 0.0;
  for (vector<Module *>::const_iterator iter = children_.begin();
      iter != children_.end(); ++iter) {
    result += (*iter) -> Area();
  }
  return result;
}

/*
 * Implementation notes: Power
 * ----------------------------
 * Power is the sum of all the components. However, the dynamic power should
 * depends on the working status, and it is better to model it in the PROCESS.
 * (TODO)
 */
double MAC::Power() const
{
  double result = 0.0;
  for (vector<Module *>::const_iterator iter = children_.begin();
      iter != children_.end(); ++iter) {
    result += (*iter) -> Power();
  }
  return result;
}
