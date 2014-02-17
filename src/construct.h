#ifndef __JEST__CONSTRUCT_H__
#define __JEST__CONSTRUCT_H__

#include <memory>
#include "template.h"

using std::shared_ptr;

template <typename T> inline T construct(shared_ptr<Expression<T>> expr) {
  switch (expr->mode) {
    case Mode::Literal:
      {
        return expr, ExpressionConstructor();
      }
  }
}

#endif //__JEST__CONSTRUCT_H__
