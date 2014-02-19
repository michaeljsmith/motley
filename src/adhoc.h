#ifndef __JEST_ADHOC_H__
#define __JEST_ADHOC_H__

template <typename F0, typename F1> struct AdHocPair : F0, F1 {
  using F0::operator();
  using F1::operator();

  using result_type = void;

  AdHocPair(F0 f0, F1 f1): F0(f0), F1(f1) {}
};

template <typename... T> struct AdHocOf {};
template <typename F> struct AdHocOf<F> {
  using type = F;
};
template <typename F, typename... R> struct AdHocOf<F, R...> {
  using type = AdHocPair<F, typename AdHocOf<R...>::type>;
};

template <typename F> inline F adhoc(F f) {return f;}

//template <typename F, typename... R> inline auto adhoc(F f, R... rest) -> AdHocPair<F, decltype(adhoc(rest...))> {
template <typename F, typename... R> inline typename AdHocOf<F, R...>::type adhoc(F f, R... rest) {
  return AdHocPair<F, decltype(adhoc(rest...))>(f, adhoc(rest...));
}

#endif // __JEST_ADHOC_H__
