/*
 * Filename: testbench.h
 * ----------------------
 * This file exports the simple class Testbench to apply the exerted 
 * voltage to the MAC system.
 */

#ifndef __TESTBENCH_H__
#define __TESTBENCH_H__

#include <systemc.h>
#include <iostream>
#include <string>
#include "module.h"

/*
 * Class: Testbench
 * -----------------
 * Testbench provides the simple voltage patterns to MAC system for 
 * simulation.
 */
SC_MODULE(Testbench) {
  public:
    Testbench(sc_module_name module_name, const int& M, const int& N,
        const Module* const system);
    ~Testbench();
    SC_HAS_PROCESS(Testbench);

    // process
    void Source();
    void Sink();

  public:
    // interfaces
    sc_in<bool> clock;
    sc_out<bool> reset;
    sc_out<bool> mac_in_valid;
    sc_out<int> *mac_in_values;
    sc_in<bool> mac_out_valid;
    sc_in<int> *mac_out_values;

  private:
    // instance variables 
    int M_, N_;   // M*N crossbar
    const Module *system_;
};

#endif 
