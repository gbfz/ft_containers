// #include "vector.hpp"
#include "../vector/vector.hpp" // TODO: delete 

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

private:
// data accessor 
	container_type		cont;

public:
// ctors, dtor 
	explicit stack(const Container& cont = Container()) {}
	stack(const stack& other): cont(other.cont) {}
	~stack() {}

// operator = 
	stack& operator = (const stack& other) {
		cont = other.cont;
		return *this;
	}

// top 
	reference top() { return cont.back(); }
	const_reference top() const { return cont.back(); }

// empty 
	bool empty() const { return cont.empty(); }

// size 
	size_type size() const { return cont.size(); }

// push 
	void push(const value_type& value) { cont.push_back(value); }

// pop 
	void pop() { cont.pop_back(); }

}; // ! stack 

// stack comparison 
template <typename T, class C>
inline bool operator ==
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return lhs.cont == rhs.cont;
}
template <typename T, class C>
inline bool operator !=
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return !(lhs.cont == rhs.cont);
}
template <typename T, class C>
inline bool operator <
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return lhs.cont < rhs.cont;
}
template <typename T, class C>
inline bool operator >
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return rhs.cont < lhs.cont;
}
template <typename T, class C>
inline bool operator <=
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return !(rhs.cont < lhs.cont);
}
template <typename T, class C>
inline bool operator >=
(const ft::stack<T, C>& lhs, const ft::stack<T, C>& rhs) {
	return !(lhs.cont < rhs.cont);
}

} // ! namespace ft
