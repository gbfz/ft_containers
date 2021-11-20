#pragma		once
#include	<iterator>

namespace ft {

template <class Iterator>
struct iterators_traits {
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type		value_type;
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::pointer		pointer;
	typedef typename Iterator::reference		reference;
}; // ! iterator_traits

template <class T>
struct iterators_traits<T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef std::ptrdiff_t			difference_type;
	typedef T*				pointer;
	typedef T&				reference;
}; // ! iterators_traits<T*>

template <class T>
struct iterators_traits<const T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T				value_type;
	typedef std::ptrdiff_t			difference_type;
	typedef const T*			pointer;
	typedef const T&			reference;
}; // ! iterators_traits<const T*>

} // ! namespace ft
