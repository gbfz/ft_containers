#pragma once
#include "../utilities/ft_type_traits.hpp"

namespace ft {

// node color definition 
typedef bool	color_t;
#define red	false
#define black	true

// Node definition 
template <typename T>
struct RBNode {
// data fields 
	T		value;
	color_t		color;
	RBNode*		mom;
	RBNode*		left;
	RBNode*		right;
	bool		is_nil; // sorry 

// unnecessary ctors, dtor 
	RBNode():
		color(black), mom(0), left(0), right(0) {}
	RBNode(const T& v):
		value(v), color(red), mom(0), left(0), right(0) {}
	explicit RBNode(const RBNode& other):
		value(other.value), color(other.color),
		mom(other.mom), left(other.left), right(other.right) {}
	template <typename O> // do i need this ???
	RBNode(const RBNode<typename enable_if_same<T, O, T>::type>& other):
		value(other.value), color(other.color),
		mom(other.mom), left(other.left), right(other.right) {}
	~RBNode() {}

// operator = 
	RBNode& operator = (const RBNode& other) {
		value = other.value;
		color = other.color;
		mom = other.mom;
		left = other.left;
		right = other.right;
		return *this;
	}
	RBNode* operator = (const RBNode*& other) {
		value = other->value;
		color = other->color;
		mom = other->mom;
		left = other->left;
		right = other->right;
		return this;
	}
// swap 
	void swap(RBNode* b) {
		T t = b->value;
		b->value = value;
		value = t;
	}
};

// node comparison 
template <typename T>
inline bool
operator == (const RBNode<T>* lhs, const RBNode<T>* rhs) {
	return lhs->value == rhs->value &&
		lhs->color == rhs->color &&
		lhs->mom == rhs->mom &&
		lhs->left == rhs->left &&
		lhs->right == rhs->right;
}
template <typename T>
inline bool
operator != (const RBNode<T>* lhs, const RBNode<T>* rhs) {
	return !(lhs == rhs);
}

// swap 
template <typename T>
inline void swap(RBNode<T>* lhs, RBNode<T>* rhs) {
	lhs->swap(rhs);
}

} // ! namespace ft
