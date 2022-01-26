#include "../map/rbtree.hpp"
#include "../utilities/pair.hpp"
#include "../utilities/comparison.hpp"
#include <limits>

namespace ft {

template<class Key, class Compare = std::less<Key>,
	 class Allocator = std::allocator<Key>
> class set {
public:
// member types definition 
	typedef Key					key_type;
	typedef Key					value_type;
	typedef std::size_t				size_type;
	typedef std::ptrdiff_t				difference_type;
	typedef Compare					key_compare;
	typedef Compare					value_compare;
	typedef Allocator				allocator_type;
	typedef value_type&				reference;
	typedef const value_type&			const_reference;
	typedef typename Allocator::pointer		pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef ft::tree_iterator<value_type>		iterator;
	typedef ft::tree_iterator<const value_type>	const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
// underlying data structure 
	RBTree<value_type, value_compare, allocator_type>	tree;
	allocator_type						alloc;

public:
// ctors, dtor 
	set(): tree() {}
	explicit set(const Compare& comp, const Allocator& alloc = Allocator());
	explicit set(const Allocator& alloc);
	template <typename InputIt>
	set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
	set(const set& other): tree(other.tree) {}
	~set() {}

// operator = 
	set& operator = (const set& other) { tree = other.tree; return *this; }

// get allocator 
	allocator_type get_allocator() const { return alloc; }

// begin, rbegin 
	iterator begin() { return tree.begin(); }
	const_iterator begin() const { return tree.begin(); }
	reverse_iterator rbegin() { return tree.rbegin(); }
	const_reverse_iterator rbegin() const { return tree.rbegin(); }

// end, rend 
	iterator end() { return tree.end(); }
	const_iterator end() const { return tree.end(); }
	reverse_iterator rend() { return tree.rend(); }
	const_reverse_iterator rend() const { return tree.rend(); }

// empty 
	bool empty() const { return tree.empty(); }

// size 
	size_type size() const { return tree.size(); }

// max_size 
	size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

// clear 
	void clear() { tree.clear(); }

// insert 
	ft::pair<iterator, bool> insert(const value_type& value) { return tree.insert(value); }
	iterator insert(iterator hint, const value_type& value) { return tree.insert(hint, value); }
	template <typename InputIt>
	void insert(InputIt first, InputIt last) { return tree.insert(first, last); }

// erase 
	void erase(iterator pos) { tree.erase(pos); }
	void erase(iterator first, iterator last) { tree.erase(first, last); }
	size_type erase(const Key& key) { tree.erase(key); }

// swap 
	void swap(set& other) {
		ft::swap(tree, other.tree);
		std::swap(alloc, other.alloc);
	}

// count 
	size_type count(const Key& key) { return tree.count(key); }

// find 
	iterator find(const Key& key) { return tree.find(key); }
	const_iterator find(const Key& key) const { return tree.find(key); }

// equal range 
	ft::pair<iterator, iterator> equal_range(const Key& key) { return tree.equal_range(key); }
	ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { return tree.equal_range(key); }

// lower bound 
	iterator lower_bound(const Key& key) { return tree.lower_bound(key); }
	const_iterator lower_bound(const Key& key) const { return tree.lower_bound(key); }

// upper bound 
	iterator upper_bound(const Key& key) { return tree.upper_bound(key); }
	const_iterator upper_bound(const Key& key) const { return tree.upper_bound(key); }

// key comp, value comp 
	key_compare key_comp() const { return key_compare(); }
	value_compare value_comp() const { return tree.value_compare(); }

}; // ! class set

// set comparison 
template <class Key, class Compare, class Alloc>
inline bool
operator == (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class Key, class Compare, class Alloc>
inline bool
operator != (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}
template <class Key, class Compare, class Alloc>
inline bool
operator < (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class Key, class Compare, class Alloc>
inline bool
operator > (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return rhs < lhs;
}
template <class Key, class Compare, class Alloc>
inline bool
operator <= (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return !(rhs < lhs);
}
template <class Key, class Compare, class Alloc>
inline bool
operator >= (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}

// swap 
template <class Key, class Compare, class Alloc>
inline void
swap(const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return lhs.swap(rhs);
}

} // ! namespace ft
