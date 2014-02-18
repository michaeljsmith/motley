#ifndef __JEST__CONSTRUCT_H__
#define __JEST__CONSTRUCT_H__

#include "environment.h"
#include <memory>
#include <iostream>
#include "template.h"

using std::shared_ptr;

template <typename T> struct ExpressionConstructor {
  using result_type = void;

  Environment const& environment;
  T result;

  ExpressionConstructor(Environment const& _environment): environment(_environment) {}

  void operator()(Literal<T> const& literal) {
    result = literal.value;
  }

  void operator()(VariableReference<T> const& variableReference) {
    result = lookup<T>(environment, variableReference.name);
  }
};

template <typename T> inline T construct(Environment const& environment, Expression<T> expression) {
  ExpressionConstructor<T> expressionConstructor(environment);
  visitExpression(expression, expressionConstructor);
  return expressionConstructor.result;
}

#endif //__JEST__CONSTRUCT_H__
