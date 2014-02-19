#ifndef __JEST_ADHOC_H__
#define __JEST_ADHOC_H__

template <typename F0, typename F1> struct AdHocPair : F0, F1 {
  using F0::operator();
  using F1::operator();

  AdHocPair(F0 f0, F1 f1): F0(f0), F1(f1) {}
};

template <typename... T> struct AdHocOf {};
template <typename F> struct AdHocOf<F> {
  using type = F;
};
template <typename F, typename... R> struct AdHocOf<F, R...> {
  using type = AdHocPair<F, typename AdHocOf<R...>::type>;
};

template <typename T, typename U> struct AdHoc : U {
  using U::operator();

  using result_type = T;

  AdHoc(U u): U(u) {}
};

template <typename F> inline F adhocRecurse(F f) {return f;}

template <typename F, typename... R> inline typename AdHocOf<F, R...>::type adhocRecurse(F f, R... rest) {
  return AdHocPair<F, decltype(adhocRecurse(rest...))>(f, adhocRecurse(rest...));
}

template <typename T, typename... A> AdHoc<T, typename AdHocOf<A...>::type> adhoc(A... args) {
  return AdHoc<T, typename AdHocOf<A...>::type>(adhocRecurse(args...));
}

#endif // __JEST_ADHOC_H__
