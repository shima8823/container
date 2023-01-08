#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

// integral_constant

// _Tp型の__v
template <class _Tp, _Tp __v>
struct integral_constant {
	static const _Tp value = __v;
	typedef _Tp value_type;
	typedef integral_constant<_Tp, __v> type;
	const value_type operator()() const {return value;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// remove_const

template <class T>
struct remove_const {typedef T type;};
template <class T>
struct remove_const<const T> {typedef T type;};

// remove_volatile
// volatile compile時の最適化

template <class T>
struct remove_volatile {typedef T type;};
template <class T>
struct remove_volatile<volatile T> {typedef T type;};

// remove_cv

template <class T>
struct remove_cv {
	typedef typename remove_volatile<typename remove_const<T>::type>::type type;
};

// helper

template <class _Tp>
struct _is_integral : public false_type {};

// template <> 完全特殊化 それぞれの型に対して。
template <> struct _is_integral<bool>				: public true_type {};
template <> struct _is_integral<char>				: public true_type {};
template <> struct _is_integral<signed char>		: public true_type {};
template <> struct _is_integral<unsigned char>		: public true_type {};
template <> struct _is_integral<wchar_t>			: public true_type {};
template <> struct _is_integral<short>				: public true_type {};
template <> struct _is_integral<unsigned short>		: public true_type {};
template <> struct _is_integral<int>				: public true_type {};
template <> struct _is_integral<unsigned int>		: public true_type {};
template <> struct _is_integral<long>				: public true_type {};
template <> struct _is_integral<unsigned long>		: public true_type {};

// is_integral

template <class _Tp>
struct is_integral : public _is_integral<typename remove_cv<_Tp>::type> {};

// enable_if

// false の場合
template <bool B, class _Tp = void> struct enable_if {};
// true の場合
template <class _Tp> struct enable_if<true, _Tp> {typedef _Tp type;};

} // namespace ft

#endif
