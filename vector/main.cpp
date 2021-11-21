#include "vector.hpp"
#include <iostream>
#include <vector>

using namespace std;

// print 
template <typename T>
void	print(const std::vector<T>& v) {
	for (typename std::vector<T>::const_iterator it = v.begin(); it < v.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	cout << "std: size: " << v.size() << " cap: " << v.capacity() << '\n';
}

template <typename T>
void	print(const ft::vector<T>& v) {
	for (typename ft::vector<T>::iterator it = v.begin(); it < v.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	cout << "ft: size: " << v.size() << " cap: " << v.capacity() << '\n';
}

void	test1() // push, pop 
{
	ft::vector<char> a;
	std::vector<char> b;

	a.push_back('a'); b.push_back('b'); cout << "push\n";
	print(a); print(b);
	a.push_back('c'); b.push_back('d'); cout << "push\n";
	print(a); print(b);
	a.pop_back(); b.pop_back(); cout << "pop\n";
	print(a); print(b);
	a.pop_back(); b.pop_back(); cout << "pop\n";
	print(a); print(b);
	a.pop_back(); b.pop_back(); cout << "pop\n";
	print(a); print(b);
}

void	test2() // insert, erase 
{
	ft::vector<short> a;
	std::vector<short> b;

	a.insert(a.begin(), 3);
	b.insert(b.begin(), 3);
	print(a), print(b);
}

int main()
{
	test2();
}
