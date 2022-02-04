#pragma  once
#include "../rbtree/RBTree.hpp"

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
	typedef ft::tree_iterator<const value_type>	iterator;
	typedef ft::tree_iterator<const value_type>	const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
// underlying data structure 
	RBTree<value_type, value_compare, allocator_type>	tree;
	allocator_type						key_alloc;
	typedef ft::tree_iterator<value_compare>		__mutable_iterator;

public:
// ctors, dtor 
	set(): tree() {}
	explicit set(const Compare& comp, const Allocator& alloc = Allocator()): tree(comp, alloc), key_alloc(alloc) {}
	explicit set(const Allocator& alloc);
	template <typename InputIt>
	set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()):
		tree(comp, alloc), key_alloc(alloc) {
			for (; first != last; ++first)
				tree.insert(*first);
	}
	set(const set& other): tree(other.tree) {}
	~set() {}

// operator = 
	set& operator = (const set& other) {
		if (this == &other) return *this;
		tree = other.tree;
		key_alloc = other.key_alloc;
		return *this;
	}

// get allocator 
	allocator_type get_allocator() const { return key_alloc; }

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
	size_type max_size() const { return tree.max_size(); }

// clear 
	void clear() { tree.clear(); }

// insert 
	ft::pair<iterator, bool> insert(const value_type& value) {
		return tree.insert(value);
	}
	iterator insert(iterator hint, const value_type& value) {
		return tree.insert(hint, value);
	}
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {
		return tree.insert(first, last);
	}

// erase 
	void erase(iterator pos) { tree.erase(pos); }
	void erase(iterator first, iterator last) { tree.erase(first, last); }
	size_type erase(const Key& key) { return tree.erase(key); }

// swap 
	void swap(set& other) {
		ft::swap(tree, other.tree);
		std::swap(key_alloc, other.key_alloc);
	}

// count 
	size_type count(const Key& key) const { return tree.find(key) != tree.end(); }

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
	value_compare value_comp() const { return value_compare(); }

// friend operators for private tree access 
	template <typename K, class C, class A>
	friend bool operator ==
	(const set<K,C,A>& lhs, const set<K,C,A>& hrs);
	template <typename K, class C, class A>
	friend bool operator <
	(const set<K,C,A>& lhs, const set<K,C,A>& hrs);

}; // ! class set

// set comparison 
template <class Key, class Compare, class Alloc>
inline bool
operator == (const ft::set<Key, Compare, Alloc>& lhs, const ft::set<Key, Compare, Alloc>& rhs) {
	return lhs.tree == rhs.tree;
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
