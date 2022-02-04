#include <vector>
#include "vector/Vector.hpp"
#include <stack>
#include "stack/Stack.hpp"
#include <map>
#include "map/Map.hpp"
#include <set>
#include "set/Set.hpp"
#include <iostream>

clock_t START_TIMER;

clock_t tic() {
	return START_TIMER = clock();
}
void toc(clock_t start = START_TIMER) {
	std::cout << "Elapsed time: "
	<< (clock() - start) / (double)CLOCKS_PER_SEC << "s\n";
}

void test_vector_speed() {
	std::vector<std::string> std_vec;
	ft::vector<std::string> ft_vec;
	int i;
	std::cout << "std::vector:" << std::endl;
	tic();
	for (i = 0; i < 90000; ++i)
		std_vec.push_back("wow");
	for (i = 0; i < 100; ++i)
		std_vec.insert(std_vec.begin(), "yeah");
	for (i = 0; i < 100; ++i)
		std_vec.erase(std_vec.begin());
	while (!std_vec.empty())
		std_vec.pop_back();
	toc();
	std::cout << "ft::vector:" << std::endl;
	tic();
	for (i = 0; i < 90000; ++i)
		ft_vec.push_back("wow");
	for (i = 0; i < 100; ++i)
		ft_vec.insert(ft_vec.begin(), "yeah");
	for (i = 0; i < 100; ++i)
		ft_vec.erase(ft_vec.begin());
	while (!ft_vec.empty())
		ft_vec.pop_back();
	toc();
}

void test_stack_speed() {
	std::stack<int> std_stack;
	ft::stack<int> ft_stack;
	int i;
	std::cout << "std::stack:" << std::endl;
	tic();
	for (i = 0; i < 1000000; ++i)
		std_stack.push(i);
	while (!std_stack.empty())
		std_stack.pop();
	toc();
	std::cout << "ft::stack:" << std::endl;
	tic();
	for (i = 0; i < 1000000; ++i)
		ft_stack.push(i);
	while (!ft_stack.empty())
		ft_stack.pop();
	toc();
}

void test_map_speed() {
	size_t i;
	const size_t size = 100000;
	const size_t msize = size * 10;
	std::vector<std::pair<int, std::string> > a(size);
	ft::vector<ft::pair<int, std::string> > b(size);
	for (i = 0; i < size; ++i) {
		a[i] = std::make_pair(i, "net");
		b[i] = ft::make_pair(i, "net");
	}
	std::cout << "std::map :" << std::endl;
	tic();
	{
		std::map<int, std::string> std_map;
		for (i = size; i < msize; ++i)
			std_map.insert(std::make_pair(i, "ogo"));
		std_map.insert(a.begin(), a.end());
		std_map.erase(std_map.find(10), std_map.find(90));
	}
	toc();
	std::cout << "ft::map :" << std::endl;
	tic();
	ft::map<int, std::string> ft_map;
	{
		ft::map<int, std::string> ft_map;
		for (i = size; i < msize; ++i)
			ft_map.insert(ft::make_pair(i, "ogo"));
		ft_map.insert(b.begin(), b.end());
		ft_map.erase(ft_map.find(10), ft_map.find(90));
	}
	toc();
}

void test_set_speed() {
	size_t i;
	const size_t size = 100000;
	const size_t msize = size * 10;
	std::vector<long> a(size);
	ft::vector<long> b(size);
	for (i = 0; i < size; ++i) {
		a[i] = i;
		b[i] = i;
	}
	std::cout << "std::set :" << std::endl;
	tic();
	{
		std::set<long> std_set;
		for (i = size; i < msize; ++i)
			std_set.insert(i);
		std_set.insert(a.begin(), a.end());
		std_set.erase(std_set.find(10), std_set.find(90));
	}
	toc();
	std::cout << "ft::map :" << std::endl;
	tic();
	{
		ft::set<long> ft_set;
		for (i = size; i < msize; ++i)
			ft_set.insert(i);
		ft_set.insert(b.begin(), b.end());
		ft_set.erase(ft_set.find(10), ft_set.find(90));
	}
	toc();
}

int main() {
	test_vector_speed();
	// test_stack_speed();
	// test_map_speed();
	// test_set_speed();
}
