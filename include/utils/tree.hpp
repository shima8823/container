#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"

namespace ft
{

enum _Rb_tree_color { _S_red = false, _S_black = true };

/*--------------------------------------------------------------------------*/
/*                               _Rb_tree_node                              */
/*--------------------------------------------------------------------------*/

template<typename _Val>
struct _Rb_tree_node
{
	typedef _Rb_tree_node<_Val>* _Link_type;

	_Rb_tree_color	_M_color;
	_Link_type		_M_parent;
	_Link_type		_M_left;
	_Link_type		_M_right;
	_Val*			_M_value_type;
};

/*--------------------------------------------------------------------------*/
/*                               tree.cc                                    */
/*--------------------------------------------------------------------------*/

template <typename _Val>
static _Rb_tree_node<_Val>* local_Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw()
{
	/*
		size == 0
		番兵ノードが初期値のままの時
		無限ループにならないように
	*/
	if (__x->_M_right == __x)
		return __x;

	if (__x->_M_right != 0)
	{
		// 右があったら右に進んで、左に進み続ける
		__x = __x->_M_right;
		while (__x->_M_left != 0)
			__x = __x->_M_left;
	}
	else
	{
		// 右がなかったら親に戻る。
		_Rb_tree_node<_Val>* __y = __x->_M_parent;
		// 戻り続ける。
		while (__x == __y->_M_right)
		{
			__x = __y;
			__y = __y->_M_parent;
		}
		/*
			通常はこのままtrueになるが
			サイズが1の時 && 与えられた__x == rootの時にincrementされないようにする。
		*/
		if (__x->_M_right != __y)
			__x = __y;
	}
	return __x;
}

template <typename _Val>
_Rb_tree_node<_Val>*
_Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_increment(__x);
}

template <typename _Val>
const _Rb_tree_node<_Val>*
_Rb_tree_increment(const _Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_increment(const_cast<_Rb_tree_node<_Val>*>(__x));
}

template <typename _Val>
static _Rb_tree_node<_Val>*
local_Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
{
	/*
		size == 0
		番兵ノードが初期値のままの時
		無限ループにならないように
	*/
	if (__x->_M_right == __x)
		return __x;
	
	// m_headerの時は最大値を返す。
	if (__x->_M_color == _S_red && __x->_M_parent->_M_parent == __x)
		__x = __x->_M_right;
	else if (__x->_M_left != 0)
	{
		// 左があったら左に進んで、右に進み続ける
		_Rb_tree_node<_Val>* __y = __x->_M_left;
		while (__y->_M_right != 0)
			__y = __y->_M_right;
		__x = __y;
	}
	else
	{
		// 左がなかったら親に戻る。
		_Rb_tree_node<_Val>* __y = __x->_M_parent;
		// 戻り続ける。
		while (__x == __y->_M_left)
		{
			__x = __y;
			__y = __y->_M_parent;
		}
		__x = __y;
	}
	return __x;
}

template <typename _Val>
_Rb_tree_node<_Val>*
_Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_decrement(__x);
}

template <typename _Val>
const _Rb_tree_node<_Val>*
_Rb_tree_decrement(const _Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_decrement(const_cast<_Rb_tree_node<_Val>*>(__x));
}

/*--------------------------------------------------------------------------*/
/*                             _Rb_tree_iterator                            */
/*--------------------------------------------------------------------------*/

template<typename _Tp>
struct _Rb_tree_iterator
{
	typedef _Tp  value_type;
	typedef _Tp& reference;
	typedef _Tp* pointer;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t			 difference_type;

	typedef _Rb_tree_iterator<_Tp>		_Self;
	typedef typename _Rb_tree_node<_Tp>::_Link_type	_Link_type;

	_Link_type _M_node;

	_Rb_tree_iterator() : _M_node() {}

	explicit
	_Rb_tree_iterator(_Link_type __x) : _M_node(__x) { }

	reference operator*() const {return *_M_node->_M_value_type;}
	pointer operator->() const {return _M_node->_M_value_type;}

	_Self& operator++() {
		_M_node = _Rb_tree_increment(_M_node);
		return *this;
	}

	_Self operator++(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_increment(_M_node);
		return __tmp;
	}

	_Self& operator--() {
		_M_node = _Rb_tree_decrement(_M_node);
		return *this;
	}

	_Self operator--(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_decrement(_M_node);
		return __tmp;
	}

	bool operator==(const _Self& __x) {
		return _M_node == __x._M_node;
	}

	bool operator!=(const _Self& __x) {
		return _M_node != __x._M_node;
	}
};

/*--------------------------------------------------------------------------*/
/*                          _Rb_tree_const_iterator                         */
/*--------------------------------------------------------------------------*/

template<typename _Tp>
struct _Rb_tree_const_iterator
{
	typedef _Tp	 value_type;
	typedef const _Tp& reference;
	typedef const _Tp* pointer;

	typedef _Rb_tree_iterator<_Tp> iterator;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t			 difference_type;

	typedef _Rb_tree_const_iterator<_Tp>		_Self;
	typedef const _Rb_tree_node<_Tp>*			_Link_type;

	_Link_type _M_node;

	_Rb_tree_const_iterator() : _M_node() { }

	explicit _Rb_tree_const_iterator(_Link_type __x) : _M_node(__x) { }

	_Rb_tree_const_iterator(const iterator& __it) : _M_node(__it._M_node) { }

	iterator _M_const_cast() const {
		return iterator(const_cast<typename iterator::_Link_type>(_M_node));
	}

	reference operator*() const {return *_M_node->_M_value_type;}
	pointer operator->() const {return _M_node->_M_value_type;}

	_Self& operator++() {
		_M_node = _Rb_tree_increment(_M_node);
		return *this;
	}

	_Self operator++(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_increment(_M_node);
		return __tmp;
	}

	_Self& operator--() {
		_M_node = _Rb_tree_decrement(_M_node);
		return *this;
	}

	_Self operator--(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_decrement(_M_node);
		return __tmp;
	}

	bool operator==(const _Self& __x) {
		return _M_node == __x._M_node;
	}

	bool operator!=(const _Self& __x) {
		return _M_node != __x._M_node;
	}
};

/*--------------------------------------------------------------------------*/
/*                                 _Rb_tree                                 */
/*--------------------------------------------------------------------------*/

template<typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc = std::allocator<_Val> >
class _Rb_tree
{
	/*
		allocatorを再指定している。
		今回の場合はnode型の_Rb_tree_node<_Val>型に。
		rebindはstructでotherがallocatorになってくれる。
	*/
	typedef typename _Alloc::template
		rebind<_Rb_tree_node<_Val> >::other _Node_allocator;

protected:
	typedef _Rb_tree_node<_Val>*		_Link_type;
	typedef const _Rb_tree_node<_Val>*	_Const_Link_type;

public:
	typedef _Key					key_type;
	typedef _Val					value_type;
	typedef value_type*				pointer;
	typedef const value_type*		const_pointer;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	typedef size_t					size_type;
	typedef ptrdiff_t				difference_type;
	typedef _Alloc					allocator_type;
	typedef _Compare				key_compare;


protected:

	// alloc_helper

	_Link_type _M_get_node() {
		return _M_node_alloc.allocate(1);
	}

	void _M_put_node(_Link_type __p) {
		_M_node_alloc.destroy(__p);
		_M_node_alloc.deallocate(__p, 1);
	}

	void _M_construct_node(_Link_type node, const value_type& x) {
		try {
			node->_M_color = _S_red;
			node->_M_left = NULL;
			node->_M_right = NULL;
			node->_M_parent = NULL;
			_Alloc value_alloc;
			typename _Alloc::pointer p = value_alloc.allocate(1);
			value_alloc.construct(p, x);
			node->_M_value_type = p;
		} catch (...) {
			_M_put_node(node);
			throw;
		}
	}

	_Link_type _M_create_node(const value_type& x) {
		_Link_type tmp = _M_get_node();
		_M_construct_node(tmp, x);
		return tmp;
	}

	void _M_destroy_node(_Link_type __p) {
		_Alloc value_alloc;
		value_alloc.destroy(__p->_M_value_type);
		value_alloc.deallocate(__p->_M_value_type, 1);
	}

	void _M_drop_node(_Link_type __p) {
		_M_destroy_node(__p);
		_M_put_node(__p);
	}

	_Link_type _M_clone_node(_Link_type __x) {
		_Link_type __tmp = _M_create_node(*(__x->_M_value_type));
		__tmp->_M_color = __x->_M_color;
		__tmp->_M_left = 0;
		__tmp->_M_right = 0;
		return __tmp;
	}

private:

	// struct _Rb_tree_impl

	_Link_type _M_header;
	size_type _M_node_count;
	key_compare _M_key_compare;
	_Node_allocator _M_node_alloc;

protected:

	// helper

	_Link_type& _M_root() {return _M_header->_M_parent;}
	_Const_Link_type _M_root() const {return _M_header->_M_parent;}

	_Link_type& _M_leftmost() {return _M_header->_M_left;}
	_Const_Link_type _M_leftmost() const {return _M_header->_M_left;}
	_Link_type& _M_rightmost() {return _M_header->_M_right;}
	_Const_Link_type _M_rightmost() const {return _M_header->_M_right;}

	_Link_type _M_mbegin() const { return _M_header->_M_parent; }
	_Link_type _M_begin() { return _M_mbegin(); }
	_Const_Link_type _M_begin() const { return _M_header->_M_parent; }
	_Link_type _M_end() {return _M_header;}
	_Const_Link_type _M_end() const {return _M_header;}

	static _Link_type _S_left(_Link_type __x) {return __x->_M_left;}
	static _Const_Link_type _S_left(_Const_Link_type __x) {return __x->_M_left;}
	static _Link_type _S_right(_Link_type __x) {return __x->_M_right;}
	static _Const_Link_type _S_right(_Const_Link_type __x) {return __x->_M_right;}

	key_type _S_key(_Const_Link_type x) const {return x->_M_value_type->first;}

	static _Link_type _S_minimum(_Link_type __x) {
		while (__x->_M_left != 0)
			__x = __x->_M_left;
		return __x;
	}
	static _Const_Link_type _S_minimum(_Const_Link_type __x) {
		while (__x->_M_left != 0)
			__x = __x->_M_left;
		return __x;
	}

	static _Link_type _S_maximum(_Link_type __x) {
		while (__x->_M_right != 0)
			__x = __x->_M_right;
		return __x;
	}
	static _Const_Link_type _S_maximum(_Const_Link_type __x){
		while (__x->_M_right != 0)
			__x = __x->_M_right;
		return __x;
	}

public:
	typedef _Rb_tree_iterator<value_type>			iterator;
	typedef _Rb_tree_const_iterator<value_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// constructor/destructor

/*
	_M_headerは番兵ノード
	番兵ノードのparentはROOT
	番兵ノードの左はbegin()
	番兵ノードの右はend()-1
	番兵ノードがend()
*/

	_Rb_tree() : _M_key_compare(key_compare()), _M_node_alloc(_Node_allocator()) {
		_M_header = _M_create_node(value_type());
		_M_reset();
	}

	_Rb_tree(const _Compare& __comp, const allocator_type& __a = allocator_type())
		: _M_key_compare(__comp), _M_node_alloc(_Node_allocator(__a))
	{
		_M_header = _M_create_node(value_type());
		_M_reset();
	}

	_Rb_tree(const _Rb_tree& __x) {
		_M_header = _M_create_node(value_type());
		_M_reset();
		
		if (__x._M_root() != 0)
			_M_root() = _M_copy(__x);
	}

	~_Rb_tree() {
		clear();
		_M_drop_node(_M_header);
	}

	_Rb_tree& operator=(const _Rb_tree& __x) {
		if (this == &__x)
			return *this;
		clear();
		if (__x._M_root() != 0)
			_M_root() = _M_copy(__x);
		return *this;
	}

	allocator_type get_allocator() const {return allocator_type(_M_node_alloc);}

	// iterators

	iterator begin() {return iterator(_M_header->_M_left);}
	const_iterator begin() const {return const_iterator(_M_header->_M_left);}
	iterator end() {return iterator(_M_header);}
	const_iterator end() const {return const_iterator(_M_header);}

	reverse_iterator rbegin() {return reverse_iterator(end());}
	const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
	reverse_iterator rend() {return reverse_iterator(begin());}
	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
	
	// Capacity

	bool empty() const {return _M_node_count == 0;}
	size_type size() const {return _M_node_count;}
	size_type max_size() const {
		return std::min<size_type>(
			_M_node_alloc.max_size(),
			std::numeric_limits<difference_type >::max());
	}

	// Modifiers

	void clear() {
		_M_erase(_M_begin());
		_M_reset();
	}

	ft::pair<iterator, bool> _M_insert_unique(const value_type& __v) {
		typedef pair<iterator, bool> _Res;
		pair<_Link_type, _Link_type> __res = _M_get_insert_unique_pos(_KeyOfValue()(__v));
		if (__res.second)
			return _Res(_M_insert_(__res.first, __res.second, __v), true);
		return _Res(iterator(__res.first), false);
	}

	template<typename _InputIterator>
	void _M_insert_range_unique(_InputIterator __first, _InputIterator __last)
	{
		for (; __first != __last; ++__first)
			_M_insert_unique_(end(), *__first);
	}

	iterator _M_insert_unique_(const_iterator __position, const _Val& __v)
	{
		pair<_Link_type, _Link_type> __res
			= _M_get_insert_hint_unique_pos(__position, _KeyOfValue()(__v));

		if (__res.second)
			return _M_insert_(__res.first, __res.second, __v);
		return iterator(__res.first);
	}

	void erase(iterator __position) {
		if (__position == end())
			return ;
		_M_erase_aux(__position);
	}

	void erase(iterator __first, iterator __last) {_M_erase_aux(__first, __last);}

	size_type erase(const key_type& __x) {
		pair<iterator, iterator> __p = equal_range(__x);
		const size_type __old_size = size();
		_M_erase_aux(__p.first, __p.second);
		return __old_size - size();
	}

	void swap(_Rb_tree& __t) {
		if (_M_root() == 0)
		{
			if (__t._M_root() != 0)
				_M_move_data(__t);
		}
		else if (__t._M_root() == 0)
			__t._M_move_data(*this);
		else
		{
			std::swap(_M_root(), __t._M_root());
			std::swap(_M_leftmost(), __t._M_leftmost());
			std::swap(_M_rightmost(), __t._M_rightmost());

			_M_root()->_M_parent = _M_end();
			__t._M_root()->_M_parent = __t._M_end();
			std::swap(_M_node_count, __t._M_node_count);
		}
		std::swap(_M_key_compare, __t._M_key_compare);
		std::swap(_M_node_alloc, __t._M_node_alloc);
	}

	// Lookup

	iterator find(const key_type& __k) {
		iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
		return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	const_iterator find(const key_type& __k) const {
		const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
		return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	pair<iterator, iterator> equal_range(const _Key& __k)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();
		while (__x != 0)
		{
			if (_M_key_compare(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else {
				_Link_type __xu(__x);
				_Link_type __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return pair<iterator,
					iterator>(_M_lower_bound(__x, __y, __k),
							_M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<iterator, iterator>(iterator(__y), iterator(__y)); // 見つからなければ
	}

	pair<const_iterator, const_iterator> equal_range(const key_type& __k) const {
		_Const_Link_type __x = _M_begin();
		_Const_Link_type __y = _M_end();
		while (__x != 0)
		{
		if (_M_key_compare(_S_key(__x), __k))
			__x = _S_right(__x);
		else if (_M_key_compare(__k, _S_key(__x)))
			__y = __x, __x = _S_left(__x);
		else
			{
			_Const_Link_type __xu(__x);
			_Const_Link_type __yu(__y);
			__y = __x, __x = _S_left(__x);
			__xu = _S_right(__xu);
			return pair<const_iterator,
				const_iterator>(_M_lower_bound(__x, __y, __k),
						_M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<const_iterator, const_iterator>
					(const_iterator(__y), const_iterator(__y));
	}

	iterator lower_bound(const key_type& k) {
		return _M_lower_bound(_M_begin(), _M_end(), k);
	}

	const_iterator lower_bound(const key_type& k) const {
		return _M_lower_bound(_M_begin(), _M_end(), k);
	}

	iterator upper_bound(const key_type& __k) {
		return _M_upper_bound(_M_begin(), _M_end(), __k);
	}

	const_iterator upper_bound(const key_type& __k) const {
		return _M_upper_bound(_M_begin(), _M_end(), __k);
	}

	// Observers

	_Compare key_comp() const {return _M_key_compare;}

private:

	/// @brief インサート位置にインサートしてあげる。
	/// @param __x 実際の挿入位置
	/// @param __p __xの親
	/// @param __v 挿入するpair
	/// @return 新しいノードのイテレーター
	iterator _M_insert_(_Link_type __x, _Link_type __p, const value_type &__v) {
		bool __insert_left = (__x != 0 || __p == _M_end()
					|| _M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

		_Link_type __z = _M_create_node(__v);

		_Rb_tree_insert_and_rebalance(__insert_left, __z, __p, _M_header);
		++_M_node_count;
		return iterator(__z);
	}

	/// @brief 木の構造をコピーする
	/// @param __x コピー開始ノード
	/// @param __p xの親
	/// @return コピーしたノードのroot
	_Link_type _M_copy(_Link_type __x, _Link_type __p)
	{
		_Link_type __top = _M_clone_node(__x);
		__top->_M_parent = __p;

		try {
			if (__x->_M_right)
				__top->_M_right = _M_copy(_S_right(__x), __top);
			__p = __top;
			__x = _S_left(__x);

			while (__x != 0)
			{
				_Link_type __y = _M_clone_node(__x);
				__p->_M_left = __y;
				__y->_M_parent = __p;
				if (__x->_M_right)
					__y->_M_right = _M_copy(_S_right(__x), __y);
				__p = __y;
				__x = _S_left(__x);
			}
		} catch(...) {
			_M_erase(__top);
			throw;
		}
		return __top;
	}

	_Link_type _M_copy(const _Rb_tree& __x) {
		_Link_type __root = _M_copy(__x._M_mbegin(), _M_end());
		_M_leftmost() = _S_minimum(__root);
		_M_rightmost() = _S_maximum(__root);
		_M_node_count = __x._M_node_count;
		_M_key_compare = __x._M_key_compare;
		_M_node_alloc = __x._M_node_alloc;
		return __root;
	}

	void _M_erase(_Link_type __x) {
		while (__x != 0) {
			_M_erase(_S_right(__x));
			_Link_type __y = _S_left(__x);
			_M_drop_node(__x);
			__x = __y;
		}
	}

	iterator _M_lower_bound(_Link_type x, _Link_type y, const _Key& k) {
		while (x != 0)
			if (!_M_key_compare(_S_key(x), k))
				y = x, x = x->_M_left;
			else
				x = _S_right(x);
		return iterator(y);
	}

	const_iterator _M_lower_bound(_Const_Link_type x, _Const_Link_type y, const _Key& k) const {
		while (x != 0)
			if (!_M_key_compare(_S_key(x), k))
				y = x, x = x->_M_left;
			else
				x = _S_right(x);
		return const_iterator(y);
	}

	iterator _M_upper_bound(_Link_type x, _Link_type y, const _Key& k) {
		while (x != 0)
			if (_M_key_compare(k, _S_key(x)))
				y = x, x = _S_left(x);
			else
				x = _S_right(x);
		return iterator(y);
	}

	const_iterator _M_upper_bound(_Const_Link_type x, _Const_Link_type y, const _Key& k) const {
		while (x != 0)
			if (_M_key_compare(k, _S_key(x)))
				y = x, x = _S_left(x);
			else
				x = _S_right(x);
		return const_iterator(y);
	}

	/// @brief 挿入する位置を探す。
	/// @param __k 新しいノードのキーの値
	/// @return __x 実際の挿入位置 __y __xの親
	ft::pair<_Link_type, _Link_type> _M_get_insert_unique_pos(const key_type &__k) {
		typedef pair<_Link_type, _Link_type> _Res;
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();
		bool __comp = true;
		while (__x != 0) {
			//何か存在していたら
			__y = __x;
			__comp = _M_key_compare(__k, _S_key(__x));
			//比較して左辺が小さければ左側に。
			__x = __comp ? __x->_M_left : __x->_M_right;
		}
		iterator __j = iterator(__y);
		if (__comp) {
			// 最初のinsert と 挿入する位置がbeginの場合
			if (__j == begin())
				return _Res(__x, __y);
			else
				--__j; //
		}
		if (_M_key_compare(_S_key(__j._M_node), __k))
			return _Res(__x, __y);
		return _Res(__j._M_node, 0); // 重複
	}

	/// @brief __positionからどこに挿入するか決める。
	/// @param __position 挿入位置
	/// @param __k key
	/// @return pair<挿入位置, 挿入位置の親>
	pair<_Link_type, _Link_type> _M_get_insert_hint_unique_pos(const_iterator __position, const key_type& __k) {
		iterator __pos = __position._M_const_cast();
		typedef pair<_Link_type, _Link_type> _Res;

		if (__pos._M_node == _M_end())
		{
			if (size() > 0 && _M_key_compare(_S_key(_M_rightmost()), __k))
				return _Res(0, _M_rightmost()); // kが一番大きいなら。
			else
				return _M_get_insert_unique_pos(__k);
		}
		else if (_M_key_compare(__k, _S_key(__pos._M_node)))
		{
			iterator __before = __pos;
			if (__pos._M_node == _M_leftmost()) // もしbegin()だったら
				return _Res(_M_leftmost(), _M_leftmost()); // 確定で左
			else if (_M_key_compare(_S_key((--__before)._M_node), __k))
			{
				if (_S_right(__before._M_node) == 0)
					return _Res(0, __before._M_node); // 親を返す
				else
					return _Res(__pos._M_node, __pos._M_node); //
			}
			else
				return _M_get_insert_unique_pos(__k); // 見つからなければ最初から探す。
		}
		else if (_M_key_compare(_S_key(__pos._M_node), __k))
		{
			iterator __after = __pos;
			if (__pos._M_node == _M_rightmost())
				return _Res(0, _M_rightmost());
			else if (_M_key_compare(__k, _S_key((++__after)._M_node)))
			{
				if (_S_right(__pos._M_node) == 0)
					return _Res(0, __pos._M_node); //
				else
					return _Res(__after._M_node, __after._M_node); //
			}
			else
				return _M_get_insert_unique_pos(__k);
		}
		else
			return _Res(__pos._M_node, 0); // 重複
	}

	void _M_erase_aux(const_iterator __position)
	{
		_Link_type __y = _Rb_tree_rebalance_for_erase(const_cast<_Link_type>(__position._M_node), _M_header);
		_M_drop_node(__y);
		--_M_node_count;
	}

	void _M_erase_aux(const_iterator __first, const_iterator __last) {
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				_M_erase_aux(__first++);
	}

	// struct _Rb_tree_header

	void _M_reset() {
		_M_header->_M_color = _S_red;
		_M_header->_M_parent = 0;
		_M_header->_M_left = _M_header;
		_M_header->_M_right = _M_header;
		_M_node_count = 0;
	}

	void _M_move_data(_Rb_tree& __from) {
		_M_header->_M_color = __from._M_header->_M_color;
		_M_header->_M_parent = __from._M_header->_M_parent;
		_M_header->_M_left = __from._M_header->_M_left;
		_M_header->_M_right = __from._M_header->_M_right;
		_M_header->_M_parent->_M_parent = _M_header;
		_M_node_count = __from._M_node_count;
		__from._M_reset();
	}

	// tree.cc

	/// @brief 回転
	/// @param __x 実際の挿入するノードの親
	/// @param __root root
	static void local_Rb_tree_rotate_left(_Link_type const __x,
										_Link_type& __root) {
		_Link_type const __y = __x->_M_right;

		__x->_M_right = __y->_M_left;
		if (__y->_M_left != 0)
			__y->_M_left->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->_M_parent->_M_left)
			__x->_M_parent->_M_left = __y;
		else
			__x->_M_parent->_M_right = __y;
		__y->_M_left = __x;
		__x->_M_parent = __y;
	}

	/// @brief 回転
	/// @param __x 実際の挿入するノードの親
	/// @param __root root
	static void local_Rb_tree_rotate_right(_Link_type const __x,
										_Link_type& __root) {
		_Link_type const __y = __x->_M_left;

		__x->_M_left = __y->_M_right;
		if (__y->_M_right != 0)
			__y->_M_right->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->_M_parent->_M_right)
			__x->_M_parent->_M_right = __y;
		else
			__x->_M_parent->_M_left = __y;
		__y->_M_right = __x;
		__x->_M_parent = __y;
	}

	/// @brief 実際にインサートをしてみて、ルールに違反していたら回転。
	/// @param __insert_left 左にインサートするかどうか
	/// @param __x 挿入したい新しいノード
	/// @param __p 挿入したい位置の親
	/// @param __header header(end())
	void _Rb_tree_insert_and_rebalance(const bool __insert_left,
									_Link_type __x,
									_Link_type __p,
									_Link_type& __header) throw () {
		_Link_type & __root = __header->_M_parent;

		// 挿入する新しいノードの初期化
		__x->_M_parent = __p;
		__x->_M_left = 0;
		__x->_M_right = 0;
		__x->_M_color = _S_red;

		// 挿入してみる。
		// 新しいノードを親の子にして、ルート、左端、および右端のノードを維持する
		// 最初のノードは常に左に挿入される
		if (__insert_left) {
			__p->_M_left = __x; // また、__p == &__headerのとき、leftmost = __xとする

			// 初めてinsertされる時 true
			if (__p == __header) {
				__header->_M_parent = __x;
				__header->_M_right = __x;
			}
			else if (__p == __header->_M_left)
				__header->_M_left = __x; // 番兵の左端がMinノードを指すようにする
		} else {
			__p->_M_right = __x;

			if (__p == __header->_M_right)
				__header->_M_right = __x; // 右端が最大ノードを指すようにする
		}
		// Rebalance.
		// 初めては入らない。
		while (__x != __root && __x->_M_parent->_M_color == _S_red) {
			_Link_type const __xpp = __x->_M_parent->_M_parent; // xpp = 祖父

			if (__x->_M_parent == __xpp->_M_left) { // 祖父の左が親なら
				_Link_type const __y = __xpp->_M_right; // y = 叔父
				if (__y && __y->_M_color == _S_red) { 
					__x->_M_parent->_M_color = _S_black;
					__y->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					__x = __xpp;
				} else {
					if (__x == __x->_M_parent->_M_right) { // 右の子なら
						__x = __x->_M_parent;
						local_Rb_tree_rotate_left(__x, __root);
					}
					__x->_M_parent->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					local_Rb_tree_rotate_right(__xpp, __root);
				}
			} else {
				_Link_type const __y = __xpp->_M_left;
				if (__y && __y->_M_color == _S_red) {
					__x->_M_parent->_M_color = _S_black;
					__y->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					__x = __xpp;
				} else {
					if (__x == __x->_M_parent->_M_left) {
						__x = __x->_M_parent;
						local_Rb_tree_rotate_right(__x, __root);
					}
					__x->_M_parent->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					local_Rb_tree_rotate_left(__xpp, __root);
				}
			}
		}
		__root->_M_color = _S_black;
	}

	/// @brief 削除して、ルールに合うようにrebalance。
	/// @param __z 削除するノード
	/// @param __header header
	/// @return _Link_type 削除されるノード
	_Link_type _Rb_tree_rebalance_for_erase(_Link_type const __z,
					_Link_type& __header) throw ()
	{
		_Link_type& __root = __header->_M_parent;
		_Link_type& __leftmost = __header->_M_left;
		_Link_type& __rightmost = __header->_M_right;
		_Link_type __y = __z;
		_Link_type __x = 0; // yの子
		_Link_type __x_parent = 0;

		// ノードの入れ替え
		if (__y->_M_left == 0)  // y == z.  zの子は(1 || 0)個ある
			__x = __y->_M_right;  // xはnullかも
		else
			if (__y->_M_right == 0)  // y == z.  zの子は1個ある
				__x = __y->_M_left;  // xは存在する子
			else { // zの子は2個ある
				__y = __y->_M_right; // __x might be null.
				// 削除するノードの次に大きいノードを探す y = 次に大きいノード
				while (__y->_M_left != 0)
					__y = __y->_M_left;
				__x = __y->_M_right;
			}
		if (__y != __z) { // 削除するノードの子が2個の場合
			// zの代わりにyを繋げる。yはzの後継者
			__z->_M_left->_M_parent = __y;
			__y->_M_left = __z->_M_left;
			if (__y != __z->_M_right) { //448
				__x_parent = __y->_M_parent;
				if (__x) // 469
					__x->_M_parent = __y->_M_parent;
				__y->_M_parent->_M_left = __x;
				__y->_M_right = __z->_M_right;
				__z->_M_right->_M_parent = __y;
			}
			else
				__x_parent = __y; // 441
			if (__root == __z)
				__root = __y; // 441
			else if (__z->_M_parent->_M_left == __z)
				__z->_M_parent->_M_left = __y; // 462
			else
				__z->_M_parent->_M_right = __y;
			__y->_M_parent = __z->_M_parent;
			std::swap(__y->_M_color, __z->_M_color);
			__y = __z;
			// y が実際に削除されるノードを指すように
		} else { // 削除するノードの子が0, 1個の場合
			// ノードの接続の変更
			__x_parent = __y->_M_parent;
			if (__x)
				__x->_M_parent = __y->_M_parent; // 426
			if (__root == __z)
				__root = __x; //419
			else
				if (__z->_M_parent->_M_left == __z) // zが左の子なら
					__z->_M_parent->_M_left = __x; // 405
				else
					__z->_M_parent->_M_right = __x; // 412

			// 変数の更新
			if (__leftmost == __z) {
				if (__z->_M_right == 0)  // __z->_M_left もNULLでなければならない。leftmost == zだから。
					__leftmost = __z->_M_parent; //405
				// if __z == __root, __leftmost == _M_header 
				else
					__leftmost = _S_minimum(__x); // 433
			}
			if (__rightmost == __z) {
				if (__z->_M_left == 0)  // __z->_M_right もNULLでなければならない。rightmost == zだから。
					__rightmost = __z->_M_parent; // 412
				// if __z == __root, __rightmost == _M_header 
				else  // __x == __z->_M_left
					__rightmost = _S_maximum(__x); // 426
			}
		}
		if (__y->_M_color != _S_red) {
			while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
				if (__x == __x_parent->_M_left) {  // 476
					_Link_type __w = __x_parent->_M_right;  // sibling
					if (__w->_M_color == _S_red) {  // 兄弟の色が赤の場合 483
						__w->_M_color = _S_black;
						__x_parent->_M_color = _S_red;
						local_Rb_tree_rotate_left(__x_parent, __root);
						__w = __x_parent->_M_right;
					}
					if ((__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
						&& (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black))  // 兄弟の色が黒、兄弟の左右の子が黒の場合 483
					{
						__w->_M_color = _S_red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					} else {
						if (__w->_M_right == 0
							|| __w->_M_right->_M_color == _S_black)  // 兄弟の色が黒、兄弟の右の子が黒 490
						{
							__w->_M_left->_M_color = _S_black;
							__w->_M_color = _S_red;
							local_Rb_tree_rotate_right(__w, __root);
							__w = __x_parent->_M_right;
						}
						// 兄弟の色が黒、兄弟の右の子が赤
						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = _S_black;
						if (__w->_M_right)
							__w->_M_right->_M_color = _S_black; // 476
						local_Rb_tree_rotate_left(__x_parent, __root);
						break;
					}
				} else {  // 逆
					_Link_type __w = __x_parent->_M_left;
					if (__w->_M_color == _S_red) {
						__w->_M_color = _S_black;
						__x_parent->_M_color = _S_red;
						local_Rb_tree_rotate_right(__x_parent, __root);
						__w = __x_parent->_M_left;
					}
					if ((__w->_M_right == 0 ||
					__w->_M_right->_M_color == _S_black) &&
					(__w->_M_left == 0 ||
					__w->_M_left->_M_color == _S_black))
					{
						__w->_M_color = _S_red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					} else {
						if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black){
							__w->_M_right->_M_color = _S_black;
							__w->_M_color = _S_red;
							local_Rb_tree_rotate_left(__w, __root);
							__w = __x_parent->_M_left;
						}
						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = _S_black;
						if (__w->_M_left)
							__w->_M_left->_M_color = _S_black;
						local_Rb_tree_rotate_right(__x_parent, __root);
						break;
					}
				}
			if (__x)
				__x->_M_color = _S_black; // 426
		}
		return __y;
	}

};

} // namespace ft

#endif
