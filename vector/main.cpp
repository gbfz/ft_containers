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
}

template <typename T>
void	print(const ft::vector<T>& v) {
	for (typename ft::vector<T>::iterator it = v.begin(); it < v.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
}

void	test1()
{
	ft::vector<int> a;
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.push_back(1); cout << "push\n";
	print(a);
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.push_back(2); cout << "push\n";
	print(a);
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.pop_back(); cout << "pop\n";
	print(a);
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.pop_back(); cout << "pop\n";
	print(a);
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.pop_back(); cout << "pop\n";
	print(a);
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
}

void	test2()
{
	string str = "rrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbrobbobb";
	//std::vector<char> so(str.length());
	std::vector<char> so;
	so.insert(so.begin(), str.begin(), str.end());
	print(so);

	cout << "cap: " << so.capacity() << '\n';
	cout << "size: " << so.size() << '\n';
	cout << "strsize: " << str.size() << '\n';

	//ft::vector<char> s(str.length());
	ft::vector<char> s;
	try {
		s.insert(s.begin(), str.begin(), str.end());
	} catch (...) {
		cout << "fuck\n";
	}
	print(s);
	cout << "cap: " << s.capacity() << '\n';
	cout << "size: " << s.size() << '\n';
}

void	test3()
{
	ft::vector<char> a;
	std::vector<char> b;

	b.insert(b.end(), 'b');
	cout << b.front() << '\n';
	a.insert(a.end(), 'a');
	cout << a.front() << '\n';
}

int main()
{
	test2();
}
