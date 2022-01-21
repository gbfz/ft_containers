#pragma  once
#include <cstddef>

namespace ft {

struct false_type {};
struct true_type {};

// enable if 
template <bool, typename>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
	typedef T type;
};
// enable if same 
template <typename, typename, typename>
struct enable_if_same {};

template <typename T, typename C>
struct enable_if_same<T, T, C> {
	typedef C type;
};

// remove const 
template <typename T>
struct remove_const {
	typedef T type;
};

template <typename T>
struct remove_const<const T> {
	typedef T type;
};

// is_integral 
template <typename>
struct is_integral {
	enum { value = false };
	typedef false_type type;
};
template <>
struct is_integral<char> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<unsigned char> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<short> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<unsigned short> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<int> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<unsigned int> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<long> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<unsigned long> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<long long> {
	enum { value = true };
	typedef true_type type;
};
template <>
struct is_integral<unsigned long long> {
	enum { value = true };
	typedef true_type type;
};

} // ! namespace ft
