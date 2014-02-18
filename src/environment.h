#ifndef __JEST_ENVIRONMENT_H__
#define __JEST_ENVIRONMENT_H__

#include <vector>
#include <boost/any.hpp>
#include <string>
#include <memory>
#include <functional>
#include <iostream>
#include <cassert>

using std::shared_ptr;
using std::vector;
using std::string;
using boost::any;
using boost::any_cast;
using std::function;

struct Environment {
  struct Entry {
    shared_ptr<Entry> rest;
    string name;
    any value;

    Entry(shared_ptr<Entry> const& _rest, string const& _name, any const& _value)
      : rest(_rest), name(_name), value(_value) {}
  };

  shared_ptr<Entry> headEntry;
};

template <typename T> void push(Environment& environment, string const& name, T const& value) {
  auto entry = make_shared<Environment::Entry>(environment.headEntry, name, value);
  environment.headEntry = entry;
}

template <typename T> T lookup(Environment const& environment, string const& name) {
  function<T (shared_ptr<Environment::Entry> const&)> recurse;
 
  recurse = [&](shared_ptr<Environment::Entry> const& entry) {

      if (!entry) {
        std::cout << "missing entry\n";
        assert(0);
      }

      if (entry->name == name) {
        if (entry->value.type() == typeid(T)) {
          return any_cast<T>(entry->value);
        } else {
          std::cout << "entry of wrong type\n";
          assert(0);
        }
      }

      return recurse(entry->rest);
    };

  return recurse(environment.headEntry);
}

#endif //__JEST_ENVIRONMENT_H__
