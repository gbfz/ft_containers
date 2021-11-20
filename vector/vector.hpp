#pragma		once
#include	<algorithm>
#include	<limits>
#include	"vector_iterator.hpp"
#include	"vector_brain.hpp"

namespace ft {

template < typename T, class Allocator = std::allocator<T> >
class vector: public vector_brain<T> {

public: // member types definitions
	typedef T				value_type;
	typedef Allocator			allocator_type;
	typedef typename Allocator::pointer	pointer;
	typedef const pointer			const_pointer;
	typedef value_type&			reference;
	typedef const value_type&		const_reference;
	typedef std::size_t			size_type;
	typedef std::ptrdiff_t			difference_type;
	typedef vector_iterator < ft::vector<T> >		iterator;
	typedef vector_reverse_iterator < ft::vector<T> >	reverse_iterator;
	typedef vector_const_iterator < vector<T> >		const_iterator;
	typedef vector_const_reverse_iterator < ft::vector<T> > const_reverse_iterator;
protected: // brain
	vector_brain<value_type> brain;
public:
// constructors
	vector(): brain(vector_brain<value_type>()) {}
	vector(const vector& other): brain(other.brain()) {}
	explicit vector(const Allocator& alloc):
			brain(vector_brain<value_type, Allocator>()) {}
	explicit vector(size_type count,
			const_reference value = value_type(),
			const Allocator& alloc = Allocator()):
		brain(vector_brain<value_type>(count, count + 1)) {
		std::fill(brain.begin(), brain.end(), value);
	}
	template <class InputIt>
	vector(InputIt first, InputIt last,
		const Allocator& alloc = Allocator()) {
		difference_type dist = std::distance(first, last);
		brain = vector_brain<T, Allocator>(dist, dist + 1);
		if (first < last)
			std::copy(first, last, begin());
		else std::reverse_copy(first, last, begin());
	}
	~vector() {}
// =
	vector&	operator = (const vector& other) {
		brain = other.brain;
	}
// assign
	void	assign(size_type count,	const_reference value) {
		if (count > max_size())
			throw std::length_error("Attempt to assign() too many values to vector");
		brain.reallocate(count);
		std::fill(begin(), end(), value);
	}
	template <class InputIt>
	void	assign(InputIt first, InputIt last) {
		difference_type dist = std::distance(first, last);
		if (dist > max_size())
			throw std::length_error("Attempt to assign() too many values to vector");
		pointer new_mem = brain.allocate(dist);
		if (first < last)
			std::copy(first, last, new_mem);
		else if (first > last)
			std::reverse_copy(last, first, new_mem);
		brain.update_mem(new_mem, dist, dist);
	}
// reserve
	void	reserve(size_type new_cap) {
		if (new_cap <= capacity()) return;
		if (new_cap > max_size())
			throw std::length_error("Attempt to reserve too much storage for vector");
		pointer new_mem = brain.allocate(new_cap);
		std::copy(begin(), end(), new_mem);
		brain.update_mem(new_mem, new_cap, size());
	}
// resize
	void	resize(size_type count, value_type value = value_type()) {
		if (count <= size()) {
			brain._size = count;
			return;
		}
		pointer new_mem = brain.allocate(count);
		std::copy(begin(), end(), new_mem);
		std::fill(new_mem + size(), new_mem + count, value);
		_update_mem(new_mem, count, count);
	}
// get_allocator
	allocator_type	get_allocator() const {
		return brain._alloc;
	}
// at
	reference at(size_type pos) {
		if (pos < 0 || pos >= size())
			throw std::out_of_range("Invalid pos in at()");
		return brain._mem[pos];
	}
	const_reference at(size_type pos) const {
		if (pos < 0 || pos >= size())
			throw std::out_of_range("Invalid pos in at()");
		return brain._mem[pos];
	}
// []
	reference operator [] (size_type pos) {
		return brain._mem[pos];
	}
	const_reference operator [] (size_type pos) const {
		return brain._mem[pos];
	}
// front
	reference front() {
		return brain._mem[0];
	}
	const_reference front() const {
		return brain._mem[0];
	}
// back
	reference back() {
		return *brain._memlast;
	}
	const_reference back() const {
		return *brain._memlast;
	}
// data
	pointer	data() {
		return brain._mem;
	}
	const_pointer data() const {
		return brain._mem;
	}
// begin
	iterator begin() {
		return brain.begin();
	}
	const_iterator begin() const {
		return brain.begin();
	}
// end
	iterator end() {
		return brain.end();
	}
	const_iterator end() const {
		return brain.end();
	}
// rbegin
	reverse_iterator rbegin() {
		return brain.rbegin();
	}
	const_reverse_iterator rbegin() const {
		return brain.rbegin();
	}
// rend
	reverse_iterator rend() {
		return brain.rend();
	}
	const_reverse_iterator rend() const {
		return brain.rend();
	}
// empty
	bool empty() const {
		return brain.empty();
	}
// size
	size_type size() const {
		return brain.size();
	}
// max_size
	size_type max_size() const {
		return brain.max_size();
	}
// capacity
	size_type capacity() const {
		return brain.capacity();
	}
// clear
	void clear() {
		for (iterator it = begin(); it < end(); ++it)
			~(*it)();
		brain._size = 0;
	}
// insert
	iterator insert(iterator pos, const_reference value) {
		if (pos < begin() || pos >= /*>=?*/ end())
			throw std::out_of_range("Invalid pos in insert().1");
		if (size() + 1 >= capacity())
			brain.double_size();
		std::copy(pos, end(), pos + 1);
		*pos = value;
		++brain._size;
		return pos;
	}
	iterator insert(iterator pos, size_type count, const_reference value) {
		if (count == 0) return pos;
		if (pos - count < begin() || pos >= /*>=?*/ end())
			throw std::out_of_range("Invalid pos in insert().2");
		difference_type dist = std::distance(begin(), pos - count);
		pointer new_mem = brain.allocate(capacity() + count);
		std::copy(begin(), pos - count, new_mem);
		std::fill(new_mem + dist, new_mem + dist + count, value);
		std::copy(pos, end(), new_mem);
		brain.update_mem(new_mem, capacity() + count, size() + count);
	}
	template <class InputIt>
	void	insert(iterator pos, InputIt first, InputIt last) {
		difference_type dist = std::distance(first, last);
		if (dist == 0) return;
		if (pos - dist < begin() || pos >= /*>=?*/ end())
			throw std::out_of_range("Invalid iterator(s) in insert().3");
		pointer new_mem = brain.allocate(capacity() + dist);
		iterator endcopied = std::copy(begin(), pos - dist, new_mem);
		std::copy(first, last, endcopied);
		std::copy(endcopied + dist, end(), new_mem);
		brain.update_mem(new_mem, capacity() + dist, size() + dist);
	}
// erase
	iterator erase(iterator pos) {
		if (pos < begin() || pos >= end())
			throw std::out_of_range("Invalid iterator in erase.1");
		if (size() == 0)
			throw std::out_of_range("Erasing element of empty vector");
		~(*pos)(); // really??
		std::copy(pos + 1, end(), pos);
		--brain._size;
		return pos + 1;
	}
	iterator erase(iterator first, iterator last) {
		if (first < begin() || last > end())
			throw std::out_of_range("Invalid iterators in erase.2");
		if (first == last)
			return last;
		difference_type dist = std::distance(first, last);
		pointer new_mem = brain.allocate(capacity() - dist);
		std::copy(begin(), first, new_mem);
		std::copy(last, end(), new_mem);
		brain.update_mem(new_mem, capacity() - dist, size() - dist);
	}
// push_back
	void push_back(const_reference value) {
		if (size() + 1 >= capacity())
			brain.double_size();
		*brain._memend = value;
		++brain._memlast && ++brain._memend;
	}
// pop_back
	void pop_back() {
		if (empty()) return; // or exception?
		~(*brain._memlast)();
		--brain._memlast && --brain._memend;
	}
}; // ! class vector

} // ! namespace ft
