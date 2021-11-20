#pragma		once
#include	<algorithm>
#include	<limits>
#include	"vector_iterator.hpp"

namespace ft {

template < typename T, class Allocator = std::allocator<T> >
class vector_brain {
public:
	typedef Allocator		allocator_type;
	typedef typename Allocator::pointer	pointer;
	typedef std::size_t			size_type;
	typedef std::ptrdiff_t			difference_type;
protected:
	allocator_type	_alloc;
	pointer		_mem;
	pointer		_memlast;
	pointer		_memend;
	size_type	_size;
	size_type	_capacity;
	difference_type	_max;
	typedef vector_iterator<vector_brain>		iterator;
	typedef vector_const_iterator<vector_brain>	const_iterator;
	typedef vector_reverse_iterator<vector_brain>	reverse_iterator;
	typedef vector_const_reverse_iterator<vector_brain>
		const_reverse_iterator;
public:
// default constructor
	vector_brain(): _size(0), _capacity(2),
			_alloc(allocator_type()) {
		_mem = _alloc.allocate(_capacity);
		_memlast = _mem;
		_memend = _mem;
		_max = std::numeric_limits<size_type>::max();
	}
// parametrized constructor
	vector_brain(size_type new_size, size_type new_cap):
       			_size(new_size), _capacity(new_cap),
			_alloc(allocator_type()) {
		_mem = _alloc.allocate(_capacity);
		_memlast = _mem;
		_memend = _mem;
		_max = std::numeric_limits<size_type>::max();
	}
// copy constructor
	vector_brain(const vector_brain& other):
		_size(other._size), _capacity(other._capacity),
		_alloc(other.allocator_type()) {
			_mem = _alloc.allocate(_capacity);
			_memlast = _mem + _size - 1;
			_memend = _mem + _capacity;
			std::copy(other.begin(), other.end(), _mem);
			_max = std::numeric_limits<size_type>::max();
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
// default destructor
	~vector_brain() {
		deallocate();
	}
// memory
	pointer	allocate(size_type amount) {
		if (amount == 0) return 0;
		if (amount > max_size())
			throw std::length_error("Too much to realloc");
		return _alloc.allocate(amount);
	}
	void	deallocate() {
		_alloc.deallocate(begin(), _capacity);
	}
	pointer reallocate(size_type amount) {
		if (amount > max_size())
			throw std::length_error("Too much to realloc");
		if (amount <= capacity())
			return _mem;
		pointer new_mem = allocate(amount);
		std::copy(begin(), end(), new_mem);
		update_mem(new_mem, amount + 1, amount);
		return _mem;
	}
	void	update_mem(pointer new_mem, size_type new_cap, size_type new_size) {
		if (capacity() != 0)
			_alloc.deallocate(_mem, _capacity);
		_capacity = new_cap;
		_size = new_size;
		_mem = new_mem;
		_memlast = _mem + _size - 1;
		_memend = _memlast + 1;
	}
	void	double_size() {
		pointer new_mem = _alloc.allocate(_capacity * 2);
		std::copy(begin(), end(), new_mem);
		update_mem(new_mem, _capacity * 2, _size);
	}
// iterators
	iterator begin() { return _mem; }
	const_iterator begin() const { return _mem; }
	iterator end()   { return _memend; }
	const_iterator end() const { return _memend; }
	iterator last()  { return _memlast; }
	const_iterator last() const { return _memlast; }
	reverse_iterator rbegin() { return _memlast; }
	const_reverse_iterator rbegin() const { return _memlast; }
	reverse_iterator rend() { return _mem - 1; }
	const_reverse_iterator rend() const { return _mem - 1; }
// accessors
	size_type size() const { return _size; }
	bool empty() const { return _size == 0; }
	size_type capacity() const { return _capacity; }
	size_type max_size() const { return _max; }
}; // ! class vector_brain

} // ! namespace ft
