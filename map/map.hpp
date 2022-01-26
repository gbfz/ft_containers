#pragma  once
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <limits>
// TODO: normal includes
#include "rbtree.hpp"
#include "../utilities/pair.hpp"
#include "../utilities/comparison.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>,
	 class Allocator = std::allocator<ft::pair<const Key, T> >
> class map {
public:
// member types definitions 
	typedef Key					key_type;
	typedef T					mapped_type;
	typedef ft::pair<const Key, T>			value_type;
	typedef size_t					size_type;
	typedef ptrdiff_t				difference_type;
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
				return comp(lhs.first, rhs.first);
			}
	};

private:
// underlying red-black tree data structure && comparison functor 
	RBTree<value_type, allocator_type>	tree;
	value_compare				comp;

public:
// TODO: hide 
	void print() { tree.print(); }

// ctors, dtor 
	map(): tree() {}
	explicit map(const Compare& comp, const Allocator& alloc = Allocator()):
		tree(comp, alloc) {}
	template <typename InputIt>
	map(InputIt first, InputIt last,
		const Compare& comp = Compare(),
		const Allocator& alloc = Allocator()): tree(comp, alloc) {
		for (; first != last; ++first)
			tree.insert(*first);
	}
	map(const map& other): value_compare(other.value_compare), tree(other.tree) {}
	~map() {}

// find 
	iterator find(const Key& key) {
		return tree.find(ft::make_pair(key, mapped_type()));
	}
	const_iterator find(const Key& key) const {
		return tree.find(ft::make_pair(key, mapped_type()));
	}

// insert 
	ft::pair<iterator, bool> insert(const value_type& value) {
		iterator f = find(value.first);
		if (f != end())
			return ft::make_pair(f, false);
		return tree.insert(value);
	}
	template <typename InputIt>
	void insert(InputIt first, InputIt last) {
		tree.insert(first, last);
	}

// erase 
	size_type erase(const Key& key) {
		return tree.erase(ft::make_pair(key, mapped_type()));
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
		return tree.find(ft::make_pair(key, mapped_type())) != tree.end();
	}

// clear 
	void clear() { tree.clear(); }

// lower bound 
	iterator lower_bound(const Key& key) { return tree.lower_bound(ft::make_pair(key, mapped_type())); }
	const_iterator lower_bound(const Key& key) const { return tree.lower_bound(ft::make_pair(key, mapped_type())); }

// upper bound
	iterator upper_bound(const Key& key) { return tree.upper_bound(ft::make_pair(key, mapped_type())); }
	const_iterator upper_bound(const Key& key) const { return tree.upper_bound(ft::make_pair(key, mapped_type())); }

// equal range 
	iterator equal_range(const Key& key) { return tree.equal_range(ft::make_pair(key, mapped_type())); }
	const_iterator equal_range(const Key& key) const { return tree.equal_range(ft::make_pair(key, mapped_type())); }

// begin, rbegin 
	iterator begin() { return tree.begin(); }
	const_iterator begin() const { return tree.begin(); }

// end, rend 
	iterator end() { return tree.end(); }
	const_iterator end() const { return tree.end(); }

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
	size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

// key compare, value compare 
	key_compare key_comp() const { return tree.key_comp(); }
	value_compare value_comp() const { return tree.value_comp(); }

};

// map comparison 
template <class Key, class T, class Compare, class Alloc>
bool operator == (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class Key, class T, class Compare, class Alloc>
bool operator != (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator < (const ft::map<Key, T, Compare, Alloc>& lhs,
		  const ft::map<Key, T, Compare, Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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
