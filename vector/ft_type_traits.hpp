#pragma  once
#include <cstddef>

namespace ft {

struct false_type {};
struct true_type {};

template <bool, typename>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};

template <typename, typename>
struct are_same_type {
	enum { value = false };
	typedef false_type type;
};
template <typename T>
struct are_same_type<T, T> {
	enum { value = true };
	typedef true_type type;
};

template <typename T>
struct is_integral {
	typedef false_type type;
};
template <>
struct is_integral<unsigned long long> {
	typedef true_type type;
};
template <>
struct is_integral<long long> {
	typedef true_type type;
};
template <>
struct is_integral<size_t> {
	typedef true_type type;
};
template <>
struct is_integral<long> {
	typedef true_type type;
};
template <>
struct is_integral<unsigned int> {
	typedef true_type type;
};
template <>
struct is_integral<int> {
	typedef true_type type;
};
template <>
struct is_integral<short> {
	typedef true_type type;
};
template <>
struct is_integral<char> {
	typedef true_type type;
};

} // ! namespace ft
