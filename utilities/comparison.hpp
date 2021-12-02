#pragma once

namespace ft {

// ft::equal 
template <typename InpIt1, typename InpIt2>
bool equal(InpIt1 first1, InpIt2 last1, InpIt2 first2) {
	for ( ; first1 < last1; ++first1, ++first2)
		if (*first1 != *first2) return false;
	return true;
}

template <typename typeL, typename typeR>
static bool __predicate(const typeL& lhs, const typeR& rhs) {
	return lhs == rhs;
}

template <typename InpIt1, typename InpIt2, class BiPred>
bool equal(InpIt1 first1, InpIt2 last1, InpIt2 first2, BiPred pred = __predicate) {
	for ( ; first1 < last1; ++first1, ++first2)
		if (pred(*first1, *first2) == false) return false;
	return true;
}

// ft::lexicographical_compare 
template <typename InpIt1, typename InpIt2>
bool lexicographical_compare(InpIt1 first1, InpIt1 last1,
			     InpIt2 first2, InpIt2 last2) {
	for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return first1 == last1 && first2 != last2;
}

template <typename typeL, typename typeR>
static bool __is_less(const typeL& lhs, const typeR& rhs) {
	return lhs < rhs;
}

template <typename InpIt1, typename InpIt2, class Compare>
bool lexicographical_compare(InpIt1 first1, InpIt1 last1,
			     InpIt2 first2, InpIt2 last2,
			     Compare is_less = __is_less) {
	for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (is_less(*first1, *first2)) return true;
		if (is_less(*first2, *first1)) return false;
	}
	return first1 == last1 && first2 != last2;
}

} // ! namespace ft
