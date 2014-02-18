#ifndef __JEST__CONSTRUCT_H__
#define __JEST__CONSTRUCT_H__

#include <memory>
#include "template.h"

using std::shared_ptr;

template <typename T> inline T construct(shared_ptr<Expression<T>> expr) {
  struct ExpressionConstructor {
    T result;

    void visitLiteral(T const& value) {
      result = value;
    }
  };

  ExpressionConstructor expressionConstructor;
  visitExpression(expr, expressionConstructor);
  return expressionConstructor.result;
}

#endif //__JEST__CONSTRUCT_H__
