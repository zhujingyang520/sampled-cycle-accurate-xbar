/*
 * Filename: mac.h
 * ----------------
 * This file exports the class MAC, which consists of a complete 
 * subsystem doing Multiply-and-Accumulation (MAC). It includes 
 * DAC, ReRAM crossbar, and ADC.
 */

#ifndef __MAC_H__
#define __MAC_H__

#include "module.h"
#include "adc.h"
#include "dac.h"
#include "crossbar.h"
#include <string>
#include <iostream>
#include <vector>
#include <systemc.h>

/*
 * Class: MAC
 * -----------
 * Module MAC is the elementary unit doing the MAC operation.
 */
class MAC : public sc_core::sc_module, public Module {
  public:
    MAC(sc_module_name module_name, const int& M, const int& N, 
        Module *parent, const std::string& name);
    virtual ~MAC();
    SC_HAS_PROCESS(MAC);

    // circuitry properties
    virtual double CriticalPath() const;
    virtual double Area() const;
    virtual double Power() const;

  public:
    // interfaces
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<bool> in_valid;
    sc_in<int> *in_values;
    sc_out<bool> out_valid;
    sc_out<int> *out_values;

    // interconnections 
    sc_signal<bool> dac_values_valid;
    sc_signal<double> *dac_values;
    sc_signal<bool> crossbar_values_valid;
    sc_signal<double> *crossbar_values;
    
    sc_signal<bool> *dummy1;
    sc_signal<bool> *dummy2;

  private:
    // private methods
    void InitMAC();

  private:
    // instance variables
    int M_, N_;               // dimension: MxN dot product
    ADC **adcs_;              // ADC instantiations 
    DAC **dacs_;              // DAC instantiations 
    Crossbar *crossbar_;      // Crossbar instantiation

    std::vector<Module *> modules_; // all modules within the MAC
};

#endif
