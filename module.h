/*
 * Filename: module.h
 * -------------------
 * This file exports an abstract class Module, which defines the basic 
 * properties for all circuit modules require.
 */

#ifndef __MODULE_H__
#define __MODULE_H__

#include <string>
#include <vector>
#include <iostream>

/*
 * Class: Module
 * --------------
 * Module acts as the base class for all circuit modules to inherit.
 */
class Module {
  public:
    explicit Module(Module *parent, const std::string& name);
    virtual ~Module() {}

    // inline methods
    inline const std::string& Name() const { return name_; }
    inline const std::string& FullName() const { return fullname_; }

    // display methods 
    void DisplayHierarchy(const int& level = 0, std::ostream& os = std::cout) 
      const;

    // pure virtual functions 
    virtual double CriticalPath() const = 0;
    virtual double Area() const = 0;
    virtual double Power() const = 0;

  protected:
    // Method: add child pointer to the children_ list
    void _AddChild(Module *child);

  private: 
    // instance variables 
    std::string name_;
    std::string fullname_;            // name containing hierarchy
    std::vector<Module *> children_;  // children list 
};

#endif 
