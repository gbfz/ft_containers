#pragma once
// TODO: delete 
#include <iostream>
#include <unistd.h>
using namespace std;
// TODO: normal includes 
#include "../map/rbnode.hpp"
#include "../utilities/ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"

namespace ft {

// nil check methods i need for iterator movement 
template <typename Nodeptr> static inline
bool is_nil(Nodeptr node) { return node->is_nil == true; }
template <typename Nodeptr> static inline
bool not_nil(Nodeptr node) { return node->is_nil == false; }

// tree increment 
template <typename Nodeptr> static
Nodeptr	tree_increment(Nodeptr node) {
	// if (node->color == red && node->right->mom == node)
		// return node = node->right;
	if (not_nil(node->right)) {
		node = node->right;
		while (not_nil(node->left))
			node = node->left;
		return node;
	}
	Nodeptr ma = node->mom;
	while (node == ma->right) {
		node = ma;
		ma = ma->mom;
	}
	if (node->right != ma)
		node = ma;
	return node;
}

// tree decrement 
template <typename Nodeptr> static 
Nodeptr	tree_decrement(Nodeptr node) {
	// if (is_nil(node))
		// return node = node->mom;
	if (not_nil(node->left)) {
		node = node->left;
		while (not_nil(node->right))
			node = node->right;
		return node;
	}
	Nodeptr ma = node->mom;
	while (node == ma->left) {
		node = ma;
		ma = ma->mom;
	}
	if (node->left != ma)
		node = ma;
	return node;
}


template <typename Value>
class tree_iterator {
public:
// member type definitions 
	typedef iterator_traits <Value*>		traits;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
	typedef typename traits::iterator_category	iterator_category;
private:
// memory accessor 
	typedef RBNode<typename ft::remove_const<value_type>
				  ::type>*		Nodeptr;
	Nodeptr		node;

// ctors, dtor  
	// Default constructor 
public:
	tree_iterator() {}
	tree_iterator(Nodeptr other):
		node(static_cast<Nodeptr>(other)) {}
	tree_iterator(const tree_iterator<const value_type>& other): node(other.base()) {}
	// tree_iterator(const tree_iterator<typename ft::remove_const<value_type>::type>& other):
		// node(other.base()) {}
	~tree_iterator() {}


// operator = 
	template <typename _other>
	tree_iterator operator = (const tree_iterator<typename ft::remove_const
			<value_type>::type>& other) {
		node = other.base();
		return *this;
	}

// *, -> 
	reference operator * () const {
		return node->value;
	}
	pointer operator -> () const {
		return &node->value;
	}

// ++ 
	tree_iterator& operator ++ () {
		node = tree_increment(node);
		return *this;
	}
	tree_iterator operator ++ (int) {
		tree_iterator it = *this;
		++node;
		return it;
	}

// -- 
	tree_iterator& operator -- () {
		node = tree_decrement(node);
		return *this;
	}
	tree_iterator operator -- (int) {
		tree_iterator it = *this;
		--node;
		return it;
	}

// base 
	const Nodeptr& base() const {
		return node;
	}

};

// iterator comparison 
template <typename typeL, typename typeR>
inline bool
operator ==
(const tree_iterator<typeL>& lhs,
 const tree_iterator<typeR>& rhs) {
	return lhs.base() == rhs.base();
}
template <typename typeL, typename typeR>
inline bool
operator !=
(const tree_iterator<typeL>& lhs,
 const tree_iterator<typeR>& rhs) {
	return !(lhs == rhs);
}

} // ! namespace ft
