# sampled-cycle-accurate-xbar

This is a simple demonstration of how to use C++ to model a cycle-accurate 
system. In particular, the mini-system emulates the DAC read, Crossbar Array 
computation, and ADC conversion.

## Installation
The Software requires the pre-installation of SystemC library to model the 
concurrency of hardware platform. The SystemC can be downloaded here:
http://accellera.org/downloads/standards/systemc

Before compilation, the SystemC ROOT directory in Makefile should be replaced
with the actual installation path in your environement.
