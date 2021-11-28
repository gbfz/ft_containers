#pragma  once
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "normal_iterator.hpp"

namespace ft {

template <typename T, class Alloc = std::allocator<T> >
class vector {

public:
// member types definitions 
	typedef T			value_type;
	typedef Alloc			allocator_type;
	typedef typename Alloc::pointer		pointer;
	typedef typename Alloc::const_pointer	const_pointer;
	typedef value_type&		reference;
	typedef const value_type&	const_reference;
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
	typedef std::random_access_iterator_tag		iterator_category;
	typedef _normal_iterator<pointer, vector>	iterator;
	typedef _normal_iterator<const_pointer, vector> const_iterator;
	//	typedef vector_iterator <pointer>		iterator;
	//typedef vector_reverse_iterator < ft::vector<T> >	rev_iterator;
	//	typedef vector_const_iterator <pointer>		const_iterator;
	//typedef vector_const_reverse_iterator < ft::vector<T> > const_rev_iterator;
protected:
// member fields 
	allocator_type	_alloc;
	pointer		_mem;
	size_type	_size;
	size_type	_capacity;
// memory methods 
// update mem
	void	update_mem(pointer new_mem, size_type new_cap, size_type new_size) {
		if (_capacity > 0)
			_alloc.deallocate(_mem, _capacity);
		_mem = new_mem;
		_capacity = new_cap;
		_size = new_size;
	}
// construct 
	void	construct(const iterator& it, const_reference value) {
		_alloc.construct(&(*it), value);
	}
	void	construct(const iterator& first, const iterator& last,
			  const_reference value) {
		for (iterator it(first); it < last; ++it)
			construct(it, value);
	}
// destroy
	void	destroy(const iterator& it) {
		_alloc.destroy(&(*it));
	}
	void	destroy(const iterator& first, const iterator& last) {
		for (iterator it(first); it < last; ++it)
			destroy(it);
	}
public:
// constructors, destructor 
	vector(): // {
		_alloc(allocator_type()), _mem(0), _size(0), _capacity(0) {
	}
	vector(const vector& other): // {
		_alloc(other.get_allocator()),
		_size(other._size), _capacity(other._capacity) {
		_mem = _alloc.allocate(_capacity);
		construct(begin(), end(), value_type());
		std::copy(other.begin(), other.end(), _mem);
	}
	explicit vector(const Alloc& alloc): // {
		_alloc(alloc), _mem(0), _size(0), _capacity(0) {
	}
	explicit vector(size_type count,
			const_reference value = value_type(),
			const Alloc& alloc = Alloc()): // {
		_alloc(alloc), _size(count), _capacity(count) {
		_mem = _alloc.allocate(_capacity);
		construct(iterator(_mem), iterator(_mem + _size),
			value);
	}
	template <class InputIt>
	vector(InputIt first, InputIt last,
			const Alloc& alloc = Alloc()): _alloc(alloc) {
		// TODO: what if distance is 0?
		difference_type distance = std::abs(std::distance(first, last));
		_mem = _alloc.allocate(distance);
		_size = _capacity = distance;
		construct(iterator(_mem), iterator(_mem + _size),
				value_type());
		if (first < last) std::copy(first, last, _mem);
		else std::reverse_copy(first, last, _mem);
	}
	~vector() {
		if (_capacity) _alloc.deallocate(_mem, _capacity);
	}
// = 
	vector&	operator = (const vector& other) {
		if (this == &other) return *this;
		pointer new_mem = other._alloc.allocate(other.capacity());
		std::copy(other.begin(), other.end(), new_mem);
		update_mem(new_mem, other.capacity(), other.size());
		return *this;
	}
	vector&	operator = (vector& other) {
		if (this == &other) return *this;
		pointer new_mem = other._alloc.allocate(other._capacity);
		std::copy(other.begin(), other.end(), new_mem);
		update_mem(new_mem, other.capacity(), other.size());
		return *this;
	}
// assign 
private:
// one value 
	void	_assign(size_type count, const_reference value, true_type) {
		if (count > max_size())
			throw std::length_error("Attempt to assign() too many values to vector");
		resize(count);
		construct(begin(), end(), value);
	}
// range 
	template <class InputIt>
	void	_assign(InputIt first, InputIt last, false_type) {
		size_type dist = std::abs(std::distance(first, last));
		if (dist > max_size())
			throw std::length_error("Attempt to assign() too many values to vector");
		pointer new_mem = _alloc.allocate(dist);
		if (first < last)
			std::copy(first, last, new_mem);
		else std::reverse_copy(last, first, new_mem);
		update_mem(new_mem, std::max(_capacity, dist), dist);
	}
public:
// dispatch disambiguation 
	template <typename First, typename Second>
	void	assign(First first, Second second) {
		typedef typename is_integral<First>::type assign_type;
		_assign(first, second, assign_type());
	}
// reserve 
	void	reserve(size_type new_cap) {
		if (new_cap >= max_size())
			throw std::length_error("Cannot reserve given amount of memory");
		if (new_cap <= _capacity) return;
		pointer new_mem = _alloc.allocate(new_cap);
		construct(iterator(new_mem), iterator(new_mem + new_cap),
				value_type()); // XXX: is this correct?
		std::copy(begin(), end(), new_mem);
		update_mem(new_mem, new_cap, _size);
	}
// resize 
	void	resize(size_type count, value_type value = value_type()) {
		if (_capacity + count >= max_size())
			throw std::length_error("Cannot resize to given amount");
		if (count == _size) return;
		if (count < _size) {
			destroy(begin() + count, end());
			_size = count;
			return;
		}
		pointer new_mem = _alloc.allocate(count);
		construct(iterator(new_mem), iterator(new_mem + count),
				value);
		if (_size) std::copy(begin(), end(), new_mem);
		update_mem(new_mem, count, count);
	}
// clear 
	void clear() {
		destroy(begin(), end());
		_size = 0;
	}
// [], at 
	reference operator [] (size_type pos) {
		return _mem[pos];
	}
	const_reference operator [] (size_type pos) const {
		return _mem[pos];
	}
	reference at(size_type pos) {
		if (pos >= size())
			throw std::out_of_range("Invalid pos in at()");
		return _mem[pos];
	}
	const_reference at(size_type pos) const {
		if (pos >= size())
			throw std::out_of_range("Invalid pos in at()");
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
// one value 
	iterator insert(iterator pos, const_reference value) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid pos in insert().1");
		difference_type offset = std::distance(begin(), pos);
		if (_size == _capacity)
			reserve(_size + 1);
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + 1);
		construct(pos, value);
		_size += 1;
		return pos;
	}
private:
// count values 
	void	_insert(iterator pos, size_type count, const_reference value,
			true_type) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid iterator in insert().2");
		if (count == 0) return;
		difference_type offset = std::distance(begin(), pos);
		if (_size + count > _capacity)
			reserve(_size + count);
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + count);
		construct(pos, pos + count, value);
		_size += count;
	}
// range 
	template <class InputIt>
	void	_insert(iterator pos, InputIt first, InputIt last,
			false_type) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid iterator in insert().3");
		if (first == last) return;
		size_type count = std::distance(first, last);
		difference_type offset = std::distance(begin(), pos);
		if (_size + count > _capacity)
			reserve(_size + count);
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + count);
		if (first < last)
			std::copy(first, last, pos);
		else std::reverse_copy(first, last, pos);
		_size += count;
	}
public:
// dispatch disambiguation 
	template <typename First, typename Second>
	void	insert(iterator pos, First first, Second second) {
		typedef typename is_integral<First>::type insert_type;
		_insert(pos, first, second, insert_type());
	}
// erase 
	iterator erase(iterator pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Invalid iterator in erase.1");
		destroy(pos);
		std::copy(pos + 1, end(), pos);
		_size -= 1;
		return pos + 1;
	}
	iterator erase(iterator first, iterator last) {
		if (first < begin() || last > end())
			throw std::out_of_range("Invalid iterators in erase.2");
		if (first == last) return last;
		destroy(first, last);
		std::copy(last, end(), first);
		_size -= std::distance(first, last);
		return last + (last < end());
	}
// push_back 
	void push_back(const_reference value) {
		if (_size == _capacity)
			reserve((_capacity | !_capacity) << !!_capacity);
		*(_mem + _size) = value;
		_size += 1;
	}
// pop_back 
	void pop_back() {
		if (!empty())
			destroy(end() - 1); // what...
		_size -= 1;
	}
// swap 
	void	swap(vector& other) {
		if (this == &other) return;
		vector t = *this;
		*this = other;
		other = t;
	}
// accessors 
	reference	front() const { return *_mem; }
	reference	back() const { return *(_mem + _size - !empty()); }
	size_type	size() const { return _size; }
	bool		empty() const { return begin() == end(); }
	size_type	capacity() const { return _capacity; }
	size_type	max_size() const {
		static size_type max =
			(static_cast<unsigned long long>(~0) >> 1) /
			sizeof(value_type);
		return max;
	}
	allocator_type	get_allocator() const { return _alloc; }
}; // ! class vector

// swap 
template <typename T, class Alloc>
void	swap(vector<T, Alloc>&a, vector<T, Alloc>& b) {
	a.swap(b);
}

// vector comparison 
template <typename T, class Alloc>
bool operator == (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	if (a.size() != b.size()) return false;
	return std::equal(a.begin(), a.end(), b.begin());
}
template <typename T, class Alloc>
bool operator != (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return !(a == b);
}
template <typename T, class Alloc>
bool operator < (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return std::lexicographical_compare(a.begin(), a.end(),
					    b.begin(), b.end());
}
template <typename T, class Alloc>
bool operator > (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return b < a;
}
template <typename T, class Alloc>
bool operator <= (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return !(b < a);
}
template <typename T, class Alloc>
bool operator >= (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return !(a < b);
}

} // ! namespace ft
