#pragma once

namespace ft {

// equal 
template <typename InpIt1, typename InpIt2>
bool equal(InpIt1 first1, InpIt2 last1, InpIt2 first2) {
	for ( ; first1 != last1; ++first1, ++first2)
		if (*first1 != *first2) return false;
	return true;
}

template <typename InpIt1, typename InpIt2, class BinaryPred>
bool equal(InpIt1 first1, InpIt2 last1, InpIt2 first2, BinaryPred comp) {
	for ( ; first1 != last1; ++first1, ++first2)
		if (!comp(*first1, *first2)) return false;
	return true;
}

// lexicographical compare 
template <typename InpIt1, typename InpIt2>
bool lexicographical_compare(InpIt1 first1, InpIt1 last1,
			     InpIt2 first2, InpIt2 last2) {
	for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return first1 == last1 && first2 != last2;
}

template <typename InpIt1, typename InpIt2, typename Compare>
bool lexicographical_compare(InpIt1 first1, InpIt1 last1,
			     InpIt2 first2, InpIt2 last2,
			     Compare is_less) {
	for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (is_less(*first1, *first2)) return true;
		if (is_less(*first2, *first1)) return false;
	}
	return first1 == last1 && first2 != last2;
}

} // ! namespace ft
