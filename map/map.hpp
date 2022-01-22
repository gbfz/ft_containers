#pragma  once
#include <memory>
#include <stdexcept>
#include <algorithm>
// TODO: normal includes
#include "rbtree.hpp"
#include "../utilities/pair.hpp"
// #include "../utilities/comparison.hpp"

namespace ft {

template <typename Key, typename T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
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
	typedef RBTree<value_type, allocator_type>	RBTree;
	typedef typename RBTree::iterator		iterator;
	typedef typename RBTree::const_iterator		const_iterator;
	/*
	typedef tree_iterator<value_type, map>		iterator;
	typedef tree_iterator<const value_type, map>	const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	*/

private:
// underlying red-black tree data structure 
	// RBTree<value_type, allocator_type>		tree;
	RBTree tree;

public:
// ctors, dtor 
	map(): tree() {}
	explicit map(const Compare& comp, const Allocator& alloc = Allocator()):
		tree(comp, alloc) {}
	template <typename InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): tree(comp, alloc) {
		for (; first != last; ++first)
			tree.insert(*first);
	}
	map(const map& other): tree(other.tree) {}
	~map() {}

	void insert(const value_type& d) {
		tree.insert(d);
	}

	void print() {
		tree.print();
	}

	iterator begin() {
		return tree.begin();
	}

	iterator end() {
		return tree.end();
	}

	reference operator * () const { return tree.operator*(); }

	pointer operator -> () const { return tree.operator->(); }
};

} // ! namespace ft
