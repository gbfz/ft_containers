#pragma		once
#include	"iterators_traits.hpp"

namespace ft {

// normal iterator
template <class vector> class vector_iterator {

public:
// member types definitions 
	typedef iterators_traits<vector>	trait;
	typedef typename trait::value_type	value_type;
	typedef typename trait::difference_type difference_type;
	typedef typename trait::pointer		pointer;
	typedef typename trait::reference	reference;
	typedef const pointer			const_pointer;
	typedef const reference			const_reference;
	typedef vector_iterator			iterator;
	typedef typename trait::iterator_category iterator_category;
protected:
	pointer	m_Ptr;
public:
// ctors, =, dtor 
	 vector_iterator(pointer ptr): m_Ptr(ptr) {}
	 vector_iterator(const iterator& other): m_Ptr(other.m_Ptr) {}
	 iterator& operator = (const iterator& other) {
		 m_Ptr = other.m_Ptr;
	 }
	 ~vector_iterator() {}
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
		difference_type n = std::distance(m_Ptr, other.m_Ptr);
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
	bool operator < (const iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) const { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) const { return m_Ptr != other.m_Ptr; }
};
// ! normal iterator

// const_iterator
template <class vector> class vector_const_iterator {
public:
// member types definitions 
	typedef iterators_traits<vector>	trait;
	typedef typename trait::value_type	value_type;
	typedef typename trait::difference_type difference_type;
	typedef typename trait::pointer		pointer;
	typedef typename trait::reference	reference;
	typedef const pointer			const_pointer;
	typedef const reference			const_reference;
	typedef vector_const_iterator		const_iterator;
	typedef typename trait::iterator_category iterator_category;
protected:
	pointer	m_Ptr;
public:
// ctors, =, dtor 
	vector_const_iterator(pointer ptr): m_Ptr(ptr) {}
	vector_const_iterator(vector_iterator<vector>& other):
		m_Ptr(other.m_Ptr) {}
	vector_const_iterator(const_iterator& other): m_Ptr(other.m_Ptr) {}
	const_iterator& operator = (const_iterator& other) {
		m_Ptr = other.m_Ptr;
	}
	~vector_const_iterator() {}
// *, ->, [] 
	const_reference operator * () { return *m_Ptr; }
	const_pointer operator -> () { return m_Ptr; }
	const_reference operator [] (difference_type offset) {
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
	difference_type operator - (const_iterator& other) const
	{
		difference_type n = std::distance(m_Ptr, other.m_Ptr);
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
	bool operator < (const_iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator > (const_iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator <= (const_iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const_iterator& other) const { return m_Ptr >= other.m_Ptr; }
	bool operator == (const_iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const_iterator& other) const { return m_Ptr != other.m_Ptr; }
};
// ! const iterator

// reverse iterator
template <class vector> class vector_reverse_iterator {

public:
// member types definitions 
	typedef iterators_traits<vector>	trait;
	typedef typename trait::value_type	value_type;
	typedef typename trait::difference_type difference_type;
	typedef typename trait::pointer		pointer;
	typedef typename trait::reference	reference;
	typedef const pointer			const_pointer;
	typedef const reference			const_reference;
	typedef vector_reverse_iterator		reverse_iterator;
	typedef typename trait::iterator_category iterator_category;
protected:
	pointer	m_Ptr;
public:
// ctors, =, dtor 
	vector_reverse_iterator(pointer ptr): m_Ptr(ptr) {}
	template <typename Iterator>
	vector_reverse_iterator(const Iterator& other): m_Ptr(other) {}
	template <typename Iterator>
	reverse_iterator& operator = (const Iterator& other) {
		m_Ptr = other;
	}
	~vector_reverse_iterator() {}
// *, ->, [] 
	reference operator * () { return *m_Ptr; }
	pointer operator -> () { return m_Ptr; }
	reference operator [] (difference_type offset) {
		return *(m_Ptr + offset);
	}
// ++ 
	reverse_iterator& operator ++ () { --m_Ptr; return *this; }
	reverse_iterator  operator ++ (int) {
		reverse_iterator it = *this;
		--(*this);
		return it;
	}
// + 
	reverse_iterator operator + (difference_type offset) const {
		return reverse_iterator(m_Ptr - offset);
	}
// -- 
	reverse_iterator& operator -- () { ++m_Ptr; return *this; }
	reverse_iterator  operator -- (int) {
		reverse_iterator it = *this;
		++(*this);
		return it;
	}
// - 
	reverse_iterator operator - (difference_type offset) const {
		return reverse_iterator(m_Ptr + offset);
	}
	difference_type operator - (const reverse_iterator& other) const
	{
		difference_type n = std::distance(m_Ptr, other.m_Ptr);
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
	bool operator < (const reverse_iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator > (const reverse_iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator <= (const reverse_iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const reverse_iterator& other) const { return m_Ptr >= other.m_Ptr; }
	bool operator == (const reverse_iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const reverse_iterator& other) const { return m_Ptr != other.m_Ptr; }
};
// ! reverse iterator

// const reverse iterator XXX TODO: coplien form, rename type XXX
template <class vector> class vector_const_reverse_iterator {
public:
// member types definitions 
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
		difference_type n = std::distance(m_Ptr, other.m_Ptr);
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
	bool operator < (const iterator& other) const { return m_Ptr < other.m_Ptr; }
	bool operator > (const iterator& other) const { return m_Ptr > other.m_Ptr; }
	bool operator <= (const iterator& other) const { return m_Ptr <= other.m_Ptr; }
	bool operator >= (const iterator& other) const { return m_Ptr >= other.m_Ptr; }
	bool operator == (const iterator& other) const { return m_Ptr == other.m_Ptr; }
	bool operator != (const iterator& other) const { return m_Ptr != other.m_Ptr; }
}; // ! const reverse iterator

} // ! namespace ft
