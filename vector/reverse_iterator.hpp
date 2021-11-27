#pragma  once
#include "iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class reverse_iterator: public Iterator {
public:
// member types definitions 
	typedef Iterator				iterator_type;
	typedef iterator_traits<iterator_type>		traits;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
protected:
// underlying iterator 
	iterator_type	current;
public:
// constructors 
	reverse_iterator(): current(iterator_type()) {}
	reverse_iterator(iterator_type x): iterator_type(x), current(x) {}
	template <class T>
	reverse_iterator(const reverse_iterator& other):
		iterator_type(other.base()), current(other.base()) {}
// base 
	iterator_type	base() const { return current; }
// [] 
	reference	operator [] (difference_type n) const {
	}
};

} // ! namespace ft
