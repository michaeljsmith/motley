#ifndef __JEST__CONSTRUCT_H__
#define __JEST__CONSTRUCT_H__

#include "adhoc.h"
#include "environment.h"
#include <memory>
#include <iostream>
#include "expression.h"

using std::shared_ptr;

template <typename T> inline T construct(Environment const& environment, Expression<T> expression) {
  T result;
  visitExpression(expression, adhoc(

    [&] (Literal<T> const& literal) {
      result = literal.value;
    },

    [&] (VariableReference<T> const& variableReference) {
      result = lookup<T>(environment, variableReference.name);
    }));

  return result;
}

#endif //__JEST__CONSTRUCT_H__
