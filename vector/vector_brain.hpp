#pragma		once
#include	<algorithm>
#include	<limits>
#include	"vector_iterator.hpp"

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
	pointer		_memlast;
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
		_memlast = _mem;
		_memend = _mem;
		_max = std::numeric_limits<size_type>::max();
	}
// parametrized constructor
	vector_brain(size_type new_size, size_type new_cap):
			_alloc(allocator_type()),
       			_size(new_size), _capacity(new_cap) {
		_mem = _alloc.allocate(_capacity);
		_memlast = _mem;
		_memend = _mem;
		_max = std::numeric_limits<size_type>::max();
	}
// copy constructor
	vector_brain(const vector_brain& other):
		_alloc(other.get_allocator()),
		_size(other._size), _capacity(other._capacity) {
			_mem = _alloc.allocate(_capacity);
			_memlast = _mem + _size - 1;
			_memend = _mem + _capacity;
			std::copy(other.begin(), other.end(), _mem);
			_max = std::numeric_limits<size_type>::max();
	}
// default destructor
	~vector_brain() {
		deallocate();
	}
// = 
	vector_brain& operator = (const vector_brain& other) {
		deallocate();
		allocate(other._capacity);
		_size = other._size && _capacity = other._capacity;
		std::copy(other.begin(), other.end(), begin());
		_memlast = _mem + _size - 1;
		_memend = _memlast + 1;
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
	void	update_mem(pointer new_mem, size_type new_cap, size_type new_size) {
		if (capacity() != 0)
			_alloc.deallocate(_mem, _capacity);
		_capacity = new_cap;
		_size = new_size;
		_mem = new_mem;
		_memlast = _mem + _size - 1;
		_memend = _memlast + 1;
	}
// double size
	void	double_size() {
		pointer new_mem = _alloc.allocate(_capacity * 2);
		std::copy(begin(), end(), new_mem);
		update_mem(new_mem, _capacity * 2, _size);
	}
// iterators 
	iterator begin() { return _mem; }
	const_iterator begin() const { return _mem; }
	iterator end() { return _memend; }
	const_iterator end() const { return _memend; }
// accessors 
	pointer		memstart() { return _mem; }
	const_pointer	memstart() const { return _mem; }
	pointer		memlast() { return _memlast; }
	const_pointer	memlast() const { return _memlast; }
	pointer		memend() { return _memend; }
	const_pointer	memend() const { return _memend; }
	size_type	size() const { return _size; }
	bool		empty() const { return _size == 0; }
	size_type	capacity() const { return _capacity; }
	size_type	max_size() const { return _max; }
	allocator_type	get_allocator() const { return _alloc; }
// modifiers 
	void	set_mem(const_reference value) { *_mem = value; }
	void	set_memlast(const_reference value) { *_memlast = value; }
	void	set_memend(const_reference value) { *_memend = value; }
	void	set_size(size_type new_size) { _size = new_size; }
	void	set_cap(size_type new_cap) { _capacity = new_cap; }
	void	advance_border() { ++_memlast; ++_memend; }
	void	retreat_border() { --_memlast; --_memend; }
	void	advance_size(size_type offset) { _size += offset; }
	void	retreat_size(size_type offset) { _size -= offset; }
}; // ! class vector_brain

} // ! namespace ft
