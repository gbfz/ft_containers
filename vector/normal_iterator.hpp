#pragma  once
#include <memory>
#include <stdexcept>
#include "ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"

namespace ft {

template <typename _Iterator, typename _Container>
class _normal_iterator {
protected:
// underlying memory accessor 
	_Iterator	_base;
public:
// member types definitions 
	typedef _Iterator				base_type;
	typedef iterator_traits<_Iterator>	traits;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::difference_type	difference_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename _Container::pointer		this_iterator;
// constructors, destructor 
	// Default constructor
	_normal_iterator():
		_base(base_type()) {}
	// Regular copy constructor
	explicit _normal_iterator(const base_type& other):
		_base(other) {}
	// Copy constructor that allows iterator to const_iterator conversion
	template <typename other_iterator>
	_normal_iterator(const _normal_iterator<other_iterator, typename
				enable_if<are_same_type<other_iterator,
							this_iterator>::value,
			       _Container>::type>& other):
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
	_normal_iterator& operator ++ () {
		++_base;
		return *this;
	}
	_normal_iterator operator ++ (int) {
		return _normal_iterator(_base++);
	}
// -- 
	_normal_iterator& operator -- () {
		--_base;
		return *this;
	}
	_normal_iterator operator -- (int) {
		return _normal_iterator(_base--);
	}
// += 
	_normal_iterator& operator += (difference_type n) {
		_base += n;
		return *this;
	}
// -= 
	_normal_iterator& operator -= (difference_type n) {
		_base -= n;
		return *this;
	}
// + 
	_normal_iterator operator + (difference_type n) const {
		return _normal_iterator(_base + n);
	}
// - 
	_normal_iterator operator - (difference_type n) const {
		return _normal_iterator(_base - n);
	}
// base 
	const _Iterator& base() const {
		return _base;
	}
}; // ! class normal iterator

// _normal_iterator - _normal_iterator 
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline typename _normal_iterator<_IteratorL, _Container>::difference_type
operator -
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorL, _Container>& rhs) {
	return lhs.base () - rhs.base();
}
template <typename _Iterator, typename _Container>
inline typename _normal_iterator<_Iterator, _Container>::difference_type
operator -
(const _normal_iterator<_Iterator, _Container>& lhs,
 const _normal_iterator<_Iterator, _Container>& rhs) {
	return lhs.base () - rhs.base();
}
// _normal_iterator + offset && - offset
template <typename _Iterator, typename _Container>
inline _normal_iterator<_Iterator, _Container>
operator +
(const _normal_iterator<_Iterator, _Container>& lhs,
 typename _normal_iterator<_Iterator, _Container>::difference_type n) {
	return _normal_iterator<_Iterator, _Container>(lhs.base () + n);
}

// normal iterator comparison 
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator ==
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorR, _Container>& rhs) {
	return lhs.base() == rhs.base();
}
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator !=
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorR, _Container>& rhs) {
	return lhs.base() != rhs.base();
}
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator <
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorR, _Container>& rhs) {
	return lhs.base() < rhs.base();
}
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator >
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorR, _Container>& rhs) {
	return lhs.base() > rhs.base();
}
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator <=
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorR, _Container>& rhs) {
	return lhs.base() <= rhs.base();
}
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator >=
(const _normal_iterator<_IteratorL, _Container>& lhs,
 const _normal_iterator<_IteratorR, _Container>& rhs) {
	return lhs.base() >= rhs.base();
}

} // ! namespace ft
