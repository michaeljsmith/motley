#ifndef __JEST_TEMPLATE_H__
#define __JEST_TEMPLATE_H__

#include <memory>

using std::shared_ptr;
using std::make_shared;

enum class Mode {
  Literal
};

template <typename T> struct Expression {
  Mode mode;

  Expression(Mode _mode): mode(_mode) {
  }
};

template <typename S> struct Template {
};

template <typename S> struct Instantiation {
};

template <typename T> struct Literal : Expression<T> {
  T value;

  Literal(T const& _value): Expression<T>(Mode::Literal), value(_value) {}
};

template <typename T> shared_ptr<Expression<T>> literal(T const& value) {
  return make_shared<Literal<T>>(value);
}

#endif// __JEST_TEMPLATE_H__
