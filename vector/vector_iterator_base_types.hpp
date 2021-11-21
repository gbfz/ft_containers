#pragma  once
#include <stddef.h>

namespace ft {

struct random_access_iterator_tag { };

/*
template
<typename _type,
 typename _category = random_access_iterator_tag,
 typename _distance = ptrdiff_t,
 typename _pointer = _type*,
 typename _reference = _type&>
struct vector_iterator_base {
	typedef _category	iterator_category;
	typedef _type		value_type;
	typedef _pointer	pointer;
	typedef _reference	reference;
	typedef _distance	difference_type;
}; // ! vector iterator base
*/

template <typename _vector>
struct vector_iterator_base {
	typedef random_access_iterator_tag		iterator_category;
	typedef typename _vector::value_type		value_type;
	typedef typename _vector::pointer		pointer;
	typedef typename _vector::reference		reference;
	typedef typename _vector::difference_type	difference_type;
}; // ! vector iterator base

template <typename _iterator>
struct iterators_traits {
	typedef typename _iterator::iterator_category	iterator_category;
	typedef typename _iterator::value_type		value_type;
	typedef typename _iterator::pointer		pointer;
	typedef typename _iterator::reference		reference;
	typedef typename _iterator::difference_type	difference_type;
}; // ! iterators traits

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
