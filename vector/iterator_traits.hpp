#pragma  once
#include <stddef.h>
#include </usr/include/c++/11.1.0/bits/stl_iterator_base_types.h> // TODO: gotta find a better way. just <iterator>?

namespace ft {

template <typename _container>
struct iterator_traits {
	typedef typename _container::iterator_category	iterator_category;
	typedef typename _container::value_type		value_type;
	typedef typename _container::pointer		pointer;
	typedef typename _container::reference		reference;
	typedef typename _container::difference_type	difference_type;
}; // ! iterator traits

template <typename T>
struct iterator_traits<T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef ptrdiff_t			difference_type;
}; // ! iterator traits<T*>

template <typename T>
struct iterator_traits<const T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef const T*			pointer;
	typedef const T&			reference;
	typedef ptrdiff_t			difference_type;
}; // ! iterator traits<const T*>

} // ! namespace ft
