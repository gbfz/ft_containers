#pragma once
#include "../utilities/ft_type_traits.hpp"

namespace ft {

// color definition (i'm not some loser to just use #define) 
struct black_t {};
struct red_t {};

extern const black_t	black;
extern const red_t	red;

struct color_t {

	bool color;
	color_t(black_t): color(true) {}
	color_t(red_t): color(false) {}

	color_t& operator = (black_t) { color = true; return *this; }
	color_t& operator = (red_t  ) { color = false; return *this; }

	bool operator == (color_t other) const { return color == other.color; }
	bool operator != (color_t other) const { return color != other.color; }
	bool operator == (red_t) const { return color == false; }
	bool operator != (red_t) const { return color != false; }
	bool operator == (black_t) const { return color == true; }
	bool operator != (black_t) const { return color != true; }
};

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
		value(T()), color(black),
		mom(0), left(0), right(0), is_nil(true) {}
	RBNode(const T& v):
		value(v), color(red),
		mom(0), left(0), right(0), is_nil(false) {}
	explicit RBNode(const RBNode& other):
		value(other.value), color(other.color),
		mom(other.mom), left(other.left), right(other.right),
       		is_nil(other.is_nil) {}
	~RBNode() {}

// operator = 
	RBNode& operator = (const RBNode& other) {
		value = other.value;
		color = other.color;
		mom = other.mom;
		left = other.left;
		right = other.right;
		is_nil = other.is_nil;
		return *this;
	}

}; // ! rbnode

// nil check
template <typename T> inline
bool is_nil(RBNode<T>* node) { return node->is_nil == true; }
template <typename T> inline
bool not_nil(RBNode<T>* node) { return node->is_nil == false; }

} // ! namespace ft
