#include "vector.hpp"
#include <iostream>
#include <vector>

using namespace std;

// print 
template <typename T>
void	print(const std::vector<T>& v) {
	cout << "std: ";
	for (typename std::vector<T>::const_iterator it = v.begin(); it < v.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	cout << "size: " << v.size() << " cap: " << v.capacity() << "\n\n";
}

template <typename T>
void	print(const ft::vector<T>& v) {
	cout << "ft: ";
	for (typename ft::vector<T>::const_iterator it = v.begin(); it < v.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	cout << "size: " << v.size() << " cap: " << v.capacity() << "\n\n";
}

// test comparison 
template <typename T>
string	test_comparison(const ft::vector<T>& a,
			const ft::vector<T>& b,
			const std::vector<T>& sa,
			const std::vector<T>& sb) {
	if ((a == b) == (sa == sb) &&
		(a != b) == (sa != sb) &&
		 (a < b) == (sa < sb)  &&
		 (a > b) == (sa > sb)  &&
		(a <= b) == (sa <= sb) &&
		(a >= b) == (sa >= sb)
	   ) return "they're equal!";
	return "something went wrong:(";
}

// test comparison on self 
template <typename vector>
string	test_comparison_with_self(const vector& v) {
	if (v == v && v <= v && v >= v &&
	    !(v < v || v > v || v != v))
		return "all's well!";
	return "WHAT";
}

// test member fields  
template <typename T>
bool	test_parameter(const T& a, const T& b, bool silent = false) {
	if (a == b) {
		!silent && cout << "good\n";
		return true;
	}
	if (silent) return false;
	cout << "bad\n";
	cout << "std: " << a << '\n';
	cout << " ft: " << b << '\n';
	return false;
}
// compare max 
template <typename T>
bool	compare_max
(const std::vector<T>& a, const ft::vector<T>& b, bool silent = false) {
	!silent && cout << "max: ";
	return test_parameter(a.max_size(), b.max_size(), silent);
}
// compare size 
template <typename T>
bool	compare_size
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "size: ";
	return test_parameter(a.size(), b.size(), silent);
}
// compare cap 
template <typename T>
bool	compare_cap
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "capacity: ";
	return test_parameter(a.capacity(), b.capacity(), silent);
}
// compare front 
template <typename T>
bool	compare_front
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "front: ";
	if (a.empty() & b.empty()) {
		!silent && cout << "good\n";
		return true;
	}
	if (a.empty() ^ b.empty()) {
		!silent && cout << "front bad\n";
		return false;
	}
	return test_parameter(a.front(), b.front(), silent);
}
// compare back 
template <typename T>
bool	compare_back
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "back: ";
	if (a.empty() & b.empty()) {
		!silent && cout << "good\n";
		return true;
	}
	if (a.empty() ^ b.empty()) {
		!silent && cout << "back bad\n";
		return false;
	}
	return test_parameter(a.back(), b.back(), silent);
}
// compare empty 
template <typename T>
bool	compare_empty
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "empty: ";
	return test_parameter(a.empty(), b.empty(), silent);
}
// compare all members 
template <typename T>
void	compare_all_members
(const std::vector<T>& a, const ft::vector<T>&b) {
	if (   compare_max(a, b, true) && compare_cap(a, b, true)
	    && compare_empty(a, b, true) && compare_size(a, b, true)
	    && compare_front(a, b, true) && compare_back(a, b, true))
		cout << "all is good!\n";
	else cout << "something went wrong\n";
}
// compare iterators 
template <typename T>
void	compare_iterators
(const std::vector<T>& a, const ft::vector<T>& b) {
	typename std::vector<T>::difference_type ad;
	typename  ft::vector<T>::difference_type bd;
	ad = std::distance(a.begin(), a.end());
	bd = std::distance(b.begin(), b.end());
	cout << "iterators: ";
	if (a.end() == a.begin() + ad &&
	    b.end() == b.begin() + bd)
		cout << "good\n";
	else cout << "bad\n";
}

// test max size 
void	test_max_size() { 
	std::vector<int> std_i;
	ft::vector<int> ft_i;
	compare_max(std_i, ft_i);
	std::vector<short> std_sh;
	ft::vector<short> ft_sh;
	compare_max(std_sh, ft_sh);
	std::vector<char> std_ch;
	ft::vector<char> ft_ch;
	compare_max(std_ch, ft_ch);
	std::vector<string> std_s;
	ft::vector<string> ft_s;
	compare_max(std_s, ft_s);
	std::vector<ft::vector<std::random_access_iterator_tag> > std_v_i;
	ft::vector<ft::vector<std::random_access_iterator_tag> > ft_v_i;
	compare_max(std_v_i, ft_v_i);
}

// constructors 
void	test_constructors() {
	// default
	{
		std::vector<string> a(1);
		 ft::vector<string> b(1);
		compare_iterators(a, b);
		compare_all_members(a, b);
		a.resize(32, "aboba");
		b.resize(32, "aboba");
		compare_all_members(a, b);
		compare_iterators(a, b);
		a.insert(a.begin(), "bernard");
		b.insert(b.begin(), "bernard");
		compare_all_members(a, b);
		compare_iterators(a, b);
	}
}

int main() {
	test_constructors();
}
