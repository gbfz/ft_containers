#include "vector.hpp"
#include <iostream>
#include <vector>

using namespace std;

void	test1()
{
	ft::vector<int> a;
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.push_back(15);
	cout << *a.begin() << '\n';
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.push_back(20);
	cout << *a.begin() << '\n';
	cout << *(a.end() - 1) << '\n';
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.pop_back();
	cout << *(a.end() - 1) << '\n';
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	a.pop_back();
	cout << "a size: " << a.size() << '\n';
	cout << "a capacity: " << a.capacity() << '\n';
	vector<int> b;
	b.push_back(15);
	b.push_back(20);
	b.pop_back();
	b.pop_back();
	cout << "b size: " << b.size() << '\n';
	cout << "b capacity: " << b.capacity() << '\n';
}

void	test2()
{
	string str = "robb";
	ft::vector<char> s(str.length());
	s.insert(s.begin() + str.length(), str.begin(), str.end());
}

int main()
{
	test2();
}
