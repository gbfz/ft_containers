#pragma  once
#include <stddef.h>

namespace ft {

struct random_access_iterator_tag { };

template <typename _container>
struct iterators_traits {
	typedef typename _container::iterator_category	iterator_category;
	typedef typename _container::value_type		value_type;
	typedef typename _container::pointer		pointer;
	typedef typename _container::reference		reference;
	typedef typename _container::difference_type	difference_type;
};

template <typename T>
struct iterators_traits<T*> {
	typedef random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef ptrdiff_t			difference_type;
}; // ! iterators traits<T*>

template <typename T>
struct iterators_traits<const T*> {
	typedef random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef const T*			pointer;
	typedef const T&			reference;
	typedef ptrdiff_t			difference_type;
}; // ! iterators traits<const T*>

} // ! namespace ft
