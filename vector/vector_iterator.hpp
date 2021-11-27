#pragma  once
#include <memory>
#include <stdexcept>
#include "iterator_base_types.hpp"

namespace ft {

// iterator 
template <typename _Iterator>
class vector_iterator:
// iterator uniformity inheritance 
public iterator <
		typename iterator_traits<_Iterator>::iterator_category,
       		typename iterator_traits<_Iterator>::value_type,
		typename iterator_traits<_Iterator>::difference_type,
		typename iterator_traits<_Iterator>::pointer,
		typename iterator_traits<_Iterator>::reference
		> {
// type name shortcut 
public:
// member types definitions 
	typedef iterator_traits<_Iterator>		traits;
	typedef typename traits::difference_type	difference_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
protected:
// pointer 
	pointer m_Ptr;
public:
// ctors, =, dtor 
	vector_iterator(): m_Ptr(0) {}
	vector_iterator(pointer ptr): m_Ptr(ptr) {}
	vector_iterator(const vector_iterator& other): m_Ptr(other.m_Ptr) {}
	vector_iterator& operator = (const vector_iterator& other) {
		if (this == &other) return *this;
		m_Ptr = other.m_Ptr;
		return *this;
	}
	~vector_iterator() {}
// *, ->, [] 
	reference operator * () const { return *m_Ptr; }
	pointer   operator -> () const { return m_Ptr; }
	reference operator [] (difference_type i) { return *(m_Ptr + i); }
// ++ 
	vector_iterator& operator ++ () { ++m_Ptr; return *this; }
	vector_iterator  operator ++ (int) {
		pointer inc = m_Ptr;
		++(*this);
		return vector_iterator(inc);
	}
// -- 
	vector_iterator& operator -- () { --m_Ptr; return *this; }
	vector_iterator  operator -- (int) {
		pointer dec = m_Ptr;
		--(*this);
		return vector_iterator(dec);
	}
// offset sum, difference 
	vector_iterator operator + (difference_type off) const { return vector_iterator(m_Ptr + off); }
	vector_iterator operator - (difference_type off) const { return vector_iterator(m_Ptr - off); }
// iterator difference 
	difference_type operator - (const vector_iterator& other) {
		return m_Ptr - other.m_Ptr;
	}
// +=, -= 
	vector_iterator& operator += (difference_type off) {
		if (off >= 0) while (--off) ++(*this);
		else while (++off) --(*this);
		return *this;
	}
	vector_iterator& operator -= (difference_type off) {
		if (off >= 0) while (--off) --(*this);
		else while (++off) ++(*this);
		return *this;
	}
}; // ! class vector iterator

// iterator comparison 
// same type 
template <typename T>
bool operator == (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return lhs.operator->() == rhs.operator->();
}
template <typename T>
bool operator != (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return !(lhs == rhs);
}
template <typename T>
bool operator < (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return lhs.operator->() < rhs.operator->();
}
template <typename T>
bool operator > (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return rhs < lhs;
}
template <typename T>
bool operator <= (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return !(rhs < lhs);
}
template <typename T>
bool operator >= (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return !(lhs < rhs);
}
// different types 
template <typename T, typename U>
bool operator == (const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
	return lhs.operator->() == rhs.operator->();
}
template <typename T, typename U>
bool operator != (const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
	return !(lhs == rhs);
}
template <typename T, typename U>
bool operator < (const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
	return lhs.operator->() < rhs.operator->();
}
template <typename T, typename U>
bool operator > (const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
	return rhs < lhs;
}
template <typename T, typename U>
bool operator <= (const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
	return !(rhs < lhs);
}
template <typename T, typename U>
bool operator >= (const vector_iterator<T>& lhs, const vector_iterator<U>& rhs) {
	return !(lhs < rhs);
}

// const iterator 
template <typename _iterator>
class vector_const_iterator {
// type name shortcut 
typedef vector_const_iterator	const_iterator;
public:
// member types definitions 
	typedef iterator_traits<_iterator>		traits;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef const pointer				const_pointer;
	typedef typename traits::reference		reference;
	typedef const reference				const_reference;
	typedef typename traits::difference_type	difference_type;
protected:
// pointer 
	pointer m_Ptr;
public:
// ctors, =, dtor 
	vector_const_iterator(): m_Ptr(0) {}
	vector_const_iterator(const_pointer ptr): m_Ptr(ptr) {}
	vector_const_iterator(const const_iterator& other): m_Ptr(other.m_Ptr) {}
	const_iterator& operator = (const const_iterator& other) {
		if (this == &other) return *this;
		m_Ptr = other.m_Ptr;
		return *this;
	}
	~vector_const_iterator() {}
// *, ->, [] 
	const_reference operator * () const { return *m_Ptr; }
	const_pointer   operator -> () const { return m_Ptr; }
	const_reference operator [] (difference_type i) const { return *(m_Ptr + i); }
// ++ 
	const_iterator& operator ++ () { ++m_Ptr; return *this; }
	const_iterator  operator ++ (int) {
		const_pointer inc = m_Ptr;
		++(*this);
		return const_iterator(inc);
	}
// -- 
	const_iterator& operator -- () { --m_Ptr; return *this; }
	const_iterator  operator -- (int) {
		const_pointer dec = m_Ptr;
		--(*this);
		return const_iterator(dec);
	}
// offset sum, difference 
	const_iterator operator + (difference_type off) /* const */ { return const_iterator(m_Ptr + off); }
	const_iterator operator - (difference_type off) /* const */ { return const_iterator(m_Ptr - off); }
// iterator difference 
	difference_type operator - (const const_iterator& other) {
		return m_Ptr - other.m_Ptr;
	}
// +=, -= 
	const_iterator& operator += (difference_type off) {
		if (off >= 0) while (--off) ++(*this);
		else while (++off) --(*this);
		return *this;
	}
	const_iterator& operator -= (difference_type off) {
		if (off >= 0) while (--off) --(*this);
		else while (++off) ++(*this);
		return *this;
	}
// comparison 
	bool operator == (const const_iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const const_iterator& other) const { return m_Ptr != other.m_Ptr; }
	bool operator < (const const_iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator <= (const const_iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator > (const const_iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator >= (const const_iterator& other) const { return m_Ptr >= other.m_Ptr; }
}; // ! class vector const_iterator

} // ! namespace ft
