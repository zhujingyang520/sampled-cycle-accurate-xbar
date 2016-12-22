#include "crossbar.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
 * Implementation notes: Constructor
 * ----------------------------------
 */
Crossbar::Crossbar(sc_module_name module_name, const int& M, const int& N, 
    Module *parent, const std::string& name)
  : sc_module(module_name), Module(parent, name)
{
  M_ = M;
  N_ = N;
  wordline_voltage = new sc_in<double> [M_];
  bitline_voltage = new sc_out<double> [N_];
  InitCrossbar();

  SC_METHOD(CrossbarBehavior);
  sensitive << clock.pos();
  sensitive << reset;
}

/*
 * Implementation notes: Destructor
 * ---------------------------------
 */
Crossbar::~Crossbar()
{
  delete [] wordline_voltage;
  delete [] bitline_voltage;
}

/*
 * Implementation notes: CrossbarBehavior
 * ---------------------------------------
 * TODO: build the real ReRAM crossbar mode. Here I assume an ideal Crossbar
 * behavior, where the output voltage is the dot product of input voltage and 
 * the ReRAM equivalent conductance. We can call HSPICE simulation here if we 
 * want a more accurate estimation of output voltage.
 */
void Crossbar::CrossbarBehavior()
{
  if (reset.read()) {
    // TODO: define reset behavior 
    out_valid.write(0);
  } else if (in_valid.read()) {
    for (int j = 0; j < N_; ++j) {
      double dot_product = 0.0;
      for (int i = 0; i < M_; ++i) {
        dot_product += conductance_[i][j] / sensed_conductance_ * 
          wordline_voltage[i].read();
      }
      bitline_voltage[j].write(dot_product);
    }
    out_valid.write(1);

    // LOG info
    sc_time clock_period = reinterpret_cast<sc_clock *>(clock.get_interface()) 
      -> period();
    cout << "@" << sc_time_stamp() / clock_period << " " << FullName()
      << " Does dot product" << endl;
  } else {
    out_valid.write(0);
  }
}

/*
 * Implementation notes: InitCrossbar
 * -----------------------------------
 * TODO: initialize the conductance matrix and the bitline sensed resistance
 * in the crossbar. Here I simply assumes uniform conductance value.
 */
void Crossbar::InitCrossbar()
{
  sensed_conductance_ = 2.0;  
  conductance_.resize(M_, vector<double>(N_, 4.0));
}

/*
 * Implementation notes: CriticalPath
 * -----------------------------------
 * TODO: build the Critical Path Model for a general M*N crossbar. Here I 
 * simply assume the critical path is linearly proportional to M and N.
 */
double Crossbar::CriticalPath() const
{
  return 3.0 * (M_ + N_);
}

/*
 * Implementation notes: Area
 * ---------------------------
 * TODO: build the Area Model for a general M*N crossbar. Here I simply assume 
 * the area is proportional to the product of M and N.
 */
double Crossbar::Area() const
{
  return 200 * M_ * N_;
}

/*
 * Implementation notes: Power
 * ----------------------------
 * TODO: build the Power Model for a general M*N crossbar. Here I simply assume 
 * the power is proportional to the product of M and N.
 */
double Crossbar::Power() const
{
  return 3.0 * (M_ * N_);
}
