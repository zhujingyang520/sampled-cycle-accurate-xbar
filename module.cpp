#include "module.h"
using namespace std;

/*
 * Implementation notes: Constructor
 * ----------------------------------
 * Comment goes here.
 */
Module::Module(Module *parent, const string& name)
  : name_(name) 
{
  if (parent) {
    parent -> _AddChild(this);
    fullname_ = parent -> fullname_ + "/" + name;
  } else {
    fullname_ = name;
  }
}

/*
 * Implementation notes: _AddChild
 * --------------------------------
 * Comment goes here.
 */
void Module::_AddChild(Module *child) 
{
  children_.push_back(child);
}

/*
 * Implementation notes: DisplayHierarchy
 * ---------------------------------------
 * Comment goes here.
 */
void Module::DisplayHierarchy(const int& level, std::ostream& os) const 
{
  for (int i = 0; i < level; ++i)
    os << " ";  // print white space for hierarchy display
  os << name_ << endl;

  for (vector<Module *>::const_iterator iter = children_.begin(); 
      iter != children_.end(); ++iter) {
    (*iter) -> DisplayHierarchy(level + 1, os);
  }
}
