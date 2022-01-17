#include <iostream>
using namespace std;

#define BLACK 0
#define RED   1

/*
 * IDEA:
 * 	store nodes as pairs of <node, bool> where the latter tells whether it's the left child or right child
 */

template <typename T>
struct nodeBase {
	nodeBase* mom;
	nodeBase* left;
	nodeBase* right;
};

template <typename T>
struct nilNode: nodeBase<T> {
	static const bool color = BLACK;
};

template <typename T>
struct RBNode: nodeBase<T> {
// type definitions 
	typedef T		value_type;
	typedef nodeBase<T>	Base;
	typedef RBNode<T>*	Nodeptr;

	value_type	key;
	bool		color;
	Nodeptr		mom;
	Nodeptr		left;
	Nodeptr		right;
	RBNode(const value_type& k): key(k), color(RED) {}
	RBNode(const value_type& k, bool c): key(k), color(c) {}
};

/*
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
*/

template <typename T>
class RBTree {
// type definitions 
private:
	typedef T		value_type;
	typedef RBTree<T>	Tree;
	typedef RBNode<T>	Node;
	typedef RBNode<T>*	Nodeptr;

// data 
public:
	Nodeptr				root;
	size_t				tree_size;
	static const RBNode<void>*	nilNode;

// ctors 
	RBTree(): root(new Node(BLACK)), tree_size(0) {
		root->color = BLACK;
	}
	RBTree(const value_type& k): root(new Node(k)), tree_size(1) {
		root->color = BLACK;
	}

// helper methods 
private:
	bool is_left_child (Nodeptr node) { return node == node->mom->left; }
	bool is_right_child(Nodeptr node) { return node == node->mom->right; }
	bool has_one_child (Nodeptr node) { return !(node->left && node->right); }
	Nodeptr get_red_niece(Nodeptr node) {
		if (is_red(node->left)) return node->left;
		if (is_red(node->right)) return node->right;
		return NULL;
	}
	int count_kids(Nodeptr node) {
		bool left = node->left != NULL;
		bool right = node->right != NULL;
		return left + right;
	}
	void flip_color(Nodeptr node) { node->color = node->color == RED ? BLACK : RED; }
public:
	Nodeptr successor(Nodeptr node) {
		if (node == NULL) return NULL;
		if (node->right)
			return node->right;
		const value_type ref_val = node->key;
		node = node->mom;
		while (node->mom && ref_val > node->key)
			node = node->mom;
		if (node->key < ref_val) return NULL;
		return node;
	}
	Nodeptr predecessor(Nodeptr node) {
		if (node == NULL) return NULL;
		if (node->left)
			return node->left;
		const value_type ref_val = node->key;
		node = node->mom;
		while (node->mom && ref_val < node->key)
			node = node->mom;
		if (node->key > ref_val)
			return NULL;
		return node;
	}
	Nodeptr find (const value_type& key) {
		if (root == NULL) return NULL;
		Nodeptr node = root;
		while (key != node->key) {
			if (key < node->key)
				node = node->left;
			else if (key > node->key)
				node = node->right;
			if (node == NULL)
				return NULL;
		}
		return node;
	}
	bool is_nil(const Nodeptr node) {
		return node == NULL;
	}
	bool has_no_kids(const Nodeptr node) {
		return is_nil(node->left) && is_nil(node->right);
	}
	bool is_black(const Nodeptr node) {
		if (node == NULL) return true;
		return node->color == BLACK;
	}
	bool is_red(const Nodeptr node) {
		return node && node->color == RED;
	}

// recolor and rotate 
private:
	void update_moms_kids(Nodeptr node, Nodeptr newNode) {
		if (is_nil(node->mom))
			root = newNode;
		else if (is_left_child(node))
			node->mom->left = newNode;
		else node->mom->right = newNode;
	}

	void rotate_right(Nodeptr node) {
		Nodeptr origLeft = node->left;
		node->left = origLeft->right;
		if (!is_nil(node->left))
			node->left->mom = node;
		origLeft->right = node;
		origLeft->mom = node->mom;
		update_moms_kids(node, origLeft);
		node->mom = origLeft;
	}

	void rotate_left(Nodeptr node) {
		Nodeptr origRight = node->right;
		node->right = origRight->left;
		if (!is_nil(node->right))
			node->right->mom = node;
		origRight->left = node;
		origRight->mom = node->mom;
		update_moms_kids(node, origRight);
		node->mom = origRight;
	}

	void handle_left_situations(Nodeptr node, Nodeptr mom, Nodeptr grandma) {
		if (is_right_child(node))
			rotate_left(mom);
		flip_color(mom), flip_color(grandma);
		rotate_right(grandma);
		recolor_and_rotate(is_left_child(node) ? mom : grandma);
	}

	void handle_right_situations(Nodeptr node, Nodeptr mom, Nodeptr grandma) {
		if (is_left_child(node))
			rotate_right(mom);
		flip_color(mom), flip_color(grandma);
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

// insert 
private:
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

// erase 
private:
	void left_erase(Nodeptr node, Nodeptr mom, Nodeptr sister) {
		int kids_count = count_kids(node);
		if (is_red(node) || (is_black(node) && kids_count > 0)) {
			if (kids_count == 2) {
				Nodeptr pred = predecessor(node);
				node->key = pred->key; // TODO: relink instead
				return erase(pred);
			} else if (kids_count == 1) {
				mom->left = node->left ? node->left : node->right;
				if (node->color == BLACK)
					mom->left->color = BLACK;
			} else mom->left = NULL;
			return delete node;
		} else if (sister) {
			if (is_red(sister)) { // case 2.3
				sister->color = BLACK; // order might be messed up
				mom->color = RED;
				rotate_right(sister);
				erase(node);
			}
			else if (is_black(sister)) {
				Nodeptr red_niece = get_red_niece(sister);
				if (red_niece != NULL) { // case 2.1
					rotate_right(sister);
					sister->color = mom->color;
					red_niece->color = mom->color = BLACK; // and delete ???
				} else { // case 2.2
					node->color = sister->color = BLACK;
					if (mom->color == RED) mom->color = BLACK;
					else if (mom != root) erase(mom);
				}
			}
		}
	}

	void right_erase(Nodeptr node) {
	}

public:
	void erase(Nodeptr node) {
		if (is_left_child(node))
			;
		else ;
	}
	void erase(const value_type& data) {
		Nodeptr node = find(data);
		if (node != NULL) erase(node);
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

// test 1 
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
	cout << t.find(19)->key << endl;
	RBNode<int>* found = t.find(2);
	if (found != NULL) {
		RBNode<int>* succ = t.successor(found);
		if (succ) cout << succ->key << endl;
		else cout << "no succ\n";
		RBNode<int>* pred = t.predecessor(found);
		if (pred) cout << pred->key << endl;
		else cout << "no pred\n";
	}
	else cout << "not found\n";
}

void test2() {
	RBTree<string> t;
	t.insert("wow");
	print(t);
	t.insert("holy shit");
}

int main() {
	test2();
}
