#include "dac.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
 * Implementation notes: Constructor
 * ----------------------------------
 */
DAC::DAC(sc_module_name module_name, const int& nbits, const double& vref, 
    Module *parent, const std::string& name) 
  : sc_module(module_name), Module(parent, name) 
{
  nbits_ = nbits;
  vref_ = vref;

  SC_METHOD(DACBehavior);
  sensitive << clock.pos();
  sensitive << reset;
}

/*
 * Implementation notes: DACBehavior
 * ----------------------------------
 * TODO: build the real DAC behavior model. Here I assume an ideal DAC 
 * behavior, where no DC offset, and non-linearities.
 */
void DAC::DACBehavior()
{
  if (reset.read()) {
    // TODO: define reset behavior
    out_valid.write(0);
  } else if (in_valid.read()) {
    int input_value = in_digital.read();

    // ideal behavior
    double output_value = input_value / pow(2.0, nbits_) * vref_; 
    
    out_valid.write(1);
    out_analog.write(output_value);
    
    // LOG info
    sc_time clock_period = reinterpret_cast<sc_clock *>(clock.get_interface()) 
      -> period();
    cout << "@" << sc_time_stamp() / clock_period << " " << FullName() 
      << " Reads " << input_value << " Converts to " 
      << output_value << endl;
  } else {
    out_valid.write(0);
    out_analog.write(0);
  }
}

/*
 * Implementation notes: CriticalPath
 * -----------------------------------
 * TODO: build the Critical Path Model for a general nbits DAC. Here I simply
 * assume the critical path is linearly proportional to the resolution. 
 */
double DAC::CriticalPath() const
{
  return nbits_ * 0.5;
}

/*
 * Implementation notes: Area
 * ---------------------------
 * TODO: build the Area Model for a general nbits DAC. Here I simply assume the 
 * area is linearly proportional to the resolution.
 */
double DAC::Area() const
{
  return nbits_ * 100.0;
}

/*
 * Implementation notes: Power
 * ----------------------------
 * TODO: build the Power Model for a general nbits DAC with the reference voltage. 
 * Here I simply assume the power is the linear combination of nbits and vref.
 */
double DAC::Power() const
{
  return 1.0 * nbits_ + 2.0 * vref_;
}


