#pragma once
#include "../utilities/ft_type_traits.hpp"

namespace ft {

// color definition (i'm not a loser to just use #define) 
struct black_t {};
struct red_t {};

extern const black_t	black;
extern const red_t	red;

struct color_t {
	bool color;

	color_t(black_t): color(true) {}
	color_t(red_t): color(false) {}

	inline color_t& operator = (black_t) { color = true; return *this; }
	inline color_t& operator = (red_t  ) { color = false; return *this; }

	inline bool operator == (color_t other) const { return color == other.color; }
	inline bool operator != (color_t other) const { return color != other.color; }
	inline bool operator == (red_t) const { return color == false; }
	inline bool operator != (red_t) const { return color != false; }
	inline bool operator == (black_t) const { return color == true; }
	inline bool operator != (black_t) const { return color != true; }
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

// nil check declaration 
	template <typename U> friend bool is_nil(RBNode* node);
	template <typename U> friend bool not_nil(RBNode* node);

};

// nil check definition 
template <typename T>
bool is_nil(RBNode<T>* node) { return node->is_nil == true; }
template <typename T>
bool not_nil(RBNode<T>* node) { return node->is_nil == false; }

} // ! namespace ft
