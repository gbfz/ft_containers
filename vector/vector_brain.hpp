#pragma	 once
#include <algorithm>
#include <limits>
#include "vector_iterator.hpp"

namespace ft {

template <class vector>
class vector_brain {

public:
// member types declarations 
	typedef typename vector::allocator_type		allocator_type;
	typedef typename vector::value_type		value_type;
	typedef typename vector::pointer		pointer;
	typedef typename vector::const_pointer		const_pointer;
	typedef typename vector::reference		reference;
	typedef typename vector::const_reference	const_reference;
	typedef typename vector::size_type		size_type;
	typedef typename vector::difference_type	difference_type;
	typedef typename vector::iterator_category	iterator_category;
	typedef vector_iterator<vector_brain<vector> >	iterator;
	typedef const iterator				const_iterator;
protected:
// member fields 
	allocator_type	_alloc;
	pointer		_mem;
	pointer		_memend;
	size_type	_size;
	size_type	_capacity;
	difference_type	_max;
public:
// constructors 
// default constructor
	vector_brain(): _alloc(allocator_type()),
		_size(0), _capacity(2) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem;
		_max = std::numeric_limits<value_type>::max();
	}
// parametrized constructor
	vector_brain(size_type new_cap):
			_alloc(allocator_type()),
			_size(0), _capacity(new_cap) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem;
		_max = std::numeric_limits<value_type>::max();
	}
// copy constructor
	vector_brain(const vector_brain& other):
		_alloc(other.get_allocator()),
		_size(other._size), _capacity(other._capacity) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem + _capacity;
		_max = std::numeric_limits<value_type>::max();
		std::copy(other.begin(), other.end(), _mem);
	}
// default destructor
	~vector_brain() {
		deallocate();
	}
// = 
	vector_brain& operator = (const vector_brain& other) {
		deallocate();
		allocate(other._capacity);
		_size = other._size;
		_capacity = other._capacity;
		std::copy(other.begin(), other.end(), begin());
		_memend = _mem + _capacity;
	}
// memory 
// allocate
	pointer	allocate(size_type amount) {
		if (amount == 0) return 0;
		if (amount > max_size())
			throw std::length_error("Too much to realloc");
		return _alloc.allocate(amount);
	}
// deallocate
	void	deallocate() {
		_alloc.deallocate(_mem, _capacity);
	}
// destroy
	void	destroy(pointer p) {
		_alloc.destroy(p);
	}
// update mem
	void	update_mem(pointer new_mem, size_type new_cap) {
		if (capacity() != 0)
			_alloc.deallocate(_mem, _capacity);
		_capacity = new_cap;
		_mem = new_mem;
		_memend = _mem + _capacity;
	}
// double size
	void	double_cap() {
		pointer new_mem = _alloc.allocate(_capacity * 2);
		std::copy(memfirst(), memlast(), new_mem);
		update_mem(new_mem, _capacity * 2);
	}
// iterators 
	iterator begin() const { return iterator(memfirst()); }
	iterator end() const { return iterator(memlast()); }
// accessors 
	pointer		memfirst() const { return _mem; }
	pointer		memlast() const { return _mem + _size; }
	size_type	size() const { return _size; }
	bool		empty() const { return _size == 0; }
	size_type	capacity() const { return _capacity; }
	size_type	max_size() const { return _max; }
	allocator_type	get_allocator() const { return _alloc; }
// modifiers 
	void	set_mem(const_reference value) { *_mem = value; }
	void	set_memlast(const_reference value) { *(_mem + _size) = value; }
	void	set_memend(const_reference value) { *_memend = value; }
	void	set_cap(size_type new_cap) { _capacity = new_cap; }
	void	inc_size() { ++_size; }
	void	dec_size() { --_size; }

}; // ! class vector_brain

} // ! namespace ft
