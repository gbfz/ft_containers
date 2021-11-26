#include "vector.hpp"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// print 
template <typename vector>
void	print(const vector& v, std::ostream& stream = std::cout) {
	for (typename vector::const_iterator it = v.begin();
	     it < v.end(); ++it)
		stream << *it << ' ';
	stream << '\n';
}

// test comparison 
template <typename T>
string	test_comparison(const ft::vector<T>& a,
			const ft::vector<T>& b,
			const std::vector<T>& sa,
			const std::vector<T>& sb) {
	if ((a == b) == (sa == sb) &&
	    (a != b) == (sa != sb) &&
	    (a <  b) == (sa <  sb) &&
	    (a >  b) == (sa >  sb) &&
	    (a <= b) == (sa <= sb) &&
	    (a >= b) == (sa >= sb))
		return "they're equal!";
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

// test properties 
template <typename T>
bool	test_property(const T& a, const T& b, bool silent = false) {
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
	return test_property(a.max_size(), b.max_size(), silent);
}
// compare size 
template <typename T>
bool	compare_size
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "size: ";
	return test_property(a.size(), b.size(), silent);
}
// compare cap 
template <typename T>
bool	compare_cap
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "capacity: ";
	return test_property(a.capacity(), b.capacity(), silent);
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
	return test_property(a.front(), b.front(), silent);
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
	return test_property(a.back(), b.back(), silent);
}
// compare empty 
template <typename T>
bool	compare_empty
(const std::vector<T>& a, const ft::vector<T>&b, bool silent = false) {
	!silent && cout << "empty: ";
	return test_property(a.empty(), b.empty(), silent);
}
// compare all members 
template <typename T>
void	compare_all_properties
(const std::vector<T>& a, const ft::vector<T>&b) {
	bool all_good;
	std::stringstream a_stream, b_stream;
	all_good = compare_max(a, b, true)   &
		   compare_cap(a, b, true)   &
		   compare_empty(a, b, true) &
		   compare_size(a, b, true)  &
		   compare_front(a, b, true) &
		   compare_back(a, b, true);
	print(a, a_stream); print(b, b_stream);
	all_good &= a_stream.str() == b_stream.str();
	cout << (all_good ? "all is good!" : "something went wrong") << '\n';
}

// constructors 
void	test_constructors() {
	// default 
	cout << "default:\n";
	{
		std::vector<string> a;
		 ft::vector<string> b;
		compare_all_properties(a, b);
		a.push_back("zdraste");
		b.push_back("zdraste");
		compare_all_properties(a, b);
	}
	// copy 
	cout << "\ncopy:\n";
	{
		 ft::vector<string> a;
		std::vector<string> sa;
		compare_all_properties(sa, a);
		a.insert(a.begin(), "nihuya sebe");
		sa.insert(sa.begin(), "nihuya sebe");
		compare_all_properties(sa, a);
		a.insert(a.begin() + 1, 8, "wow!!");
		sa.insert(sa.begin() + 1, 8, "wow!!");
		compare_all_properties(sa, a);
		 ft::vector<string> b(a);
		std::vector<string> sb(sa);
		compare_all_properties(sb, b);
		b.push_back("ehhh");
		sb.push_back("ehhh");
		b.push_back("ehhh");
		sb.push_back("ehhh");
		compare_all_properties(sb, b);
		b.pop_back();
		sb.pop_back();
		compare_all_properties(sb, b);
	}
	// with explicit allocator 
	cout << "\nexplicit(alloc):\n";
	{
		std::allocator<int> alloc;
		std::vector<char> a(alloc);
		 ft::vector<char> b(alloc);
		compare_all_properties(a, b);
		a.push_back('o');
		b.push_back('o');
		compare_all_properties(a, b);
		a.pop_back();
		b.pop_back();
		compare_all_properties(a, b);
	}
	// with count, value_type && alloc 
	cout << "\nwith count && value && alloc:\n";
	{
		size_t	count		= 15;
		string	value		= "жесть";
		std::allocator<string>	alloc;
		std::vector<string>	a(count, value, alloc);
		 ft::vector<string>	b(count, value, alloc);
		compare_all_properties(a, b);
		a.erase(a.begin(), a.end());
		b.erase(b.begin(), b.end());
		compare_all_properties(a, b);
	}
	// range constructor 
	cout << "\nwith range:\n";
	{
		std::vector<string> sa;
		 ft::vector<string> a;
		sa.insert(sa.begin(), 9, "420");
		a.insert(a.begin(), 9, "420");
		compare_all_properties(sa, a);
		std::vector<string> sb(sa.begin() + 2, sa.end() - 2);
		 ft::vector<string> b(a.begin() + 2, a.end() - 2);
		compare_all_properties(sb, b);
	}
}

// swap 
void	test_swap() {
	std::vector<int> sa, sb;
	 ft::vector<int> a, b;
	sa.insert(sa.begin(), 9, 420);
	sb.push_back(34);
	a.insert(a.begin(), 9, 420);
	b.push_back(34);
	compare_all_properties(sa, a);
	compare_all_properties(sb, b);
	swap(a, b);
	compare_all_properties(sa, a);
	compare_all_properties(sb, b);
	b.swap(a);
	compare_all_properties(sa, a);
	compare_all_properties(sb, b);
}

int main() {
	test_swap();
}
