#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print(vector<int> const& a) {
	for (int i = 0; i < a.size(); ++i)
		cout << a.at(i) << ' ';
	cout << '\n';
}

int main() {
	vector<int> a;
	for (int i = 1; i < 10; i += 2)
		a.push_back(i);
	print(a);
	copy(a.begin() + 1, a.end(), a.begin());
	print(a);
}
