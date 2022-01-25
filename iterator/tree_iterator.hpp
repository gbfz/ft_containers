#pragma once
// TODO: normal includes 
#include "../map/rbnode.hpp"
#include "ft_iterator_base_types.hpp"

namespace ft {

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
	// typedef RBNode<typename ft::remove_const<value_type>::type>*	Nodeptr;
	typedef RBNode<value_type>*	Nodeptr;
	Nodeptr				node;

public:
// ctors, dtor 
	tree_iterator() {}
	tree_iterator(Nodeptr other): node(other) {}
	tree_iterator(const tree_iterator
			<const value_type>& other): node(other.base()) {}
	tree_iterator(const tree_iterator
			<typename ft::remove_const<value_type>::type>& other):
		node(other.base()) {}
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
// private:
	static Nodeptr tree_increment(Nodeptr node) {
		if (is_nil(node->right) && node->right->color == red)
			return node = node->right;
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
// public:
	tree_iterator& operator ++ () {
		node = tree_increment(node);
		return *this;
	}
	tree_iterator operator ++ (int) {
		tree_iterator it = *this;
		node = tree_increment(node);
		return it;
	}

// -- 
// private:
	static Nodeptr tree_decrement(Nodeptr node) {
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
// public:
	tree_iterator& operator -- () {
		node = tree_decrement(node);
		return *this;
	}
	tree_iterator operator -- (int) {
		tree_iterator it = *this;
		node = tree_decrement(node);
		return it;
	}

// base 
	const Nodeptr& base() const {
		return node;
	}

}; // ! tree iterator

// iterator comparison 
template <typename typeL, typename typeR>
inline bool
operator ==
(const tree_iterator<typeL>& lhs, const tree_iterator<typeR>& rhs) {
	return lhs.base() == rhs.base();
}
template <typename typeL, typename typeR>
inline bool
operator !=
(const tree_iterator<typeL>& lhs, const tree_iterator<typeR>& rhs) {
	return !(lhs == rhs);
}

} // ! namespace ft
