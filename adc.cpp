#include "adc.h"
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

/*
 * Implementation notes: Constructor
 * ----------------------------------
 */
ADC::ADC(sc_module_name module_name, const int& nbits, const double& vref,
    Module *parent, const std::string& name)
  : sc_module(module_name), Module(parent, name)
{
  nbits_ = nbits;
  vref_ = vref;

  SC_METHOD(ADCBehavior);
  sensitive << clock.pos();
  sensitive << reset;
}

/*
 * Implementation notes: ADCBehavior
 * ----------------------------------
 * TODO: build the real ADC behavior mode. Here I assume an ideal ADC 
 * behavior, where no DC offset, and non-linearities.
 */
void ADC::ADCBehavior() 
{
  if (reset.read()) {
    // TODO: define reset behavior
    out_valid.write(0);
  } else if (in_valid.read()) {
    double input_value = in_analog.read();

    // ideal behavior
    double LSB = vref_ / pow(2.0, nbits_);
    int output_val = round(input_value / LSB);
    // for simplicity, consider the unsigned representation only
    int min_val = 0;
    int max_val = pow(2.0, nbits_) - 1;
    output_val = max(min_val, min(output_val, max_val));
    out_digital.write(output_val);
    out_valid.write(1);

    // LOG info
    sc_time clock_period = reinterpret_cast<sc_clock *>(clock.get_interface()) 
      -> period();
    cout << "@" << sc_time_stamp() / clock_period << " " << FullName()
      << " Reads " << input_value << " Converts to "
      << output_val << endl;
  } else {
    out_valid.write(0);
    out_digital.write(0);
  }
}

/*
 * Implementation notes: CriticalPath
 * -----------------------------------
 * TODO: build the Critical Path Model for a general nbits ADC. Here I simply
 * assume the critical path is linearly proportional to resolution.
 */
double ADC::CriticalPath() const
{
  return nbits_ * 0.7;
}

/*
 * Implementation notes: Area
 * ---------------------------
 * TODO: build the Area Model for a general nbits ADC. Here I simply assume the
 * area is linearly proportional to the resolution.
 */
double ADC::Area() const
{
  return nbits_ * 500;
}

/*
 * Implementation notes: Power
 * ----------------------------
 * TODO: build the Power Model for a general nbits ADC with the reference voltage.
 * Here I simply assume the power is the linear combination of nbits and vref.
 */
double ADC::Power() const
{
  return 2.0 * nbits_ + 5.0 * vref_;
}
