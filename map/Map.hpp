#pragma  once
#include <stdexcept>
#include "../rbtree/RBTree.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>,
	 class Allocator = std::allocator<ft::pair<const Key, T> >
> class map {
public:
// member types definitions 
	typedef Key					key_type;
	typedef T					mapped_type;
	typedef ft::pair<const Key, T>			value_type;
	typedef std::size_t				size_type;
	typedef std::ptrdiff_t				difference_type;
	typedef Compare					key_compare;
	typedef Allocator				allocator_type;
	typedef value_type&				reference;
	typedef const value_type&			const_reference;
	typedef typename Allocator::pointer		pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef tree_iterator<value_type>		iterator;
	typedef tree_iterator<const value_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

// comparison functor 
	class value_compare {
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
		protected:
			key_compare comp;
		public:
			value_compare(Compare c): comp(c) {}
			bool operator () (const value_type& lhs, const value_type& rhs) const {
				return comp(lhs.first, rhs.first);
			}
	};

private:
// underlying red-black tree data structure && comparison functor 
	RBTree<value_type, value_compare, allocator_type>	tree;
	value_compare						comp;
	mapped_type						default_value;

public:
// ctors, dtor 
	map(): // {
		tree(comp, Allocator()),
		comp(Compare()), default_value(mapped_type()) {
	}
	explicit map(const Compare& _comp, const Allocator& alloc = Allocator()):
		tree(_comp, alloc),
		comp(_comp), default_value(mapped_type()) {
	}
	template <typename InputIt>
	map(InputIt first, InputIt last,
	    const Compare& _comp = Compare(),
	    const Allocator& alloc = Allocator()):
		tree(_comp, alloc),
		comp(_comp), default_value(mapped_type()) {
		for (; first != last; ++first)
			tree.insert(*first);
	}
	map(const map& other): // {
		tree(other.tree),
		comp(other.comp),
		default_value(mapped_type()) {
	}
	~map() {}

// operator = 
	map& operator = (const map& other) {
		if (this == &other) return *this;
		tree = other.tree;
		comp = other.comp;
		default_value = other.default_value;
		return *this;
	}

// find 
	iterator find(const Key& key) {
		return tree.find(ft::make_pair(key, default_value));
	}
	const_iterator find(const Key& key) const {
		return tree.find(ft::make_pair(key, default_value));
	}

// insert 
	ft::pair<iterator, bool> insert(const value_type& value) {
		return tree.insert(value);
	}
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {
		tree.insert(first, last);
	}
	iterator insert(iterator hint, const value_type& value) {
		return tree.insert(hint, value);
	}

// erase 
	size_type erase(const Key& key) {
		return tree.erase(ft::make_pair(key, default_value));
	}
	void erase(iterator pos) {
		tree.erase(pos);
	}
	template <typename InputIt>
	void erase(InputIt first, InputIt last) {
		tree.erase(first, last);
	}

// [] 
	T& operator [] (const Key& key) {
		return insert(ft::make_pair(key, T())).first->second;
	}

// at 
	T& at(const Key& key) {
		iterator f = find(key);
		if (f == end())
			throw std::out_of_range("no map element at given key");
		return f->second;
	}

// count 
	size_type count(const Key& key) const {
		return tree.find(ft::make_pair(key, default_value)) != tree.end();
	}

// clear 
	void clear() { tree.clear(); }

// lower bound 
	iterator lower_bound(const Key& key) {
		return tree.lower_bound(ft::make_pair(key, default_value));
	}
	const_iterator lower_bound(const Key& key) const {
		return tree.lower_bound(ft::make_pair(key, default_value));
	}

// upper bound
	iterator upper_bound(const Key& key) {
		return tree.upper_bound(ft::make_pair(key, default_value));
	}
	const_iterator upper_bound(const Key& key) const {
		return tree.upper_bound(ft::make_pair(key, default_value));
	}

// equal range 
	ft::pair<iterator, iterator> equal_range(const Key& key) {
		return tree.equal_range(ft::make_pair(key, default_value));
	}
	ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
		return tree.equal_range(ft::make_pair(key, default_value));
	}

// begin, rbegin 
	iterator begin() { return tree.begin(); }
	const_iterator begin() const { return tree.begin(); }
	reverse_iterator rbegin() { return tree.rbegin(); }
	const_reverse_iterator rbegin() const { return tree.rbegin(); }

// end, rend 
	iterator end() { return tree.end(); }
	const_iterator end() const { return tree.end(); }
	reverse_iterator rend() { return tree.rend(); }
	const_reverse_iterator rend() const { return tree.rend(); }

// size 
	size_type size() const { return tree.size(); }

// empty 
	bool empty() const { return tree.empty(); }

// swap 
	void swap(map& other) {
		tree.swap(other.tree);
		std::swap(comp, other.comp);
	}

// max size 
	size_type max_size() const { return tree.max_size(); }

// get allocator 
	allocator_type get_allocator() const { return allocator_type(); }

// key compare, value compare 
	key_compare key_comp() const { return key_compare(); }
	value_compare value_comp() const { return comp; }

// friend operators for private tree access 
	template <class K, class Tp, class C, class A>
	friend bool operator ==
	(const ft::map<K,Tp,C,A>& lhs, const ft::map<K,Tp,C,A>& rhs);
	template <class K, class Tp, class C, class A>
	friend bool operator <
	(const ft::map<K,Tp,C,A>& lhs, const ft::map<K,Tp,C,A>& rhs);

};

// map comparison 
template <class Key, class T, class Compare, class Alloc>
bool operator == (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return lhs.tree == rhs.tree;
}
template <class Key, class T, class Compare, class Alloc>
bool operator != (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator < (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return lhs.tree < rhs.tree;
}
template <class Key, class T, class Compare, class Alloc>
bool operator > (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return rhs < lhs;
}
template <class Key, class T, class Compare, class Alloc>
bool operator <= (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(rhs < lhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator >= (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs < rhs);
}

// swap 
template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
	lhs.swap(rhs);
}

} // ! namespace ft
