/*
 * Filename: crossbar.h
 * ---------------------
 * This file exports the class Crossbar, which defines the basic 
 * behavior for the ReRAM crossbar structure.
 */

#ifndef __CROSSBAR_H__
#define __CROSSBAR_H__

#include "module.h"
#include <string>
#include <iostream>
#include <vector>
#include <systemc.h>

typedef std::vector< std::vector<double> > Matrix;

/*
 * Class: Crossbar
 * ----------------
 * Module Crossbar is the crucial element to conduct the dot 
 * product operation.
 */
class Crossbar : public sc_core::sc_module, public Module {
  public:
    Crossbar(sc_module_name module_name, const int& M, const int& N,
        Module *parent, const std::string& name);
    virtual ~Crossbar();
    SC_HAS_PROCESS(Crossbar);

    // circuitry properties
    virtual double CriticalPath() const;
    virtual double Area() const;
    virtual double Power() const;

    // behavior model of Crossbar 
    void CrossbarBehavior();

  private:
    // private methods 
    void InitCrossbar();

  public:
    // interfaces 
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<bool> in_valid;
    sc_in<double> *wordline_voltage;  // applied wordline voltage 
    sc_out<bool> out_valid;
    sc_out<double> *bitline_voltage;  // converted voltage on the sensed resistors
    

  private:
    // instance variables 
    int M_, N_;                       // dimension: MxN crossbar
    Matrix conductance_;              // MxN conductance of crossbar 
    double sensed_conductance_;       // the sensed conductance at the bitline
};

#endif 
