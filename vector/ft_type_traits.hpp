#pragma  once
#include <cstddef>

namespace ft{

struct false_type {};
struct true_type {};

template <typename, typename>
struct are_same_type {
	typedef false_type type;
};
template <typename T>
struct are_same_type<T, T> {
	typedef true_type type;
};

struct fill_type {};

template <typename T>
struct is_size_type {
	typedef false_type type;
};
template <>
struct is_size_type<unsigned long long> {
	typedef fill_type type;
};
template <>
struct is_size_type<long long> {
	typedef fill_type type;
};
template <>
struct is_size_type<size_t> {
	typedef fill_type type;
};
template <>
struct is_size_type<long> {
	typedef fill_type type;
};
template <>
struct is_size_type<unsigned int> {
	typedef fill_type type;
};
template <>
struct is_size_type<int> {
	typedef fill_type type;
};
template <>
struct is_size_type<short> {
	typedef fill_type type;
};
template <>
struct is_size_type<char> {
	typedef fill_type type;
};

} // ! namespace ft
