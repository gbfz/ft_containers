#include <iostream>
using namespace std;

#define RED "\033[1;31m"
#define BLK "\033[1;30m"
#define RESET "\033[0m"

typedef enum { red, black } color_t;

// Node definition 
template <typename T>
struct RBNode {
	T		key;
	color_t		color;
	RBNode*		mom;
	RBNode*		left;
	RBNode*		right;
	RBNode():
		color(black), mom(0), left(0), right(0) {}
	RBNode(const T& k):
		key(k), color(red), mom(0), left(0), right(0) {}
};

template <typename T>
class RBTree {
// type definitions 
private:
	typedef T		value_type;
	typedef RBNode<T>	Node;
	typedef Node*		Nodeptr;

// data fields 
public:
	Nodeptr	nil;
	Nodeptr	root;
	size_t	tree_size;

public:
// ctors, dtor 
	RBTree():
		nil(new Node()), root(nil), tree_size(0) {}
	RBTree(const value_type& key):
		nil(new Node()), root(create_node(key)), tree_size(1) {
			root->color = black;
		}
	~RBTree() { delete nil; }

public:
// print 
	void print(Nodeptr node, int offset) const {
		if (is_nil(node)) return;
		print(node->right, offset + 4);
		if (is_red(node)) cout << RED;
		else cout << BLK;
		cout << string(offset, '-') << ' ' << node->key << endl;
		cout << RESET;
		print(node->left, offset + 4);
	}
	void print() {
		print(root, 0);
		cout << string(53, '~') << endl;
	}

private:
// create node with nil leaves 
	Nodeptr create_node(const value_type& key) {
		Nodeptr node = new Node(key);
		node->mom = node->left = node->right = nil;
		return node;
	}

// is nil 
	bool is_nil(Nodeptr node) const { return node == nil; }
	bool not_nil(Nodeptr node) const { return node != nil; }

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
// successor 
	Nodeptr successor(Nodeptr node) {
		if (is_nil(node))
			return nil;
		if (not_nil(node->right))
			return node->right;
		value_type& ref_val = node->key;
		node = node->mom;
		while (not_nil(node->mom) && ref_val > node->key)
			node = node->mom;
		if (node->key < ref_val)
			return nil;
		return node;
	}

// predecessor 
	Nodeptr predecessor(Nodeptr node) {
		if (is_nil(node))
			return nil;
		if (not_nil(node->left))
			return node->left;
		value_type& ref_val = node->key;
		node = node->mom;
		while (not_nil(node->mom) && ref_val < node->key)
			node = node->mom;
		if (node->key > ref_val)
			return nil;
		return node;
	}

// find 
	Nodeptr find(const value_type& key) {
		if (is_nil(root)) return nil; // end()?
		Nodeptr node = root;
		while (key != node->key) {
			if (key < node->key)
				node = node->left;
			else node = node->right;
			if (is_nil(node)) return nil;
		}
		return node;
	}

// check color 
	bool is_black(const Nodeptr node) const { return node->color == black; }
	bool is_red(const Nodeptr node) const { return node->color == red; }

private:
// tell mom her kid has changed 
	void update_mom(Nodeptr node, Nodeptr newNode) {
		if (is_nil(node->mom))
			root = newNode;
		else if (is_left_child(node))
			node->mom->left = newNode;
		else node->mom->right = newNode;
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

// recolor and rotate (insert fixup ?)
	void recolor_and_rotate(Nodeptr node) {
		Nodeptr ma = node->mom;
		if (node != root && is_red(ma)) {
			Nodeptr grandma = ma->mom;
			Nodeptr aunt = is_left_child(ma) ?
					  grandma->right : grandma->left;
			if (not_nil(aunt) && is_red(aunt)) {
				flip_color(ma), flip_color(aunt), flip_color(grandma);
				recolor_and_rotate(grandma);
			}
			else if (is_left_child(ma)) {
				if (is_right_child(node)) {
					node = node->mom;
					rotate_left(node);
				}
				node->mom->color = black;
				node->mom->mom->color = red;
				rotate_right(node->mom->mom);
			}
			else if (is_right_child(ma)) {
				if (is_left_child(node)) {
					node = node->mom;
					rotate_right(node);
				}
				node->mom->color = black;
				node->mom->mom->color = red;
				rotate_left(node->mom->mom);
			}
		}
		root->color = black;
	}

// insert 
	Nodeptr insert(Nodeptr where, Nodeptr node) {
		if (is_nil(where)) return node;
		if (node->key < where->key) {
			where->left = insert(where->left, node);
			where->left->mom = where;
		}
		else if (node->key > where->key) {
			where->right = insert(where->right, node);
			where->right->mom = where;
		}
		return where;
	}
public:
	void insert(const value_type& data) {
		Nodeptr node = create_node(data);
		root = insert(root, node);
		recolor_and_rotate(node);
	}


// erase 
private:
	void erase(Nodeptr node) {
	}

	void erase(const value_type& data) {
		Nodeptr node = find(data);
		if (not_nil(node)) erase(node);
	}
};

void test1() {
	RBTree<int> t;
	t.insert(9);
	t.print();
	t.insert(10);
	t.print();
	t.insert(11);
	t.print();
	t.insert(12);
	t.print();
	t.insert(13);
	t.print();
	t.insert(3);
	t.print();
	t.insert(4);
	t.print();
}

void test2() {
	RBTree<int> t(5);
	t.insert(9); t.print();
	t.insert(2); t.print();
	t.insert(3); t.print();
	t.insert(12); t.print();
	t.insert(17); t.print();
	t.insert(19); t.print();
	t.insert(20); t.print();
}

void test3() {
	RBTree<int> t;
	t.insert(15); t.print();
	t.insert(6); t.print();
	t.insert(9); t.print();
	t.insert(19); t.print();
	t.insert(1); t.print();
	t.insert(2); t.print();
	t.insert(0); t.print();
}

int main() {
	test3();
}