#pragma  once
#include <algorithm>
#include <limits>
#include "vector_iterator.hpp"

namespace ft {

template < typename T, class Alloc = std::allocator<T> >
class vector {

public:
// member types definitions 
	typedef T			value_type;
	typedef Alloc			allocator_type;
	typedef typename Alloc::pointer	pointer;
	typedef const pointer		const_pointer;
	typedef value_type&		reference;
	typedef const value_type&	const_reference;
	typedef std::size_t		size_type;
	typedef std::ptrdiff_t		difference_type;
	typedef vector_iterator < ft::vector<T> >		iterator;
	typedef vector_reverse_iterator < ft::vector<T> >	rev_iterator;
	typedef vector_const_iterator < vector<T> >		const_iterator;
	typedef vector_const_reverse_iterator < ft::vector<T> > const_rev_iterator;
	typedef std::random_access_iterator_tag			iterator_category;
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
	vector(): _alloc(allocator_type()),
		  _size(0), _capacity(2) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem;
		_max = std::numeric_limits<value_type>::max();
	  }
	vector(const vector& other):
		_alloc(other.get_allocator()),
		_size(other._size), _capacity(other._capacity) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem + _capacity;
		_max = std::numeric_limits<value_type>::max();
		std::copy(other.begin(), other.end(), _mem);
	}
	explicit vector(const Alloc& alloc):
		_alloc(alloc),
		_size(0), _capacity(2) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem + _capacity;
		_max = std::numeric_limits<value_type>::max();
	}
	explicit vector(size_type count,
			const_reference value = value_type(),
			const Alloc& alloc = Alloc()):
			_size(count), _capacity(count),
			_alloc(alloc) {
		_mem = _alloc.allocate(_capacity);
		_memend = _mem + _capacity;
		_max = std::numeric_limits<value_type>::max();
	}
	template <class InputIt>
	vector(InputIt first, InputIt last,
		const Alloc& alloc = Alloc()) {
		difference_type dist = std::distance(first, last);
		_mem = _alloc.allocate(dist);
		if (first < last)
			std::copy(first, last, begin());
		else std::reverse_copy(first, last, begin());
	}
	~vector() {
		_alloc.deallocate(_mem, _capacity);
	}
// = 
	vector&	operator = (const vector& other) {
		pointer new_mem = other._alloc.allocate(other._capacity);
		std::copy(other.begin(), other.end(), new_mem);
		update_mem(new_mem, _capacity);
	}
// assign 
	void	assign(size_type count,	const_reference value) {
		if (count > max_size())
			throw std::length_error("Attempt to assign() too many values to vector");
		resize(count);
		std::fill(begin(), end(), value);
	}
	template <class InputIt>
	void	assign(InputIt first, InputIt last) {
		difference_type dist = std::distance(first, last);
		if (dist > max_size())
			throw std::length_error("Attempt to assign() too many values to vector");
		pointer new_mem = _alloc.allocate(dist);
		if (first < last)
			std::copy(first, last, new_mem);
		else if (first > last)
			std::reverse_copy(last, first, new_mem);
		update_mem(new_mem, dist, dist);
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
// reserve 
	void	reserve(size_type new_cap) {
		if (new_cap <= capacity()) return;
		if (new_cap > max_size())
			throw std::length_error("Attempt to reserve too much storage for vector");
		pointer new_mem = _alloc.allocate(new_cap);
		std::copy(begin(), end(), new_mem);
		update_mem(new_mem, new_cap, size());
	}
// resize 
	void	resize(size_type count, value_type value = value_type()) {
		if (count <= size()) {
			std::for_each(begin() + count, end(), this->destroy);
			set_size(count);
			return;
		}
		pointer new_mem = _alloc.allocate(count);
		std::copy(begin(), end(), new_mem);
		std::fill(new_mem + size(), new_mem + count, value);
		update_mem(new_mem, count, count);
	}
// at 
	reference at(size_type pos) {
		if (pos < 0 || pos >= size())
			throw std::out_of_range("Invalid pos in at()");
		return _mem[pos];
	}
	const_reference at(size_type pos) const {
		if (pos < 0 || pos >= size())
			throw std::out_of_range("Invalid pos in at()");
		return _mem[pos];
	}
// [] 
	reference operator [] (size_type pos) {
		return _mem[pos];
	}
	const_reference operator [] (size_type pos) const {
		return _mem[pos];
	}
// iterators 
// begin
	iterator begin() const { return iterator(memfirst()); }
// end
	iterator end() const { return iterator(memlast()); }
// rbegin
	rev_iterator rbegin() const { return rev_iterator(memlast()); }
// rend
	rev_iterator rend() const { return rev_iterator(memfirst() - 1); }
// clear 
	void clear() {
		for (iterator it = begin(); it < end(); ++it)
			~(*it)();
		set_size(0);
	}
// insert 
	iterator insert(iterator pos, const_reference value) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid pos in insert().1");
		if (size() + 1 == capacity())
			double_cap();
		std::copy_backward(pos, end(), end() + 1);
		*pos = value;
		return pos;
	}
	iterator insert(iterator pos, size_type count, const_reference value) {
		/*
		if (count == 0) return pos;
		if (pos - count < begin() || pos >= end())
			throw std::out_of_range("Invalid pos in insert().2");
		difference_type dist = std::distance(begin(), pos - count);
		pointer new_mem = brain.allocate(capacity() + count);
		std::copy(begin(), pos - count, new_mem);
		std::fill(new_mem + dist, new_mem + dist + count, value);
		std::copy(pos, end(), new_mem);
		brain.update_mem(new_mem, capacity() + count, size() + count);
		*/
	}
	template <class InputIt>
	void	insert(iterator pos, InputIt first, InputIt last) {
		difference_type dist = std::distance(first, last);
		if (dist == 0) return;
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid iterator(s) in insert().3");
		pointer new_mem = _alloc.allocate(size() + dist);
		difference_type block = std::distance(begin(), pos);
		std::copy(begin(), pos, new_mem);
		std::copy(first, last, new_mem + block);
		std::copy(begin() + block, end(), new_mem + block + dist);
		update_mem(new_mem, size() + dist);
	}
// erase 
	iterator erase(iterator pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Invalid iterator in erase.1");
		if (size() == 0)
			throw std::length_error("Erasing element of empty vector");
		_destroy(*pos);
		std::copy(pos + 1, end(), pos);
		dec_size();
		return pos + 1;
	}
	iterator erase(iterator first, iterator last) {
		if (first < begin() || last > end())
			throw std::out_of_range("Invalid iterators in erase.2");
		if (first == last)
			return last;
		difference_type dist = std::distance(first, last);
		pointer new_mem = _alloc.allocate(capacity() - dist);
		std::copy(begin(), first, new_mem);
		std::copy(last, end(), new_mem);
		std::for_each(first, last, this->destroy);
		update_mem(new_mem, capacity() - dist, size() - dist);
	}
// push_back 
	void push_back(const_reference value) {
		if (size() + 1 >= capacity())
			double_cap();
		set_memlast(value);
		inc_size();
	}
// pop_back 
	void pop_back() {
		if (empty()) return; // or exception?
		destroy(memlast());
		dec_size();
	}
// accessors 
	reference	front() const { return *_mem; }
	reference	back() const { return *(_mem + _size - empty()); }
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
	void	set_size(size_type new_size) { _size = new_size; }
	void	set_cap(size_type new_cap) { _capacity = new_cap; }
	void	inc_size() { ++_size; }
	void	dec_size() { --_size; }

}; // ! class vector

} // ! namespace ft
