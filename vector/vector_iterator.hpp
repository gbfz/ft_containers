#pragma  once
#include <memory>
#include <stdexcept>
#include "vector_iterator_base_types.hpp"

namespace ft {

// std::distance analog 
template <class _iterator>
typename iterators_traits<_iterator>::difference_type
distance(_iterator first, _iterator last) {
	return last - first;
}

// normal iterator 
template <typename T>
class vector_iterator {
public:
// member type definitions 
	typedef iterators_traits<vector_iterator_base<T> >	traits;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
	typedef vector_iterator				iterator;
protected:
// pointer
	pointer m_Ptr;
public:
// ctors, dtor, = 
	vector_iterator(pointer ptr): m_Ptr(ptr) {}
	vector_iterator(const iterator& other): m_Ptr(other.m_Ptr) {}
	~vector_iterator() {}
	iterator& operator = (const iterator& other) {
		m_Ptr = other.m_Ptr;
		return *this;
	}
// *, ->, [] 
	reference operator * () const { return *m_Ptr; }
	pointer operator -> () const { return m_Ptr; }
	reference operator [] (difference_type offset) const {
		return *(m_Ptr + offset);
	}
// ++ 
	iterator& operator ++ () { ++m_Ptr; return *this; }
	iterator  operator ++ (int) {
		iterator it = *this;
		++(*this);
		return it;
	}
// + 
	iterator operator + (difference_type offset) const {
		return iterator(m_Ptr + offset);
	}
// -- 
	iterator& operator -- () { --m_Ptr; return *this; }
	iterator  operator -- (int) {
		iterator it = *this;
		--(*this);
		return it;
	}
// - 
	iterator operator - (difference_type offset) const {
		return iterator(m_Ptr - offset);
	}
	difference_type operator - (const iterator& other) const
	{
		difference_type n = std::distance(m_Ptr, other.m_Ptr);
		if (*this + n != other)
			throw std::out_of_range("Invalid iterator in - (2)");
		return n;
	}
// +=, -= 
	reference operator += (difference_type offs) {
		if (offs >= 0) while (offs--) ++(*this);
		else while (offs++) --(*this);
		return *this;
	}
	reference operator -= (difference_type offs) {
		if (offs >= 0) while (offs--) --(*this);
		else while (offs++) ++(*this);
		return *this;
	}
// <, >, <=, >=, ==, != 
	bool operator < (const iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) const { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) const { return m_Ptr != other.m_Ptr; }
}; // ! normal iterator

// const iterator 
template
<typename Type> class vector_const_iterator {
public:
// member type definitions 
	typedef iterators_traits<vector_iterator_base<Type> >	traits;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
	typedef vector_const_iterator			const_iterator;
protected:
// pointer
	pointer m_Ptr;
public:
// ctors, dtor, = 
	vector_const_iterator(): m_Ptr(0) {}
	vector_const_iterator(pointer ptr): m_Ptr(ptr) {}
	vector_const_iterator(const const_iterator& other): m_Ptr(other.m_Ptr) {}
	~vector_const_iterator() {}
	const_iterator& operator = (const const_iterator& other) {
		m_Ptr = other.m_Ptr;
	}
// *, ->, [] 
	const reference operator * () const { return *m_Ptr; }
	const pointer operator -> () const { return m_Ptr; }
	const reference operator [] (difference_type offset) const {
		return *(m_Ptr + offset);
	}
// ++ 
	const_iterator& operator ++ () { ++m_Ptr; return *this; }
	const_iterator  operator ++ (int) {
		const_iterator it = *this;
		++(*this);
		return it;
	}
// + 
	const_iterator operator + (difference_type offset) const {
		return const_iterator(m_Ptr + offset);
	}
// -- 
	const_iterator& operator -- () { --m_Ptr; return *this; }
	const_iterator  operator -- (int) {
		const_iterator it = *this;
		--(*this);
		return it;
	}
// - 
	const_iterator operator - (difference_type offset) const {
		return const_iterator(m_Ptr - offset);
	}
	difference_type operator - (const const_iterator& other) const
	{
		difference_type n = std::distance(m_Ptr, other.m_Ptr);
		if (*this + n != other)
			throw std::out_of_range("Invalid iterator in - (2)");
		return n;
	}
// +=, -= 
	const reference operator += (difference_type offs) {
		if (offs >= 0) while (offs--) ++(*this);
		else while (offs++) --(*this);
		return *this;
	}
	const reference operator -= (difference_type offs) {
		if (offs >= 0) while (offs--) --(*this);
		else while (offs++) ++(*this);
		return *this;
	}
// <, >, <=, >=, ==, != 
	bool operator < (const const_iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator > (const const_iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator <= (const const_iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const const_iterator& other) const { return m_Ptr >= other.m_Ptr; }
	bool operator == (const const_iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const const_iterator& other) const { return m_Ptr != other.m_Ptr; }
}; // ! const iterator

} // ! namespace ft
