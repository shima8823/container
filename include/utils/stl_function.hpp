#ifndef STL_FUNCTION_HPP
#define STL_FUNCTION_HPP

namespace ft
{

template<typename _Pair>
struct _Select1st {
	typename _Pair::first_type& operator()(_Pair& __x) const {
		return __x.first;
	}
	const typename _Pair::first_type& operator()(const _Pair& __x) const {
		return __x.first;
	}
};

} // namespace ft

#endif
