#include <iostream>
#include "rbnode.hpp"
// TODO: delete 
using namespace std; // TODO: delete !!!
#include <unistd.h>
#include <map>
// TODO: normal includes 
#include "../iterator/tree_iterator.hpp"
#include "../iterator/iterator.hpp"

namespace ft {

// ascii color defines 
#define RED "\033[1;31m"
#define BLK "\033[1;30m"
#define RESET "\033[0m"

template <typename Value, typename Compare = std::less<Value>, class Allocator = std::allocator<Value> >
class RBTree {
public:
// type definitions 
	typedef Value					value_type;
	typedef Allocator				Value_alloc;
	typedef Compare					compare_type;
	// typedef typename Value_alloc::reference 	reference;
	// typedef typename Value_alloc::const_reference	const_reference;
	typedef typename Value_alloc::pointer		pointer;
	typedef typename Value_alloc::const_pointer	const_pointer;
	typedef typename Value_alloc::
		template rebind<RBNode<Value> >::other	Node_alloc;
	typedef	typename Node_alloc::pointer		Nodeptr;
	typedef tree_iterator<Nodeptr, RBTree>		iterator;
	typedef tree_iterator<const Nodeptr, RBTree>	const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
// data fields 
	Value_alloc	value_alloc;
	Node_alloc	node_alloc;
	compare_type	comp;
	Nodeptr		nil;
	Nodeptr		header;
	Nodeptr		root;
	size_t		tree_size;

public:
// ctors, dtor 
	RBTree(): value_alloc(Value_alloc()), node_alloc(Node_alloc()),
		comp(compare_type()),
		nil(create_nil_node()), header(nil), root(nil), tree_size(0) {
			root->color = black;
			header->mom = root;
			header->left = root;
			header->right = root;
			header->color = red;
			header->is_nil = true;
	}
	explicit RBTree(const RBTree& other): value_alloc(other.value_alloc), node_alloc(other.node_alloc), comp(other.comp),
		nil(other.nil), header(other.header), root(other.root), tree_size(other.tree_size) {}
	~RBTree() {
		clear();
		if (header != nil) delete header;
		delete nil;
	}

// print 
	void print(Nodeptr node, int offset) const {
		if (is_nil(node)) return;
		print(node->right, offset + 4);
		if (is_red(node)) std::cout << RED;
		else std::cout << BLK;
		std::cout << std::string(offset, '-');// << ' ' << node->value << std::endl;
		std::cout << node->value.first << ", " << node->value.second << endl;
		std::cout << RESET;
		print(node->left, offset + 4);
	}
	void print() {
		print(root, 0);
		std::cout << std::string(53, '~') << std::endl;
	}

private:
// create nil node 
	Nodeptr create_nil_node() {
		Nodeptr _nil = node_alloc.allocate(1);
		_nil->mom = _nil->left = _nil->right = 0;
		_nil->color = black;
		_nil->is_nil = true;
		return _nil;
	}

// create node with nil leaves 
	Nodeptr create_node(const value_type& value) {
		Nodeptr node = node_alloc.allocate(1);
		value_alloc.construct(&node->value, value);
		node->mom = node->left = node->right = nil;
		node->color = red;
		node->is_nil = false;
		return node;
	}

// is nil 
	bool is_nil(Nodeptr node) const { return node == nil; }
	bool not_nil(Nodeptr node) const { return !is_nil(node); }

// children 
	bool is_left_child (Nodeptr node) { return node == node->mom->left; }
	bool is_right_child(Nodeptr node) { return node == node->mom->right; }

// flip color 
	void flip_color(Nodeptr node) {
		if (node->color == red)
			node->color = black;
		else node->color = red;
	}

public:
/*// successor 
	Nodeptr successor(Nodeptr node) {
		if (is_nil(node)) return nil;
		if (not_nil(node->right)) {
			node = node->right;
			while (node->left != nil)
				node = node->left;
			return node;
		}
		Nodeptr ma = node->mom;
		while (node == ma->right)
			node = ma, ma = ma->mom;
		if (node->right != ma)
			node = ma;
		return node;
	}

*/
// predecessor 
	Nodeptr predecessor(Nodeptr node) {
		if (is_nil(node)) return nil;
		if (not_nil(node->left)) {
			node = node->left;
			while (node->right != nil)
				node = node->right;
			return node;
		}
		Nodeptr ma = node->mom;
		while (node == ma->left)
			node = ma, ma = ma->mom;
		if (node->left != ma)
			node = ma;
		return node;
	}

// find 
	Nodeptr find(const value_type& value) {
		if (is_nil(root)) return nil; // end()?
		Nodeptr node = root;
		while (not_nil(node) && value != node->value) {
			if (value < node->value)
				node = node->left;
			else node = node->right;
		}
		return node;
	}

// delete node and children 
	void	delete_node(Nodeptr node) {
		if (is_nil(node))
			return;
		delete_node(node->left);
		delete_node(node->right);
		if (is_left_child(node))
			node->mom->left = nil;
		else node->mom->right = nil;
		value_alloc.destroy(&node->value);
		// value_alloc.deallocate(&node->value, 1);
		node_alloc.destroy(node);
		node_alloc.deallocate(node, 1);
	}

// clear 
	void clear() {
		delete_node(root);
		// root = header;
		header->left = root;
		header->mom = root;
		tree_size = 0;
	}

private:
// leftmost 
	Nodeptr leftmost(Nodeptr node) {
		if (is_nil(node)) return nil;
		while (not_nil(node->left))
			node = node->left;
		return node;
	}

// rightmost 
	Nodeptr rightmost(Nodeptr node) {
		if (is_nil(node)) return nil;
		while (not_nil(node->right))
			node = node->right;
		return node;
	}

// check color 
	bool is_black(const Nodeptr node) const { return node->color == black || is_nil(node); }
	bool is_red(const Nodeptr node) const { return node->color == red && node != header; }

// update mom 
	void update_mom(Nodeptr node, Nodeptr newNode) {
		if (node == root)
			root = newNode;
		else if (is_left_child(node))
			node->mom->left = newNode;
		else node->mom->right = newNode;
		if (not_nil(newNode)) newNode->mom = node->mom;
	}

// rotate left 
	void rotate_left(Nodeptr node) {
		Nodeptr origRight = node->right;
		node->right = origRight->left;
		if (not_nil(node->right))
			node->right->mom = node;
		origRight->left = node;
		origRight->mom = node->mom;
		update_mom(node, origRight);
		node->mom = origRight;
	}

// rotate right 
	void rotate_right(Nodeptr node) {
		Nodeptr origLeft = node->left;
		node->left = origLeft->right;
		if (not_nil(node->left))
			node->left->mom = node;
		origLeft->right = node;
		origLeft->mom = node->mom;
		update_mom(node, origLeft);
		node->mom = origLeft;
	}

// rotate x around y 
	void rotate_x_around_y(Nodeptr x, Nodeptr y) {
		if (is_left_child(x))
			rotate_right(y);
		else rotate_left(y);
	}

// insert rebalance 
	void insert_rebalance(Nodeptr node) {
		Nodeptr ma = node->mom;
		if (node != root && is_red(ma)) {
			Nodeptr grandma = ma->mom;
			Nodeptr aunt = is_left_child(ma) ?
					  grandma->right : grandma->left;
			if (not_nil(aunt) && is_red(aunt)) {
				flip_color(ma), flip_color(aunt), flip_color(grandma);
				insert_rebalance(grandma);
			}
			else if (is_left_child(ma)) {
				if (is_right_child(node))
					rotate_left(node = node->mom);
				flip_color(node->mom), flip_color(node->mom->mom);
				rotate_right(node->mom->mom);
			}
			else if (is_right_child(ma)) {
				if (is_left_child(node))
					rotate_right(node = node->mom);
				flip_color(node->mom), flip_color(node->mom->mom);
				rotate_left(node->mom->mom);
			}
		}
		root->color = black;
	}

// insert node 
	Nodeptr insert(Nodeptr where, Nodeptr node) {
		if (is_nil(where)) return node;
		if (node->value < where->value) {
		// if (comp(node->value, where->value)) {
			where->left = insert(where->left, node);
			where->left->mom = where;
		}
		else {
			where->right = insert(where->right, node);
			where->right->mom = where;
		}
		return where;
	}

public:
// insert data 
	void insert(const value_type& data) {
		   // Temp workaround
		   if (not_nil(find(data))) return;
		Nodeptr node = create_node(data);
		root = insert(root, node);
		insert_rebalance(node);
		header->left = leftmost(root);
		header->mom = rightmost(root);
		// header->right = header;
		++tree_size;
	}

private:
// get promoted kid 
	Nodeptr get_promoted_kid(Nodeptr node) {
		Nodeptr kid = not_nil(node->left) ? node->left : node->right;
		if (is_black(node)) kid->color = black;
		return kid;
	}

// get niece for rebalance case 2 
	Nodeptr get_best_red_niece(Nodeptr node, Nodeptr sis) {
		if (is_black(sis->left) && is_red(sis->right))
			return sis->right;
		if (is_black(sis->right) && is_red(sis->left))
			return sis->left;
		if (is_left_child(node))
			return sis->right;
		return sis->left;
	}

// erase rebalance 
	void erase_rebalance(Nodeptr node) {
		if (node == root) return;
		Nodeptr ma = node->mom,
			sis = is_left_child(node) ? ma->right : ma->left,
			niece = get_best_red_niece(node, sis);
		if (is_red(sis)) {					// case 1
			rotate_x_around_y(sis, ma);
			sis->color = black, ma->color = black;
			return erase_rebalance(node);
		}
		if (is_red(niece)) {					// case 2
			if (is_right_child(node) && is_right_child(niece))
				rotate_left(sis);
			else if (is_left_child(node) && is_left_child(niece))
				rotate_right(sis);
			color_t old_ma_color = ma->color;
			rotate_x_around_y(sis, ma);
			niece->color = ma->color = black;
			sis->color = old_ma_color;
		}
		else {							// case 3
			node->color = black, sis->color = red;
			if (ma->color == red) ma->color = black;
			else if (ma != root) erase_rebalance(ma);
		}
	}

// erase node 
	void erase(Nodeptr node) {
		int kids_count = (node->left != nil) + (node->right != nil);
		switch (kids_count) {
			case 0: if (is_black(node)) erase_rebalance(node);
				update_mom(node, nil);
				return delete node;
			case 1: update_mom(node, get_promoted_kid(node));
				return delete node;
			case 2: Nodeptr pred = predecessor(node);
				std::swap(node->value, pred->value);
				return erase(pred);
		}
	}

public:
// erase data 
	void erase(const value_type& data) {
		Nodeptr node = find(data);
		if (not_nil(node)) erase(node);
		header->left = leftmost(root);
		header->mom = rightmost(root);
		// header->right = header;
		--tree_size;
	}

// begin, rbegin 
	iterator begin() {
		return iterator(header->left);
	}
	const_iterator begin() const {
		return const_iterator(header->left);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(end());
	}

// end, rend 
	iterator end() {
		return iterator(header);
	}
	const_iterator end() const {
		return const_iterator(header);
	}
	reverse_iterator rend() {
		return reverse_iterator(begin());
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(begin());
	}

}; // ! rbtree 

} // ! namespace ft 