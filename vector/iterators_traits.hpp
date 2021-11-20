#pragma		once
#include	<iterator>

namespace ft {

template <class Iterator>
struct iterators_traits {
	typedef typename Iterator::value_type		value_type;
	typedef typename Iterator::pointer		pointer;
	typedef typename Iterator::reference		reference;
	typedef typename Iterator::difference_type	difference_type;
	typedef typename Iterator::iterator_category	iterator_category;
}; // ! iterator_traits

template <class T>
struct iterators_traits<T*> {
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef std::ptrdiff_t			difference_type;
	typedef std::random_access_iterator_tag	iterator_category;
}; // ! iterators_traits pointer specialization

template <class T>
struct iterators_traits<const T*> {
	typedef T				value_type;
	typedef const T*			pointer;
	typedef const T&			reference;
	typedef std::ptrdiff_t			difference_type;
	typedef std::random_access_iterator_tag	iterator_category;
}; // ! iterators_traits const pointer specialization

} // ! namespace ft
