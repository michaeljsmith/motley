#ifndef __JEST__CONSTRUCT_H__
#define __JEST__CONSTRUCT_H__

#include "adhoc.h"
#include "environment.h"
#include <memory>
#include <iostream>
#include "expression.h"

using std::shared_ptr;

template <typename T> inline T construct(Environment const& environment, Expression<T> const& expression) {
  return visitExpression(expression, adhoc<T>(

    [] (Literal<T> const& literal) {
      return literal.value;
    },

    [&environment] (VariableReference<T> const& variableReference) {
      return lookup<T>(environment, variableReference.name);
    }));
}

#endif //__JEST__CONSTRUCT_H__
