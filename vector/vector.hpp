#pragma  once
#include <algorithm>
#include <limits>
#include "vector_iterator.hpp"

#include <iostream> // XXX XXX XXX

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
	typedef vector_iterator < vector<T> >			iterator;
	//typedef vector_reverse_iterator < ft::vector<T> >	rev_iterator;
	typedef vector_const_iterator < vector<T> >		const_iterator;
	//typedef vector_const_reverse_iterator < ft::vector<T> > const_rev_iterator;
	typedef std::random_access_iterator_tag			iterator_category;
protected:
// member fields 
	allocator_type	_alloc;
	pointer		_mem;
	size_type	_size;
	size_type	_capacity;
// memory methods 
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
	void	destroy(const iterator& p) {
		_alloc.destroy(&(*p));
	}
	void	destroy(const iterator& first, const iterator& last) {
		for (iterator it(first); it < last; ++it)
			destroy(it);
	}
// update mem
	void	update_mem(pointer new_mem, size_type new_cap, size_type new_size) {
		if (_capacity > 0)
			_alloc.deallocate(_mem, _capacity);
		_mem = new_mem;
		_capacity = new_cap;
		_size = new_size;
	}
// double the capacity 
	void	double_cap() {
		reserve(_capacity * 2);
		//resize(_capacity * 2);
		/*
		pointer new_mem = _alloc.allocate(_capacity * 2);
		std::copy(_mem, _mem + _size, new_mem);
		update_mem(new_mem, _capacity * 2, _size);
		*/
	}
public:
// constructors 
	vector(): // {
		_alloc(allocator_type()), _size(0), _capacity(1) {
		_mem = _alloc.allocate(_capacity);
	}
	vector(const vector& other): // {
		_alloc(other.get_allocator()),
		_size(other._size), _capacity(other._capacity) {
		_mem = _alloc.allocate(_capacity);
		std::copy(other.begin(), other.end(), _mem);
	}
	explicit vector(const Alloc& alloc): // {
		_alloc(alloc),
		_size(0), _capacity(1) {
		_mem = _alloc.allocate(_capacity);
	}
	explicit vector(size_type count,
			const_reference value = value_type(),
			const Alloc& alloc = Alloc()): // {
		_alloc(alloc), _size(count), _capacity(count) {
		_mem = _alloc.allocate(_capacity);
		std::fill(_mem, _mem + _size, value);
	}
	template <class InputIt>
	vector(InputIt first, InputIt last,
			const Alloc& alloc = Alloc()): _alloc(alloc) {
		_mem = _alloc.allocate(ft::distance(first, last));
		if (first < last) std::copy(first, last, _mem);
		else std::reverse_copy(first, last, _mem);
		_size = _capacity = ft::distance(first, last);
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
		difference_type dist = ft::distance(first, last);
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
// reserve 
	void	reserve(size_type new_cap) {
		if (new_cap >= max_size())
			throw std::length_error("Cannot reserve given amount of memory");
		if (new_cap <= capacity()) return;
		pointer new_mem = _alloc.allocate(new_cap);
		std::copy(_mem, _mem + _size, new_mem);
		//std::copy(begin(), end(), new_mem);
		//std::fill(new_mem + _size, new_mem + new_cap, value_type()); // XXX ???
		update_mem(new_mem, new_cap, size());
	}
// resize 
	void	resize(size_type count, value_type value = value_type()) {
		if (_capacity + count >= max_size())
			throw std::length_error("Cannot resize to given amount");
		if (count < _size) {
			destroy(_mem + count, _mem + _size);
			_size = count;
			return;
		}
		pointer new_mem = _alloc.allocate(count);
		std::copy(_mem, _mem + _size, new_mem);
		std::fill(new_mem + _size, new_mem + count, value);
		update_mem(new_mem, count, count);
	}
// clear 
	void clear() {
		for (iterator it = begin(); it < end(); ++it)
			destroy(it);
		_size = 0;
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
	iterator begin() { return iterator(_mem); }
	const_iterator begin() const { return const_iterator(_mem); }
// end
	iterator end() { return iterator(_mem + _size); }
	const_iterator end() const { return const_iterator(_mem + _size); }
// rbegin
	//rev_iterator rbegin() const { return rev_iterator(_mem + _size - 1); }
// rend
	//rev_iterator rend() const { return rev_iterator(_mem - 1); }
// insert 
	iterator insert(iterator pos, const_reference value) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid pos in insert().1");
		difference_type offset = ft::distance(pos, begin());
		if (_size == _capacity)
			double_cap();
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + 1);
		*(_mem + offset) = value;
		_size += 1;
		return pos;
	}
	void	insert(iterator pos, size_type count, const_reference value) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid iterator(s) in insert().2");
		if (count == 0) return pos;
		difference_type offset = ft::distance(pos, begin());
		if (_size + count >= _capacity)
			double_cap();
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + count);
		std::fill(pos, pos + count, value);
		_size += count;
	}
	template <class InputIt>
	void	insert(iterator pos, InputIt first, InputIt last) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid iterator(s) in insert().3");
		if (first == last) return;
		size_type count = ft::distance(first, last);
		difference_type offset = ft::distance(pos, begin());
		if (_size + count >= _capacity)
			double_cap();
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + count);
		if (first < last)
			std::copy(first, last, pos);
		else std::reverse_copy(first, last, pos);
		_size += count;
	}
// erase 
	iterator erase(iterator pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Invalid iterator in erase.1");
		if (size() == 0)
			throw std::length_error("Erasing element of empty vector");
		destroy(pos);
		std::copy(pos + 1, end(), pos);
		_size -= 1;
		return pos + 1;
	}
	iterator erase(iterator first, iterator last) {
		if (first < begin() || last > end())
			throw std::out_of_range("Invalid iterators in erase.2");
		if (first == last) return last;
		iterator pos = last == end() ? end() : last + 1;
		destroy(first, last);
		std::copy(last, end(), first);
		_size -= ft::distance(first, last);
		return pos;
	}
// push_back 
	void push_back(const_reference value) {
		if (_size == _capacity)
			double_cap();
		*(_mem + _size) = value;
		_size += 1;
	}
// pop_back 
	void pop_back() {
		if (empty()) return; // std::vector does not perform this check. should the ft:: one be better?
		destroy(_mem + _size);
		_size -= 1;
	}
// accessors 
	reference	front() const { return *_mem; }
	reference	back() const { return *(_mem + _size - empty()); }
	size_type	size() const { return _size; }
	bool		empty() const { return _size == 0; }
	size_type	capacity() const { return _capacity; }
	size_type	max_size() const { return std::numeric_limits<size_type>::max(); }
	allocator_type	get_allocator() const { return _alloc; }

}; // ! class vector

} // ! namespace ft
