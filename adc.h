/*
 * Filename: adc.h
 * ----------------
 * This file expors the class ADC, which defines the basic 
 * behavior for an ADC.
 */

#ifndef __ADC_H__
#define __ADC_H__

#include "module.h"
#include <string>
#include <iostream>
#include <systemc.h>

/*
 * Class: ADC
 * -----------
 * Module ADC is a basic class emulates the ADC behavior.
 */
class ADC : public sc_core::sc_module, public Module {
  public:
    ADC(sc_module_name module_name, const int& nbits, const double& vref,
        Module *parent, const std::string& name);
    virtual ~ADC() {}
    SC_HAS_PROCESS(ADC);

    // circuitry properties
    virtual double CriticalPath() const;
    virtual double Area() const;
    virtual double Power() const;

    // behavior model of ADC 
    void ADCBehavior();

  public:
    // interfaces 
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<bool> in_valid;
    sc_in<double> in_analog;  // input value is interpretted in analog voltage
    sc_out<bool> out_valid;
    sc_out<int> out_digital;  // output value is interpretted in descrete number

  private:
    // instance variables 
    int nbits_;   // number of bits (resolution)
    double vref_; // reference voltage
};

#endif 
