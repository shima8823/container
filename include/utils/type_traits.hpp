#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

// integral_constant

template <typename _Tp, _Tp __v>
struct integral_constant {
	static const _Tp value = __v;
	typedef _Tp value_type;
	typedef integral_constant<_Tp, __v> type;
	const value_type operator()() const {return value;}
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// is_same

template <typename, typename>
struct is_same: public false_type {};
template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

// remove_const

template <typename T>
struct remove_const {typedef T type;};
template <typename T>
struct remove_const<const T> {typedef T type;};

// remove_volatile

template <typename T>
struct remove_volatile {typedef T type;};
template <typename T>
struct remove_volatile<volatile T> {typedef T type;};

// remove_cv

template <typename T>
struct remove_cv {
	typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

// helper

template <class _Tp>
struct is_integral_helper : public false_type {};

template <> struct is_integral_helper<bool>					: public true_type {};
template <> struct is_integral_helper<char>					: public true_type {};
template <> struct is_integral_helper<signed char>			: public true_type {};
template <> struct is_integral_helper<unsigned char>		: public true_type {};
template <> struct is_integral_helper<wchar_t>				: public true_type {};
template <> struct is_integral_helper<short>				: public true_type {};
template <> struct is_integral_helper<unsigned short>		: public true_type {};
template <> struct is_integral_helper<int>					: public true_type {};
template <> struct is_integral_helper<unsigned int>			: public true_type {};
template <> struct is_integral_helper<long>					: public true_type {};
template <> struct is_integral_helper<unsigned long>		: public true_type {};
template <> struct is_integral_helper<long long>			: public true_type {};
template <> struct is_integral_helper<unsigned long long>	: public true_type {};

// is_integral

template <class _Tp>
struct is_integral : public is_integral_helper<typename remove_cv<_Tp>::type>::type {};

// enable_if

template <bool, class _Tp = void> struct enable_if {};
template <class _Tp> struct enable_if<true, _Tp> {typedef _Tp type;};

} // namespace ft

#endif
