#pragma  once
#include <memory>
#include <algorithm>
#include "iterator.hpp"
#include "utility.hpp"
// #include "../iterator/iterator.hpp" // TODO: delete 
// #include "../utilities/utility.hpp"
// #include "comparison.hpp"
// #include "../utilities/comparison.hpp" // TODO: delete 
#include <stdexcept>

namespace ft {

template <typename T, class Alloc = std::allocator<T> >
class vector {

public:
// member types definitions 
	typedef T					value_type;
	typedef Alloc					allocator_type;
	typedef typename Alloc::pointer			pointer;
	typedef typename Alloc::const_pointer		const_pointer;
	typedef value_type&				reference;
	typedef const value_type&			const_reference;
	typedef size_t					size_type;
	typedef ptrdiff_t				difference_type;
	typedef ft::normal_iterator<pointer, vector>		iterator;
	typedef ft::normal_iterator<const_pointer, vector> 	const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

protected:
// member fields 
	allocator_type	_alloc;
	pointer		_mem;
	size_type	_size;
	size_type	_capacity;
	typedef true_type	fill_type;
	typedef false_type	range_type;

// memory methods 
// update mem
	void	update_mem(pointer new_mem, size_type new_cap, size_type new_size) {
		if (_mem) _alloc.destroy(_mem);
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
		_alloc(allocator_type()), _mem(NULL), _size(0), _capacity(0) {
	}
	vector(const vector& other): // {
		_alloc(other.get_allocator()),
		_size(other._size), _capacity(other._capacity) {
		if (_capacity) {
			_mem = _alloc.allocate(_capacity);
			construct(begin(), end(), value_type());
			std::copy(other.begin(), other.end(), _mem);
		} else _mem = NULL;
	}
	explicit vector(const Alloc& alloc): // {
		_alloc(alloc), _mem(NULL), _size(0), _capacity(0) {
	}
	explicit vector(size_type count, const_reference value = value_type(),
				const Alloc& alloc = Alloc()):
		_alloc(alloc), _size(count), _capacity(count) {
		if (_capacity) {
			_mem = _alloc.allocate(_capacity);
			construct(iterator(_mem), iterator(_mem + _capacity), value);
		} else _mem = 0;
	}
	template <class InputIt>
	vector(typename enable_if<!is_integral<InputIt>::value, InputIt>::type first,
			InputIt last, const Alloc& alloc = Alloc()): _alloc(alloc) {
		difference_type distance = std::abs(std::distance(first, last));
		if (distance) {
			_mem = _alloc.allocate(distance);
			_size = _capacity = distance;
			construct(iterator(_mem), iterator(_mem + _size), value_type());
			std::copy(first, last, _mem);
		} else {
			_mem = NULL;
			_capacity = _size = 0;
		}
	}
	~vector() {
		if (_mem) _alloc.destroy(_mem);
		if (_capacity) _alloc.deallocate(_mem, _capacity);
		_mem = NULL;
	}

// operator = 
	vector&	operator = (const vector& other) {
		if (this == &other) return *this;
		if (!other.empty()) {
			pointer new_mem = other.get_allocator().allocate(other.capacity());
			std::copy(other.begin(), other.end(), new_mem);
			update_mem(new_mem, other.capacity(), other.size());
		} else clear();
		return *this;
	}

// assign 
private: // only dispatcher is public
// one value 
	void	_assign(size_type count, const_reference value, fill_type) {
		if (count > max_size())
			throw std::length_error("Attempt to assign too many values");
		resize(count);
		construct(begin(), end(), value);
	}
// range 
	template <class InputIt>
	void	_assign(InputIt first, InputIt last, range_type) {
		size_type dist = std::abs(std::distance(first, last));
		if (dist > max_size())
			throw std::length_error("Attempt to assign too many values");
		pointer new_mem = _alloc.allocate(dist);
		std::copy(first, last, new_mem);
		update_mem(new_mem, std::max(_capacity, dist), dist);
	}
public: // assign dispatch disambiguation 
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
		construct(iterator(new_mem), iterator(new_mem + new_cap), value_type());
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
		construct(iterator(new_mem), iterator(new_mem + count), value);
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
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
// rend
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

// insert 
// one value 
	iterator insert(iterator pos, const_reference value) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid pos in insert().1");
		difference_type offset = std::distance(begin(), pos);
		if (_size == _capacity)
			reserve(_size * 2 + !_size);
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + 1);
		construct(pos, value);
		_size += 1;
		return pos;
	}
private:
// count values 
	void	_insert(iterator pos, size_type count, const_reference value, fill_type) {
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
	void	_insert(iterator pos, InputIt first, InputIt last, range_type) {
		if (pos < begin() || pos > end())
			throw std::out_of_range("Invalid iterator in insert().3");
		if (first == last) return;
		size_type count = std::distance(first, last);
		difference_type offset = std::distance(begin(), pos);
		if (_size + count > _capacity)
			reserve(_size + count);
		pos = begin() + offset;
		std::copy_backward(pos, end(), end() + count);
		std::copy(first, last, pos);
		// if (first < last)
			// std::copy(first, last, pos);
		// else std::reverse_copy(first, last, pos);
		_size += count;
	}
public:
// dispatch disambiguation 
	template <typename First, typename Second>
	void	insert(iterator pos, First first, Second second) {
		_insert(pos, first, second, typename is_integral<First>::type());
	}

// erase 
	iterator erase(iterator pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Invalid iterator in erase.1");
		destroy(pos);
		std::copy(pos + 1, end(), pos);
		_size -= 1;
		return pos;
	}
	iterator erase(iterator first, iterator last) {
		if (first < begin() || last > end())
			throw std::out_of_range("Invalid iterators in erase.2");
		if (first == last) return last;
		bool last_is_end = last == end();
		difference_type start = std::distance(begin(), first);
		destroy(first, last);
		std::copy(last, end(), first);
		_size -= std::distance(first, last);
		if (last_is_end) return end();
		return iterator(begin() + start);
	}

// push_back 
	void push_back(const_reference value) {
		if (_size == _capacity)
			reserve(_capacity * 2 + !_capacity);
		_mem[_size] = value;
		_size += 1;
	}

// pop_back 
	void pop_back() {
		_size -= 1;
		if (_size > 0) destroy(end() - 1);
	}

// swap 
	void	swap(vector& other) {
		std::swap(_mem, other._mem);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_alloc, other._alloc);
	}

// accessors 
	reference	front() const { return _mem[0]; }
	reference	back() const { return _mem[_size - !empty()]; }
	size_type	size() const { return _size; }
	bool		empty() const { return begin() == end(); }
	size_type	capacity() const { return _capacity; }
	size_type	max_size() const { // sorry 
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
	return ft::equal(a.begin(), a.end(), b.begin());
}

template <typename T, class Alloc>
bool operator != (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return !(a == b);
}

template <typename T, class Alloc>
bool operator < (const vector<T, Alloc>& a, const vector<T, Alloc>& b) {
	return ft::lexicographical_compare(a.begin(), a.end(),
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
