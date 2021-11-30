#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include "../Iterators/RandomAccessIterator.hpp"

namespace ft
{
	template <class T>
	struct is_integral { const static bool value = false; };
	template<>
	struct is_integral<bool> { const static bool value = true; };
	template<>
	struct is_integral<char> { const static bool value = true; };
	template<>
	struct is_integral<wchar_t> { const static bool value = true; };
	template<>
	struct is_integral<signed char> { const static bool value = true; };
	template<>
	struct is_integral<short int> { const static bool value = true; };
	template<>
	struct is_integral<int> { const static bool value = true; };
	template<>
	struct is_integral<long int> { const static bool value = true; };
	template<>
	struct is_integral<long long int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned char> { const static bool value = true; };
	template<>
	struct is_integral<unsigned short int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned long int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned long long int> { const static bool value = true; };

	template<typename Iterator>
	ptrdiff_t distance(Iterator first, Iterator last)
	{
		ptrdiff_t dist = 0;
		while (first != last)
		{
			dist++;
			first++;
		}
		return dist;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) 
				return false;
			else if (*first1<*first2) 
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
 	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1)) 
				return false;
			else if (comp(*first2, *first1)) 
				return true;
			++first1; ++first2;
		}
		return (true);
	}

	template <class Iterator1, class Iterator2>
	bool equal(Iterator1 first1, Iterator1 last1, Iterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
	
	template <class T>
	bool lessthan(T a, T b)
	{
		if (a <= b)
			return true;
		return false;
	}

	template <class T>
	bool more(T a, T b)
	{
		if (a > b)
			return true;
		return false;
	}

	template <class T>
	bool morethan(T a, T b)
	{
		if (a >= b)
			return true;
		return false;
	}
}

#endif