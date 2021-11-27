#pragma  once
#include <cstddef>

struct range_type {};
struct fill_type {};

template <typename T>
struct is_size_type {
	typedef range_type type;
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
