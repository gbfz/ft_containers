#pragma  once
#include "../utilities/ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"

namespace ft {

template <typename _iterator, typename _container>
class normal_iterator {
protected:
// underlying memory accessor 
	_iterator				_base;
	typedef typename _container::pointer	this_iterator;
public:
// member types definitions 
	typedef iterator_traits<_iterator>		traits;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
	typedef typename traits::iterator_category	iterator_category;
// constructors
	// Default constructor
	normal_iterator():
		_base(_iterator()) {}
	// Regular copy constructor
	explicit normal_iterator(const _iterator& other):
		_base(other) {}
	// Copy constructor that allows iterator to const_iterator conversion
	template <typename other_iterator>
	normal_iterator(const normal_iterator
			<other_iterator, typename enable_if_same<this_iterator,
								 other_iterator,
								 _container>
			::type>& other):
		_base(other.base()) {}
// *, ->, [] 
	reference operator * () const {
		return *_base;
	}
	pointer operator -> () const {
		return _base;
	}
	reference operator [] (difference_type n) const {
		return _base[n];
	}
// ++ 
	normal_iterator& operator ++ () {
		++_base;
		return *this;
	}
	normal_iterator operator ++ (int) {
		normal_iterator tmp = *this;
		++_base;
		return tmp;
	}
// -- 
	normal_iterator& operator -- () {
		--_base;
		return *this;
	}
	normal_iterator operator -- (int) {
		normal_iterator tmp = *this;
		--_base;
		return tmp;
	}
// +, += 
	normal_iterator operator + (difference_type n) const {
		return normal_iterator(_base + n);
	}
	normal_iterator& operator += (difference_type n) {
		_base += n;
		return *this;
	}
// -, -= 
	normal_iterator operator - (difference_type n) const {
		return normal_iterator(_base - n);
	}
	normal_iterator& operator -= (difference_type n) {
		_base -= n;
		return *this;
	}
// base 
	const _iterator& base() const {
		return _base;
	}
}; // ! class normal iterator

// iterator difference 
template <typename typeL, typename typeR, typename _container>
inline typename normal_iterator<typeL, _container>::difference_type
operator -
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() - rhs.base();
}
template <typename type, typename _container>
inline typename normal_iterator<type, _container>::difference_type
operator -
(const normal_iterator<type, _container>& lhs,
 const normal_iterator<type, _container>& rhs) {
	return lhs.base () - rhs.base();
}

// iterator comparison 
template <typename typeL, typename typeR, typename _container>
inline bool
operator ==
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() == rhs.base();
}
template <typename typeL, typename typeR, typename _container>
inline bool
operator !=
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() != rhs.base();
}
template <typename typeL, typename typeR, typename _container>
inline bool
operator <
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() < rhs.base();
}
template <typename typeL, typename typeR, typename _container>
inline bool
operator >
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() > rhs.base();
}
template <typename typeL, typename typeR, typename _container>
inline bool
operator <=
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() <= rhs.base();
}
template <typename typeL, typename typeR, typename _container>
inline bool
operator >=
(const normal_iterator<typeL, _container>& lhs,
 const normal_iterator<typeR, _container>& rhs) {
	return lhs.base() >= rhs.base();
}

} // ! namespace ft