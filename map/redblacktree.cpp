#include <iostream>
using namespace std;

#define BLACK 0
#define RED   1

#define is_left_child(x) x == x->mom->left
#define is_right_child(x) x == x->mom->right
#define has_left_child(x) x->left != NULL
#define has_right_child(x) x->right != NULL
#define flip_color(x) x->color = (x->color == RED ? BLACK : RED)

template <typename T>
struct RBNode {
// typedefs 
	typedef T		value_type;
	typedef RBNode<T>*	Nodeptr;

// data 
	value_type	key;
	bool		color;
	Nodeptr		mom;
	Nodeptr		left;
	Nodeptr		right;

// ctors 
	RBNode():
		color(BLACK), mom(NULL), left(NULL), right(NULL) {}
	RBNode(const T& k):
		key(k), color(RED),
		mom(NULL), left(NULL), right(NULL) {}
	RBNode(const T& k, bool c, Nodeptr p, Nodeptr l, Nodeptr r):
		key(k), color(c),
		mom(p), left(l), right(r) {}
	RBNode(const Nodeptr other):
		key(other->key), color(BLACK),
		mom(other->mom), left(other->left), right(other->right) {}

};

template <typename T>
class RBTree {
private:
	typedef T		value_type;
	typedef RBTree<T>	Tree;
	typedef RBNode<T>	Node;
	typedef RBNode<T>*	Nodeptr;
public:
// data 
	Nodeptr	root;
	size_t	tree_size;
// ctors 
	RBTree(): root(new Node()), tree_size(0) {
		root->color = BLACK;
	}
	RBTree(const value_type& k): root(new Node(k)), tree_size(1) {
		root->color = BLACK;
	}
private:
// recolor and rotate 
	void update_moms_kids(Nodeptr node, Nodeptr tmpNode) {
		if (node->mom == NULL)
			root = tmpNode;
		else if (is_left_child(node))
			node->mom->left = tmpNode;
		else node->mom->right = tmpNode;
	}
	void rotate_right(Nodeptr node) {
		Nodeptr origLeft = node->left;
		node->left = origLeft->right;
		if (node->left != NULL)
			node->left->mom = node;
		origLeft->right = node;
		origLeft->mom = node->mom;
		update_moms_kids(node, origLeft);
		node->mom = origLeft;
	}
	void rotate_left(Nodeptr node) {
		Nodeptr origRight = node->right;
		node->right = origRight->left;
		if (node->right != NULL)
			node->right->mom = node;
		origRight->left = node;
		origRight->mom = node->mom;
		update_moms_kids(node, origRight);
		node->mom = origRight;
	}
	void handle_left_situations(Nodeptr node, Nodeptr mom, Nodeptr grandma) {
		if (is_right_child(node))
			rotate_left(mom);
		flip_color(mom);
		flip_color(grandma);
		rotate_right(grandma);
		recolor_and_rotate(is_left_child(node) ? mom : grandma);
	}
	void handle_right_situations(Nodeptr node, Nodeptr mom, Nodeptr grandma) {
		if (is_left_child(node))
			rotate_right(mom);
		flip_color(mom);
		flip_color(grandma);
		rotate_left(grandma);
		recolor_and_rotate(is_right_child(node) ? mom : grandma);
	}
	void recolor_and_rotate(Nodeptr node) {
		Nodeptr parent = node->mom;
		if (node != root && parent->color == RED) {
			Nodeptr grandma = node->mom->mom;
			Nodeptr aunt = is_left_child(parent) ?
					   grandma->right : grandma->left;
			if (aunt != NULL && aunt->color == RED) {
				flip_color(parent), flip_color(aunt), flip_color(grandma);
				recolor_and_rotate(grandma);
			}
			else if (is_left_child(parent))
				handle_left_situations(node, parent, grandma);
			else if (is_right_child(parent))
				handle_right_situations(node, parent, grandma);
		}
		root->color = BLACK;
	}

private:
// insert 
	Nodeptr insert(Nodeptr where, Nodeptr newNode) {
		if (where == NULL)
			return newNode;
		if (newNode->key < where->key) {
			where->left = insert(where->left, newNode);
			where->left->mom = where;
		}
		else if (newNode->key > where->key) {
			where->right = insert(where->right, newNode);
			where->right->mom = where;
		}
		return where;
	}
public:
	void insert(const value_type& data) {
		Nodeptr node = new Node(data);
		root = insert(root, node);
		recolor_and_rotate(node);
	}

};

// print 
template <typename T>
void print(RBNode<T>* root, int offset = 0) {
	if (root == NULL) return;
	print(root->right, offset + 4);
	cout << string(offset, '-') << root->key << endl;
	print(root->left, offset + 4);
}
template <typename T>
void print(RBTree<T>* tree) {
	print(tree->root);
	cout << string(20, '~') << endl;
}
template<typename T>
void print(RBTree<T>& tree) {
	print(tree.root);
	cout << string(20, '~') << endl;
}

void test1() {
	RBTree<int> t(5);
	t.insert(9);
	print(t);
	t.insert(2);
	print(t);
	t.insert(3);
	print(t);
	t.insert(12);
	print(t);
	t.insert(17);
	print(t);
	t.insert(19);
	print(t);
	t.insert(20);
	print(t);
}

int main() {
	test1();
}
