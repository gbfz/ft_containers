#pragma  once
// #include "../utilities/ft_type_traits.hpp"
#include "../utilities/ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"

namespace ft {

template <typename _Iterator>
class reverse_iterator {
protected:
// underlying memory accessor 
	_Iterator	_base;

public:
// member types definitions 
	typedef _Iterator				base_type;
	typedef iterator_traits<base_type>		traits;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;

// constructors 
	reverse_iterator():
		_base() {}
	explicit reverse_iterator(base_type iterator):
		_base(iterator) {}
	reverse_iterator(const reverse_iterator& other):
		_base(other.base()) {}
	template <typename other_type>
	reverse_iterator(const reverse_iterator<other_type>& other):
		_base(other.base()) {}

// *, ->, [] 
	reference operator * () const {
		base_type tmp = _base;
		return *(--tmp);
	}
	pointer operator -> () const {
		base_type tmp = _base;
		return iterator_to_pointer(--tmp);
	}
	reference operator [] (difference_type off) const {
		return _base[-off - 1];
	}

// ++ 
	reverse_iterator& operator ++ () {
		--_base;
		return *this;
	}
	reverse_iterator operator ++ (int) {
		reverse_iterator tmp = *this;
		--_base;
		return tmp;
	}

// -- 
	reverse_iterator& operator -- () {
		++_base;
		return *this;
	}
	reverse_iterator operator -- (int) {
		reverse_iterator tmp = *this;
		++_base;
		return tmp;
	}

// +, +=
	reverse_iterator operator + (difference_type off) {
		return reverse_iterator(_base - off);
	}
	reverse_iterator& operator += (difference_type off) {
		_base -= off;
		return *this;
	}

// -, -= 
	reverse_iterator operator - (difference_type off) {
		return reverse_iterator(_base + off);
	}
	reverse_iterator& operator -= (difference_type off) {
		_base += off;
		return *this;
	}

// base 
	base_type base() const {
		return _base;
	}

private:
// base to pointer 
//   if base_type is a pointer
	template <typename __base_type>
	static __base_type*
	iterator_to_pointer(__base_type* ptr) {
		return ptr;
	}
//    if base type is an iterator
	template <typename __base_type>
	static pointer
	iterator_to_pointer(__base_type ptr) {
		return ptr.operator->();
	}

}; // ! class reverse iterator

// iterator difference 
template <typename typeL, typename typeR>
inline typename reverse_iterator<typeL>::difference_type
operator -
(const reverse_iterator<typeL>& lhs,
 const reverse_iterator<typeR>& rhs) {
	return rhs.base() - lhs.base();
}
template <typename type>
inline typename reverse_iterator<type>::difference_type
operator -
(const reverse_iterator<type>& lhs,
 const reverse_iterator<type>& rhs) {
	return rhs.base() - lhs.base();
}

// iterator comparison 
template <typename it, typename cit>
inline bool
operator ==
(const reverse_iterator<it>& lhs,
 const reverse_iterator<cit>& rhs) {
	return lhs.base() == rhs.base();
}
template <typename it, typename cit>
inline bool
operator !=
(const reverse_iterator<it>& lhs,
 const reverse_iterator<cit>& rhs) {
	return lhs.base() != rhs.base();
}
template <typename it, typename cit>
inline bool
operator <
(const reverse_iterator<it>& lhs,
 const reverse_iterator<cit>& rhs) {
	return rhs.base() < lhs.base();
}
template <typename it, typename cit>
inline bool
operator >
(const reverse_iterator<it>& lhs,
 const reverse_iterator<cit>& rhs) {
	return rhs.base() > lhs.base();
}
template <typename it, typename cit>
inline bool
operator <=
(const reverse_iterator<it>& lhs,
 const reverse_iterator<cit>& rhs) {
	return rhs.base() <= lhs.base();
}
template <typename it, typename cit>
inline bool
operator >=
(const reverse_iterator<it>& lhs,
 const reverse_iterator<cit>& rhs) {
	return rhs.base() >= lhs.base();
}

} // ! namespace ft
