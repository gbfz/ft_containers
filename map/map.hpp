#pragma  once
#include <memory>
#include <stdexcept>
#include <algorithm>
// TODO: normal includes
#include "rbtree.hpp"
#include "../utilities/pair.hpp"
#include "../utilities/comparison.hpp"

namespace ft {

template<class Key, class T,
	 class Compare = std::less<Key>,
	 class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
// member types definitions 
	typedef Key					key_type;
	typedef T					mapped_type;
	typedef ft::pair<const Key, T>			value_type;
	typedef size_t					size_type;
	typedef ptrdiff_t				difference_type;
	typedef Compare					key_compare;
	typedef Allocator				allocator_type;
	typedef value_type&				reference;
	typedef const value_type&			const_reference;
	typedef typename Allocator::pointer		pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef tree_iterator<value_type>		iterator;
	typedef tree_iterator<const value_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
// underlying red-black tree data structure 
	RBTree<value_type, allocator_type> tree;

public:
// TODO: hide 
	void print() { tree.print(); }

// ctors, dtor 
	map(): tree() {}
	explicit map(const Compare& comp, const Allocator& alloc = Allocator()):
		tree(comp, alloc) {}
	template <typename InputIt>
	map(InputIt first, InputIt last,
		const Compare& comp = Compare(),
		const Allocator& alloc = Allocator()): tree(comp, alloc) {
		for (; first != last; ++first)
			tree.insert(*first);
	}
	map(const map& other): tree(other.tree) {}
	~map() {}

// find 
	iterator find(const Key& key) {
		return iterator(tree.find(key));
	}
	const_iterator find(const Key& key) const {
		return const_iterator(tree.find(key));
	}

// insert 
	ft::pair<iterator, bool> insert(const value_type& d) {
		iterator f = find(d.first);
		if (f != end())
			return ft::make_pair(f, false);
		return tree.insert(d);
	}
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {
		tree.insert(first, last);
	}

// erase 
	size_type erase(const Key& key) {
		return tree.erase(key);
	}
	void erase(iterator pos) {
		tree.erase(pos);
	}
	template <typename InputIt>
	void erase(InputIt first, InputIt last) {
		tree.erase(first, last);
	}

// [] 
	T& operator [] (const Key& key) {
		return insert(ft::make_pair(key, T())).first->second;
	}

// at 
	T& at(const Key& key) {
		iterator f = find(key);
		if (f == end())
			throw std::out_of_range("no map element at given key");
		return f->second;
	}

// count 
	size_type count(const Key& key) const {
		return tree.find(key) != tree.end();
	}

// clear 
	void clear() { tree.clear(); }

// lower bound 
	iterator lower_bound(const Key& key) { return tree.lower_bound(key); }
	const_iterator lower_bound(const Key& key) const { return tree.lower_bound(key); }

// upper bound
	iterator upper_bound(const Key& key) { return tree.upper_bound(key); }
	const_iterator upper_bound(const Key& key) const { return tree.upper_bound(key); }

// equal range 
	iterator equal_range(const Key& key) { return tree.equal_range(key); }
	const_iterator equal_range(const Key& key) const { return tree.equal_range(key); }

// begin, rbegin 
	iterator begin() { return tree.begin(); }
	const_iterator begin() const { return tree.begin(); }

// end, rend 
	iterator end() { return tree.end(); }
	const_iterator end() const { return tree.end(); }

// size 
	size_type size() const { return tree.size(); }

// swap 
	void swap(map& other) {
		tree.swap(other.tree);
	}

};

// map comparison 
template <class Key, class T, class Compare, class Alloc>
bool operator == (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class Key, class T, class Compare, class Alloc>
bool operator != (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator < (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class Key, class T, class Compare, class Alloc>
bool operator > (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return rhs < lhs;
}
template <class Key, class T, class Compare, class Alloc>
bool operator <= (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(rhs < lhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator >= (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}

// swap 
template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
	lhs.swap(rhs);
}

} // ! namespace ft
