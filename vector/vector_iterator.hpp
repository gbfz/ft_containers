#pragma		once
#include	"iterators_traits.hpp"

namespace ft {

// normal iterator
template <class vector> class vector_iterator {

public:	// member types definitions
	typedef std::random_access_iterator_tag		iterator_category;
	typedef vector_iterator				iterator;
	typedef typename vector::value_type		value_type;
	typedef value_type*				pointer;
	typedef value_type&				reference;
	typedef typename vector::difference_type	difference_type;
	typedef typename vector::size_type		size_type;

protected:
	pointer	m_Ptr;
public:
// default ctor. copy, =, and ~ are left implicit
	vector_iterator(pointer ptr): m_Ptr(ptr) {}
// *, ->, []
	reference operator * () { return *m_Ptr; }
	pointer operator -> () { return m_Ptr; }
	reference operator [] (difference_type offset) {
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
		difference_type n = std::distance(other, *this);
		if (*this + n != other)
			throw std::out_of_range("Invalid iterator in - (2)");
		return n;
	}
// +=, -=
	reference operator += (difference_type offset) {
		difference_type m = offset;
		if (m >= 0) while (m--) ++(*this);
		else while (m++) --(*this);
		return *this;
	}
	reference operator -= (difference_type offset) {
		// TODO: check overflow
		return this += -offset;
	}
// <, >, <=, >=, ==, !=
	bool operator < (const iterator& other) { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) { return m_Ptr != other.m_Ptr; }
};
// ! normal iterator



// reverse iterator
template <class vector> class vector_reverse_iterator {

public:	// member types definitions
	typedef std::random_access_iterator_tag		iterator_category;
	typedef vector_reverse_iterator			iterator;
	typedef typename vector::value_type		value_type;
	typedef value_type*				pointer;
	typedef value_type&				reference;
	typedef typename vector::difference_type	difference_type;
	typedef typename vector::size_type		size_type;

protected:
	pointer	m_Ptr;
public:
// default ctor. copy, =, and ~ are left implicit
	vector_reverse_iterator(pointer ptr): m_Ptr(ptr) {}
// *, ->, []
	reference operator * () { return *m_Ptr; }
	pointer operator -> () { return m_Ptr; }
	reference operator [] (difference_type offset) {
		return *(m_Ptr + offset);
	}
// ++
	iterator& operator ++ () { --m_Ptr; return *this; }
	iterator  operator ++ (int) {
		iterator it = *this;
		--(*this);
		return it;
	}
// +
	iterator operator + (difference_type offset) const {
		return iterator(m_Ptr - offset);
	}
// --
	iterator& operator -- () { ++m_Ptr; return *this; }
	iterator  operator -- (int) {
		iterator it = *this;
		++(*this);
		return it;
	}
// -
	iterator operator - (difference_type offset) const {
		return iterator(m_Ptr + offset);
	}
	difference_type operator - (const iterator& other) const
	{
		difference_type n = std::distance(other, *this);
		if (*this + n != other)
			throw std::out_of_range("Invalid iterator in + (r)");
		return n;
	}
// +=, -=
	reference operator += (difference_type offset) {
		difference_type m = offset;
		if (m >= 0) while (m--) --(*this);
		else while (m++) ++(*this);
		return *this;
	}
	reference operator -= (difference_type offset) {
		// TODO: check overflow
		return this += -offset;
	}
// <, >, <=, >=, ==, !=
	bool operator < (const iterator& other) { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) { return m_Ptr != other.m_Ptr; }
};
// ! reverse iterator



// const_iterator
template <class vector> class vector_const_iterator {
public:	// member types definitions
	typedef std::random_access_iterator_tag		iterator_category;
	typedef vector_const_iterator			iterator;
	typedef typename vector::value_type		value_type;
	typedef value_type*				pointer;
	typedef const value_type*			const_pointer;
	typedef value_type&				reference;
	typedef const value_type&			const_reference;
	typedef typename vector::difference_type	difference_type;
	typedef typename vector::size_type		size_type;

protected:
	pointer	m_Ptr;
public:
// default ctor. copy, =, and ~ are left implicit
	vector_const_iterator(pointer ptr): m_Ptr(ptr) {}
// *, ->, []
	const_reference operator * () { return *m_Ptr; }
	const_pointer operator -> () { return m_Ptr; }
	const_reference operator [] (difference_type offset) {
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
		difference_type n = std::distance(other, *this);
		if (*this + n != other)
			throw std::out_of_range("Invalid iterator in - (2)");
		return n;
	}
// +=, -=
	const_reference operator += (difference_type offset) {
		difference_type m = offset;
		if (m >= 0) while (m--) ++(*this);
		else while (m++) --(*this);
		return *this;
	}
	const_reference operator -= (difference_type offset) {
		// TODO: check overflow
		return this += -offset;
	}
// <, >, <=, >=, ==, !=
	bool operator < (const iterator& other) { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) { return m_Ptr != other.m_Ptr; }
};
// ! const iterator



// const reverse iterator
template <class vector> class vector_const_reverse_iterator {
public:	// member types definitions
	typedef std::random_access_iterator_tag		iterator_category;
	typedef vector_const_reverse_iterator		iterator;
	typedef typename vector::value_type		value_type;
	typedef value_type*				pointer;
	typedef const value_type*			const_pointer;
	typedef const value_type&			const_reference;
	typedef typename vector::difference_type	difference_type;
	typedef typename vector::size_type		size_type;

protected:
	pointer	m_Ptr;
public:
// default ctor. copy, =, and ~ are left implicit
	vector_const_reverse_iterator(pointer ptr): m_Ptr(ptr) {}
// *, ->, []
	const_reference operator * () { return *m_Ptr; }
	const_pointer operator -> () { return m_Ptr; }
	const_reference operator [] (difference_type offset) {
		return *(m_Ptr + offset);
	}
// ++
	iterator& operator ++ () { --m_Ptr; return *this; }
	iterator  operator ++ (int) {
		iterator it = *this;
		--(*this);
		return it;
	}
// +
	iterator operator + (difference_type offset) const {
		return iterator(m_Ptr - offset);
	}
// --
	iterator& operator -- () { ++m_Ptr; return *this; }
	iterator  operator -- (int) {
		iterator it = *this;
		++(*this);
		return it;
	}
// -
	iterator operator - (difference_type offset) const {
		return iterator(m_Ptr + offset);
	}
	difference_type operator - (const iterator& other) const
	{
		difference_type n = std::distance(other, *this);
		if (*this + n != other)
			throw std::out_of_range("Invalid iterator in + (r)");
		return n;
	}
// +=, -=
	const_reference operator += (difference_type offset) {
		difference_type m = offset;
		if (m >= 0) while (m--) --(*this);
		else while (m++) ++(*this);
		return *this;
	}
	const_reference operator -= (difference_type offset) {
		// TODO: check overflow
		return this += -offset;
	}
// <, >, <=, >=, ==, !=
	bool operator < (const iterator& other) { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) { return m_Ptr != other.m_Ptr; }
}; // ! const reverse iterator

} // ! namespace ft
