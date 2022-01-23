#pragma  once
#include <memory>
#include <stdexcept>
#include <algorithm>
// TODO: normal includes
#include "rbtree.hpp"
#include "../utilities/pair.hpp"
// #include "../utilities/comparison.hpp"

namespace ft {

template <class Key,
	 class T,
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
		return tree.insert(d);
	}
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {
		for (; first != last; ++first)
			tree.insert(*first);
	}

// erase 
	void erase(iterator pos) {
		return tree.erase(pos);
	}
	size_type erase(const Key& key) {
		return tree.erase(key);
	}

// count 
	size_type count(const Key& key) const {
		return tree.find(key) != tree.end();
	}

// clear 
	void clear() { tree.clear(); }

// TODO: hide 
	void print() { tree.print(); }

	iterator begin() { return tree.begin(); }
	const_iterator begin() const { return tree.begin(); }

	iterator end() { return tree.end(); }
	const_iterator end() const { return tree.end(); }

	reference operator * () const { return tree.operator * (); }
	pointer   operator ->() const { return tree.operator-> (); }
};

} // ! namespace ft
