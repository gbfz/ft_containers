#pragma  once
#include <memory>
#include <stdexcept>
#include "iterator_base_types.hpp"

namespace ft {

template <typename _Iterator, typename _Container>
class _normal_iterator {
protected:
// underlying memory accessor (pointer/iterator) 
	_Iterator				_base;
// traits typedef :) 
	typedef iterator_traits<_Iterator>	traits;
public:
// member types definitions 
	typedef _Iterator				iterator_type;
	typedef typename traits::iterator_category	iterator_category;
	typedef typename traits::value_type		value_type;
	typedef typename traits::difference_type	difference_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
// constructors, destructor 
	_normal_iterator(): _base(iterator_type()) {}
}; // ! class normal iterator

} // ! namespace ft
