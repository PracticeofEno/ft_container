#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <uchar.h>
/////   max_szie() util    ////////////////
template <int>
size_t CatchOS();

template <>
size_t CatchOS<4>()
{
	return 32;
}

template <>
size_t CatchOS<8>()
{
	return 64;
}
////////////////////////////////////////

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
		ptrdiff_t dist;
		while (first != last)
		{
			dist++;
			first++;
		}
		return dist;
	}


}

#endif