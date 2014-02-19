#ifndef __JEST_TEMPLATE_H__
#define __JEST_TEMPLATE_H__

#include <memory>
#include <string>
#include <boost/variant.hpp>

using std::string;
using std::shared_ptr;
using std::make_shared;
using boost::variant;

template <typename T> struct Literal {
  T value;

  Literal(T const& _value): value(_value) {}
};

template <typename T> struct VariableReference {
  string name;

  VariableReference(string const& _name): name(_name) {}
};

template <typename T> struct Expression {
  variant<Literal<T>, VariableReference<T>> value;

  Expression(Literal<T> literal): value(literal) {}
  Expression(VariableReference<T> variableReference): value(variableReference) {}
};

template <typename T> Expression<T> literal(T const& value) {
  return Expression<T>(Literal<T>(value));
}

template <typename T> Expression<T> variableReference(string const& name) {
  return Expression<T>(VariableReference<T>(name));
}

template <typename T, typename F> inline auto visitExpression(Expression<T> const& expression, F visitor) -> decltype(apply_visitor(visitor, expression.value)) {
  return apply_visitor(visitor, expression.value);
}

#endif// __JEST_TEMPLATE_H__
