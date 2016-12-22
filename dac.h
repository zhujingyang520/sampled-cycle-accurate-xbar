/*
 * Filename: dac.h
 * ----------------
 * This file exports the class DAC, which defines the basic 
 * behavior for a DAC.
 */

#ifndef __DAC_H__
#define __DAC_H__

#include "module.h"
#include <string>
#include <systemc.h>
#include <iostream>

/*
 * Class: DAC
 * -----------
 * Module DAC is a basic class emulates the DAC behavior.
 */
class DAC : public sc_core::sc_module, public Module {
  public:
    DAC(sc_module_name module_name, const int& nbits, const double& vref, 
        Module *parent, const std::string& name);
    virtual ~DAC() {}
    SC_HAS_PROCESS(DAC);

    // circuitry properties 
    virtual double CriticalPath() const;
    virtual double Area() const;
    virtual double Power() const;

    // behavior model of DAC 
    void DACBehavior();

  public:
    // interfaces 
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<bool> in_valid;
    sc_in<int> in_digital;      // input value is interpretted in binary number
    sc_out<bool> out_valid;
    sc_out<double> out_analog;  // output value is interpretted in analog voltage

  private:
    // instance variables 
    int nbits_;   // number of bits (resolution)
    double vref_; // reference voltage 
};

#endif 
