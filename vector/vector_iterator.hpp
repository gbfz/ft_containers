#pragma  once
#include <memory>
#include <stdexcept>
#include "iterator_traits.hpp"

namespace ft {

// iterator 
template <typename _iterator> // could be a pointer or an iterator of different type or whatever 
class vector_iterator {
// type name shortcut 
typedef vector_iterator	iterator;
public:
// member types definitions 
	typedef iterator_traits<_iterator>		traits;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
protected:
// pointer 
	pointer m_Ptr;
public:
// ctors, =, dtor 
	vector_iterator(): m_Ptr(0) {}
	vector_iterator(pointer ptr): m_Ptr(ptr) {}
	vector_iterator(const iterator& other): m_Ptr(other.m_Ptr) {}
	iterator& operator = (const iterator& other) {
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
	iterator& operator ++ () { ++m_Ptr; return *this; }
	iterator  operator ++ (int) {
		pointer inc = m_Ptr;
		++(*this);
		return iterator(inc);
	}
// -- 
	iterator& operator -- () { --m_Ptr; return *this; }
	iterator  operator -- (int) {
		pointer dec = m_Ptr;
		--(*this);
		return iterator(dec);
	}
// offset sum, difference 
	iterator operator + (difference_type off) /* const */ { return iterator(m_Ptr + off); }
	iterator operator - (difference_type off) /* const */ { return iterator(m_Ptr - off); }
// iterator difference 
	difference_type operator - (const iterator& other) {
		return m_Ptr - other.m_Ptr;
	}
// +=, -= 
	iterator& operator += (difference_type off) {
		if (off >= 0) while (--off) ++(*this);
		else while (++off) --(*this);
		return *this;
	}
	iterator& operator -= (difference_type off) {
		if (off >= 0) while (--off) --(*this);
		else while (++off) ++(*this);
		return *this;
	}
// comparison 
	bool operator == (const iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) const { return m_Ptr != other.m_Ptr; }
	bool operator < (const iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator <= (const iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator > (const iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator >= (const iterator& other) const { return m_Ptr >= other.m_Ptr; }
}; // ! class vector iterator

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
	typedef const typename traits::pointer		const_pointer;
	typedef const typename traits::reference	const_reference;
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
