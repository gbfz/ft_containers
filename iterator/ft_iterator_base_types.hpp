#pragma  once
#include <bits/stl_iterator_base_types.h> // TODO: is this right ?

namespace ft {

template <typename iterator>
struct iterator_traits {
	typedef typename iterator::iterator_category	iterator_category;
	typedef typename iterator::value_type		value_type;
	typedef typename iterator::pointer		pointer;
	typedef typename iterator::reference		reference;
	typedef typename iterator::difference_type	difference_type;
}; // ! iterator traits

template <typename T>
struct iterator_traits<T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef std::ptrdiff_t			difference_type;
}; // ! iterator traits<T*>

template <typename T>
struct iterator_traits<const T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef const T*			pointer;
	typedef const T&			reference;
	typedef std::ptrdiff_t			difference_type;
}; // ! iterator traits<const T*>

} // ! namespace ft
