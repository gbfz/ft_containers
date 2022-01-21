#pragma once
// TODO: normal includes 
#include <iostream>
#include <unistd.h>
using namespace std;
#include "../map/rbnode.hpp"
#include "../utilities/ft_type_traits.hpp"
#include "ft_iterator_base_types.hpp"

namespace ft {

// not_nil method i need for iterator movement 
template <typename Nodeptr> static inline
bool not_nil(Nodeptr node) {
	return node->is_nil == false;
}

// tree increment 
template <typename Nodeptr> static
Nodeptr	tree_increment(Nodeptr node) {
	if (node->color == red && node->right->mom == node)
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

// tree decrement 
template <typename Nodeptr> static 
Nodeptr	tree_decrement(Nodeptr node) {
	if (node->color == red && node->right->mom == node)
		return node = node->mom;
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


template <typename _node, typename _container>
class tree_iterator {
protected:
// memory accessor 
	typedef typename _container::pointer		this_iterator;
	_node						_base;

public:
// member type definitions 
	typedef iterator_traits<_node>			traits;
	typedef typename traits::value_type		value_type;
	typedef typename traits::pointer		pointer;
	typedef typename traits::reference		reference;
	typedef typename traits::difference_type	difference_type;
	typedef typename traits::iterator_category	iterator_category;

// ctors, dtor  
	// Default constructor 
	tree_iterator(): _base(_node()) {}
	// Regular copy constructor 
	explicit tree_iterator(const _node& other): _base(other) {}
	// Copy constructor that allows iterator to const_iterator conversion
	template <typename other>
	tree_iterator(const tree_iterator
			<other, typename enable_if_same<this_iterator, other,
			_container>::type>& source): _base(source.base()) {}
	~tree_iterator() {}

// operator = 
	template <typename other>
	tree_iterator operator = (const tree_iterator
			<other, typename enable_if_same<this_iterator, other,
			_container>::type>& source) {
		_base = source.base();
		return *this;
	}

// *, -> 
	reference operator * () const {
		return *_base;
	}

	pointer operator -> () const {
		return _base;
	}

// ++ 
	tree_iterator& operator ++ () {
		_base = tree_increment(_base);
		return *this;
	}

	tree_iterator operator ++ (int) {
		tree_iterator it = *this;
		++_base;
		return it;
	}

// -- 
	tree_iterator& operator -- () {
		_base = tree_decrement(_base);
		return *this;
	}

	tree_iterator operator -- (int) {
		tree_iterator it = *this;
		--_base;
		return it;
	}

// base 
	const _node& base() const {
		return _base;
	}

};

// iterator comparison 
template <typename typeL, typename typeR, typename _container>
inline bool
operator ==
(const tree_iterator<typeL, _container>& lhs,
 const tree_iterator<typeR, _container>& rhs) {
	return lhs.base() == rhs.base();
}

template <typename typeL, typename typeR, typename _container>
inline bool
operator !=
(const tree_iterator<typeL, _container>& lhs,
 const tree_iterator<typeR, _container>& rhs) {
	return !(lhs == rhs);
}


} // ! namespace ft
