#include "rbnode.hpp"
#include <functional>
#include <memory>
// TODO: normal includes 
#include "../iterator/tree_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../utilities/pair.hpp"
#include <iostream> // TODO: delete 
#include <limits>

namespace ft {

// ascii color defines 
#define RED "\033[1;31m"
#define BLK "\033[1;30m"
#define RESET "\033[0m"

template<class Value, class Compare = std::less<Value>,
	 class Allocator = std::allocator<Value>
> class RBTree {
public:
// type definitions 
	typedef Value					value_type;
	typedef Allocator				Value_alloc;
	typedef typename Value_alloc::
		template rebind<RBNode<Value> >::other	Node_alloc;
	typedef	typename Node_alloc::pointer		Nodeptr;
	typedef Compare					key_compare;
	typedef tree_iterator<value_type>		iterator;
	typedef tree_iterator<const value_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

protected:
// comparison functor 
	class value_compare {
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
		protected:
			Compare	comp;
		public:
			value_compare(Compare c): comp(c) {}
			bool operator () (const value_type& lhs, const value_type& rhs) const {
				return lhs.first < rhs.first;
			}
	};

private:
// data fields 
	Value_alloc	value_alloc;
	Node_alloc	node_alloc;
	Nodeptr		nil;
	Nodeptr		header;
	Nodeptr		root;
	size_t		tree_size;
	value_compare	comp;

public:
// ctors, dtor 
	RBTree(): // {
		value_alloc(Value_alloc()), node_alloc(Node_alloc()),
		nil(create_nil_node()), root(nil), tree_size(0), comp(key_compare()) {
			header = create_nil_node();
			header->mom = nil;
			header->left = header;
			header->right = header;
			header->color = red;
			root->color = black;
			root->right = header;
	}
	explicit RBTree(const RBTree& other): // {
		value_alloc(other.value_alloc), node_alloc(other.node_alloc),//, comp(other.comp),
		comp(other.comp), nil(other.nil), header(other.header), root(other.root), tree_size(other.tree_size) {
	}
	~RBTree() {
		clear();
		if (header != nil) delete header;
		delete nil;
	}

// operator = 
	RBTree operator = (const RBTree& other) {
		value_alloc = other.value_alloc;
		node_alloc = other.node_alloc;
		comp = other.comp;
		nil = other.nil;
		header = other.header;
		root = other.root;
		tree_size = other.tree_size;
	}

// print 
	void print(Nodeptr node, int offset) const {
		if (is_nil(node)) return;
		print(node->right, offset + 4);
		if (is_red(node)) std::cout << RED;
		else std::cout << BLK;
		std::cout << std::string(offset, '-');
		// std::cout << ' ' << node->value.first << ", " << node->value.second << endl;
		std::cout << ' ' << node->value.first << std::endl;
		std::cout << RESET;
		print(node->left, offset + 4);
	}
	void print() const {
		print(root, 0);
		std::cout << std::string(53, '~') << std::endl;
	}

private:
// create nil node 
	Nodeptr create_nil_node() {
		Nodeptr _nil = node_alloc.allocate(1);
		value_alloc.construct(&_nil->value, Value());
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

public:
// begin, rbegin 
	iterator begin() {
		return iterator(header->right);
	}
	const_iterator begin() const {
		return const_iterator(header->right);
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

// size 
	size_t size() const { return tree_size; }

// empty 
	bool empty() const { return begin() == end(); }

// find 
	iterator find(const value_type& value) {
		Nodeptr node = root;
		while (not_nil(node) && value != node->value) {
			if (comp(value, node->value))
				node = node->left;
			else node = node->right;
		}
		if (is_nil(node)) return end();
		return iterator(node);
	}
	const_iterator find(const value_type& value) const {
		Nodeptr node = root;
		while (not_nil(node) && value != node->value) {
			if (comp(value, node->value))
				node = node->left;
			else node = node->right;
		}
		if (is_nil(node)) return end();
		return const_iterator(node);
	}

// lower bound 
	iterator lower_bound(const value_type& value) {
		if (comp(value, header->right->value))
			return begin();
		if (comp(header->left->value, value))
			return end();
		Nodeptr node = root;
		while (!comp(value, node->left->value))
			node = node->left;
		while (comp(node->value, value))
			node = node->right;
		return iterator(node);
	}
	const_iterator lower_bound(const value_type& value) const {
		if (comp(value, header->right->value))
			return begin();
		if (comp(header->left->value, value))
			return end();
		Nodeptr node = root;
		while (!comp(value, node->left->value))
			node = node->left;
		while (comp(node->value, value))
			node = node->right;
		return const_iterator(node);
	}

// upper bound 
	iterator upper_bound(const value_type& value) {
		iterator lb = lower_bound(value);
		// if (value == lb)
		if (!comp(value, *lb))
			return ++lb;
		return lb;
	}
	const_iterator upper_bound(const value_type& value) const {
		const_iterator lb = lower_bound(value);
		// if (value == lb)
		if (!comp(value, lb.base()->value))
			return ++lb;
		return lb;
	}

// equal range 
	ft::pair<iterator, iterator> equal_range(const value_type& value) {
		return ft::make_pair(lower_bound(value), upper_bound(value));
	}
	ft::pair<const_iterator, const_iterator> equal_range(const value_type& value) const {
		return ft::make_pair(lower_bound(value), upper_bound(value));
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
		// node_alloc.destroy(node);
		node_alloc.deallocate(node, 1);
	}

// clear 
	void clear() {
		delete_node(root);
		root = header;
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

// is left or is right child 
	bool is_left_child (Nodeptr node) { return node == node->mom->left; }
	bool is_right_child(Nodeptr node) { return node == node->mom->right; }

// flip color 
	void flip_color(Nodeptr node) {
		if (node->color == red)
			node->color = black;
		else node->color = red;
	}

// maintain header pointers 
	void maintain_header() {
		header->left = rightmost(root);
		header->left->right = header;
		header->right = leftmost(root);
	}

// transplant value 
	void transplant_value(Nodeptr where, Nodeptr what) {
		value_alloc.destroy(&where->value);
		value_alloc.construct(&where->value, what->value);
	}

// update mom 
	void update_mom(Nodeptr node, Nodeptr newNode) {
		if (node == root)
			root = newNode;
		else if (is_left_child(node))
			node->mom->left = newNode;
		else node->mom->right = newNode;
		if (not_nil(newNode)) newNode->mom = node->mom;
	}

// rotate 
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

public:
// insert 
// insert data 
	ft::pair<iterator, bool> insert(const value_type& data) {
		Nodeptr node = create_node(data);
		root = insert(root, node);
		insert_rebalance(node);
		maintain_header();
		++tree_size;
		return ft::make_pair(iterator(node), true);
	}

// insert from iterator range 
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {
		while (first != last)
			insert(*first++);
	}

// insert at hinted position 
	iterator insert(iterator hint, const value_type& value) {
		iterator f = find(value);
		if (f != end()) return f;
		Nodeptr node = create_node(value);
		if (hint == begin()) {
			if (!empty() && comp(value, *hint))
				insert(node, leftmost(root));
			else insert(node, root);
		}
		else if (hint == end()) {
			if (!empty() && comp(*--hint, value))
				insert(node, header->left);
			else insert(node, root);
		}
		else insert(node, root);
		insert_rebalance(node);
		++tree_size;
		maintain_header();
		return iterator(node);
	}

private:
// insert rebalance 
	void insert_rebalance(Nodeptr node) {
		Nodeptr ma = node->mom;
		if (node != root && is_red(ma)) {
			Nodeptr grandma = ma->mom;
			Nodeptr aunt = is_left_child(ma) ?
					  grandma->right : grandma->left;
			if (is_red(aunt)) {
				flip_color(ma), flip_color(aunt), flip_color(grandma);
				insert_rebalance(grandma);
			}
			else if (is_left_child(ma)) {
				if (is_right_child(node))
					rotate_left(node = node->mom);
				flip_color(node->mom), flip_color(node->mom->mom);
				rotate_right(node->mom->mom);
			} else {
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
		if (is_nil(where)) return node; // TODO: what if i'm inserting into an empty tree?
		if (comp(node->value, where->value)) {
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
// erase 
// erase at pos 
	void erase(iterator pos) {
	// template <typename Iter>
	// void erase(tree_iterator <typename enable_if_same<iterator, Iter, Iter>::type>& pos) {
		erase(pos.base());
		maintain_header();
		--tree_size;
	}

// erase iterator range 
	template <typename InputIt>
	void erase(InputIt first, InputIt last) {
		while (first != last)
			erase(first++);
	}

// erase data 
	template <typename Key>
	bool erase(const Key& key) {
	// bool erase(const typename remove_const<Key>::type& key) {
		Nodeptr node = find(key).base();
		if (is_nil(node))
			return 0;
		erase(node);
		maintain_header();
		--tree_size;
		return 1;
	}

private:
// get promoted kid 
	Nodeptr get_promoted_kid(Nodeptr node) {
		Nodeptr kid = not_nil(node->left) ? node->left : node->right;
		if (is_black(node)) kid->color = black;
		return kid;
	}

// get niece for rebalance case 2 
	Nodeptr get_niece(Nodeptr node, Nodeptr sis) {
		if (sis->left->color != sis->right->color)
			return is_red(sis->right) ? sis->right : sis->left;
		return is_left_child(node) ? sis->right : sis->left;
	}

// erase rebalance 
	void erase_rebalance(Nodeptr node) {
		if (node == root) return;
		Nodeptr ma = node->mom,
			sis = is_left_child(node) ? ma->right : ma->left,
			niece = get_niece(node, sis);
		if (is_red(sis)) {						// case 1
			rotate_x_around_y(sis, ma);
			sis->color = black, ma->color = red;
			return erase_rebalance(node);
		}
		if (is_red(niece)) {						// case 2
			if (is_left_child(node) && is_left_child(niece))
				rotate_right(sis); 
			else if (is_right_child(node) && is_right_child(niece))
				rotate_left(sis);
			color_t ma_color = ma->color;
			rotate_x_around_y(sis, ma);
			niece->color = ma->color = black;
			sis->color = ma_color;
		} else {							// case 3
			node->color = black, sis->color = red;
			if (ma->color == red) ma->color = black;
			else if (ma != root) erase_rebalance(ma);
		}
	}

// erase node 
	void erase(Nodeptr node) {
		int kids_count = not_nil(node->left) + not_nil(node->right);
		switch (kids_count) {
			case 0: if (is_black(node)) erase_rebalance(node);
				update_mom(node, nil);
				return delete node;
			case 1: update_mom(node, get_promoted_kid(node));
				return delete node;
			case 2: Nodeptr pred = iterator::tree_decrement(node);
				transplant_value(node, pred);
				return erase(pred);
		}
	}

public:
// swap 
	void swap(RBTree& other) {
		std::swap(nil, other.nil);
		std::swap(header, other.header);
		std::swap(root, other.root);
		std::swap(tree_size, other.tree_size);
		std::swap(node_alloc, other.node_alloc);
		std::swap(value_alloc, other.value_alloc);
		std::swap(comp, other.comp);
	}

// key compare, value compare 
	key_compare key_comp() const { return key_compare(); }
	value_compare value_comp() const { return comp; }

}; // ! rbtree 

// swap 
template <typename V, typename C, typename A>
void swap(RBTree<V, C, A>& lhs, RBTree<V, C, A>& rhs) {
	lhs.swap(rhs);
}

} // ! namespace ft
