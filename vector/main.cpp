#include "vector.hpp"
#include <iostream>
#include <vector>

using namespace std;

template <class vector>
void	print(const vector& v) {
	for (typename vector::const_iterator it = v.begin(); it < v.end(); ++it)
		cout << *it;// << ' ';
	cout << '\n';
}

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
	test3();
}
