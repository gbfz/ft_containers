#pragma once
#include "../utilities/ft_type_traits.hpp"

namespace ft {

// node color definition 
typedef bool	color_t;
#define red	false
#define black	true

template <typename T>
struct RBNode {
// data fields 
	T		value;
	color_t		color;
	RBNode*		mom;
	RBNode*		left;
	RBNode*		right;
	bool		is_nil; // sorry 

// ctors, dtor 
	RBNode():
		color(black), mom(0), left(0), right(0) {}
	RBNode(const T& v):
		value(v), color(red), mom(0), left(0), right(0) {}
	explicit RBNode(const RBNode& other):
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

// nil check 
	template <typename U> friend bool is_nil(RBNode* node);
	template <typename U> friend bool not_nil(RBNode* node);

};

// nil check definition 
template <typename T>
bool is_nil(RBNode<T>* node) { return node->is_nil == true; }
template <typename T>
bool not_nil(RBNode<T>* node) { return node->is_nil == false; }

} // ! namespace ft
