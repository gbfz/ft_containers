#pragma  once

namespace ft {

template <class T1, class T2>
struct pair {
// member fields 
	T1 first;
	T2 second;
// constructors 
	pair(): // {
		first(T1()), second(T2()) {
	}
	pair(const T1& _f, const T2& _s):
		first(_f), second(_s) {
	}
	template <class U1, class U2>
	pair(const pair<U1, U2>& p):
		first(p.first), second(p.second) {
	}
// = 
	pair& operator = (const pair& other) {
		first = other.first;
		second = other.second;
		return *this;
	}
}; // ! struct pair

// make pair 
template <class T1, class T2>
ft::pair<T1, T2>
make_pair(T1 t, T2 u) {
	return pair<T1, T2>(t, u);
}

// pair comparison 
template <class T1, class T2>
inline bool
operator == (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}
template <class T1, class T2>
inline bool
operator != (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
	return !(lhs == rhs);
}
template <class T1, class T2>
inline bool
operator < (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
	return (lhs.first < rhs.first) ||
		((lhs.first == rhs.first) && (lhs.second < rhs.second));
}
template <class T1, class T2>
inline bool
operator > (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
	return rhs < lhs;
}
template <class T1, class T2>
inline bool
operator <= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
	return !(rhs < lhs);
}
template <class T1, class T2>
inline bool
operator >= (const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) {
	return !(lhs < rhs);
}

} // ! namespace ft
