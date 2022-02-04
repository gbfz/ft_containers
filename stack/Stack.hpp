#include "../vector/Vector.hpp"

namespace ft {

template <typename T, class Container = ft::vector<T> >
class stack {
public:
// member types definition 
	typedef T				value_type;
	typedef typename Container::size_type	size_type;
	typedef typename Container::reference	reference;
	typedef typename Container::const_reference
						const_reference;
	typedef Container			container_type;

protected:
// data accessor 
	container_type		c;

public:
// ctors, dtor 
	explicit stack(const Container& other_c = Container()): c(other_c) {}
	stack(const stack& other): c(other.c) {}
	~stack() {}

// operator = 
	stack& operator = (const stack& other) {
		if (this == &other) return *this;
		c = other.c;
		return *this;
	}

// top 
	reference top() { return c.back(); }
	const_reference top() const { return c.back(); }

// empty 
	bool empty() const { return c.empty(); }

// size 
	size_type size() const { return c.size(); }

// push 
	void push(const value_type& value) { c.push_back(value); }

// pop 
	void pop() { c.pop_back(); }

// friend operator overloads 
	template <typename Tp, class C>
	friend bool operator ==
	(const ft::stack<Tp, C>& lhs, const ft::stack<Tp, C>& rhs);
	template <typename Tp, class C>
	friend bool operator <
	(const ft::stack<Tp, C>& lhs, const ft::stack<Tp, C>& rhs);

}; // ! stack 

// stack comparison 
template <typename T, class C>
bool operator ==
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return lhs.c == rhs.c;
}
template <typename T, class C>
bool operator !=
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return !(lhs == rhs);
}
template <typename T, class C>
bool operator <
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return lhs.c < rhs.c;
}
template <typename T, class C>
bool operator >
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return rhs < lhs;
}
template <typename T, class C>
bool operator <=
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return !(rhs < lhs);
}
template <typename T, class C>
bool operator >=
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return !(lhs < rhs);
}

} // ! namespace ft
