#include <vector>
#include <stack>
#include <map>
#include "vector/vector.hpp"
#include "stack/stack.hpp"
#include "map/node.hpp"
#include "map/RBTree.hpp"
#include "map/pair.hpp"
#include "map/map.hpp"
#include <deque>
#include <list>
#include <math.h>
#include <algorithm>
#include "exampleClass.hpp"
#include "compClass.hpp"
#include "map/bvaletteTester_defines.hpp"

#define NOPRINT ""

class failedTest : public std::exception
{
};

template <typename K, typename T, typename Compare, typename Alloc>
void putMap(ft::Map<K, T, Compare, Alloc> const &container, int errorPos = -1)
{

	std::cout << PRINT_TITLE << "[ FT::map ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of map ]" << RESET_COLOR << " -> ";
	std::cout << container.size() << std::endl;
	typename ft::Map<K, T, Compare, Alloc>::const_iterator it = container.begin();
	typename ft::Map<K, T, Compare, Alloc>::const_iterator ite = container.end();

	int printMax;

	if (container.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(container.size());
	for (int i = 0; container.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(container.size()))
			std::cout << ERROR_SOURCE << "ft: [" << i << "] " << RESET_COLOR << it->first << "; " << it->second << " -> " << &(*it) << std::endl;
		else
			std::cout << "ft: [" << i << "] " << it->first << "; " << it->second << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(container.size()))
		std::cout << " !!\t map size is too large to print... stoping here." << std::endl;
}

template <typename K, typename T, typename Compare, typename Alloc>
void putMap(std::map<K, T, Compare, Alloc> const &container, int errorPos = -1)
{

	std::cout << PRINT_STD_TITLE << "[ STD::map ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_STD_TITLE << "[ size of map ]" << RESET_COLOR << " -> ";
	std::cout << container.size() << std::endl;
	typename std::map<K, T, Compare, Alloc>::const_iterator it = container.begin();
	typename std::map<K, T, Compare, Alloc>::const_iterator ite = container.end();

	int printMax;

	if (container.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(container.size());
	for (int i = 0; container.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(container.size()))
			std::cout << ERROR_SOURCE << "std: [" << i << "] " << RESET_COLOR << it->first << "; " << it->second << " -> " << &(*it) << std::endl;
		else
			std::cout << "std: [" << i << "] " << it->first << "; " << it->second << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(container.size()))
		std::cout << " !!\t map size is too large to print... stoping here." << std::endl;
}

template <class K,
		  class T>
void testMap(ft::Map<K, T> const &ft_c, std::map<K, T> const &std_c,
			 bool print, std::string message = "")
{

	bool success = true;

	if (message.empty() == false)
		std::cout << SUBTITLE << message << RESET_COLOR << std::endl;

	if (print == true)
	{
		putMap<K, T>(ft_c);
		putMap<K, T>(std_c);
	}

	if (ft_c.size() != std_c.size())
	{
		if (print == false && success == true)
		{
			putMap<K, T>(ft_c);
			putMap<K, T>(std_c);
		}
		std::cout << TITLE << "size: ft (" << ft_c.size() << ") std (" << std_c.size() << ") Diff ! " << RESET_COLOR << std::endl;
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
		else
			success = false;
	}

	if (ft_c.size() > 0)
	{
		int i = 0;
		typename ft::Map<K, T>::const_iterator ft_it = ft_c.begin();
		typename ft::Map<K, T>::const_iterator ft_ite = ft_c.end();

		typename std::map<K, T>::const_iterator std_it = std_c.begin();
		typename std::map<K, T>::const_iterator std_ite = std_c.end();
		while (ft_it != ft_ite && std_it != std_ite)
		{

			if (ft_it->first != std_it->first || ft_it->second != std_it->second)
			{
				putMap<K, T>(ft_c, i);
				putMap<K, T>(std_c, i);
				std::cout << TITLE << "iterator at pos " << i << ": ft (" << ft_it->first << "; " << ft_it->second << ") ";
				std::cout << " / std (" << std_it->first << "; " << std_it->second << ") Diff ! " << RESET_COLOR << std::endl;
				std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
				if (DEBUG_MODE < 1)
					throw failedTest();
				else
					success = false;
			}
			i++;
			ft_it++;
			std_it++;
		}
		if (ft_it != ft_ite || std_it != std_ite)
		{
			if (print == false && success == true)
			{
				putMap<K, T>(ft_c);
				putMap<K, T>(std_c);
			}
			std::cout << TITLE << "Diff in map after iterating thought it." << RESET_COLOR << std::endl;
			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
			if (DEBUG_MODE < 1)
				throw failedTest();
			else
				success = false;
		}
	}

	if (print == true && success == true)
		std::cout << TESTOK_TITLE << "[ TEST PASSED: no diff ] map size: ft(" << ft_c.size() << ") std(" << std_c.size() << ")" << RESET_COLOR << "\t  \342\234\205" << std::endl;
	else if (success == true)
		std::cout << "[ TEST PASSED: no diff ] map size: ft(" << ft_c.size() << ") std(" << std_c.size() << ") \t \342\234\205" << std::endl;
	else
		std::cout << ERROR_TITLE << "TEST FAILED !" << RESET_COLOR << std::endl;
}

bool testBool(bool b, const char *file, int const lineNo, int const loopIter)
{
	if (b == true)
		std::cout << "[ TEST PASSED: no diff ] \t \342\234\205" << std::endl;
	else
	{
		std::cout << ERROR_TITLE << "[ FAILURE at " << file << ":" << lineNo << "]" << RESET_COLOR << BLINK << " \t \342\235\214" << RESET_COLOR << std::endl;
		if (loopIter != -1)
			std::cout << ERROR_TITLE << " loop iteration = " << loopIter << "." << RESET_COLOR << " \t \342\235\214" << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
	}
	return (b);
}

template<	class K,
			class T,
			class Compare = std::less<K>,
			class ftAlloc = std::allocator<ft::pair<const K, T> >,
			class stdAlloc = std::allocator<std::pair<const K, T> > >
void
testMap( ft::Map<K, T, Compare, ftAlloc> const & ft_c, std::map<K, T, Compare, stdAlloc> const &std_c,
bool print, std::string message = "" )	{

	bool	success = true;

	if (message.empty() == false)
		std::cout << SUBTITLE << message << RESET_COLOR << std::endl;

	if (print == true)
	{
		putMap<K, T>(ft_c);
		putMap<K, T>(std_c);
	}

	if(ft_c.size() != std_c.size())	{
		if (print == false && success == true)
		{
			putMap<K, T>(ft_c);
			putMap<K, T>(std_c);
		}
		std::cout << TITLE <<"size: ft (" << ft_c.size() << ") std (" << std_c.size() << ") Diff ! " << RESET_COLOR << std::endl;
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
		else
			success = false;
	}

	if (ft_c.size() > 0)
	{
		int i = 0;
		typename ft::Map<K, T, Compare, ftAlloc>::const_iterator	ft_it = ft_c.begin();
		typename ft::Map<K, T, Compare, ftAlloc>::const_iterator	ft_ite = ft_c.end();

		typename std::map<K, T, Compare, stdAlloc>::const_iterator	std_it = std_c.begin();
		typename std::map<K, T, Compare, stdAlloc>::const_iterator	std_ite = std_c.end();
		while (ft_it != ft_ite && std_it != std_ite)	{

			if(ft_it->first != std_it->first || ft_it->second != std_it->second)	{
				putMap<K, T>(ft_c, i);
				putMap<K, T>(std_c, i);
				std::cout << TITLE <<"iterator at pos " << i << ": ft (" << ft_it->first << "; " << ft_it->second << ") ";
				std::cout << " / std (" << std_it->first << "; " << std_it->second << ") Diff ! " << RESET_COLOR << std::endl;
				std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
				if (DEBUG_MODE < 1)
					throw failedTest();
				else
					success = false;
			}
			i++;
			ft_it++;
			std_it++;
		}
		if (ft_it != ft_ite || std_it != std_ite)	{
			if (print == false && success == true)
			{
				putMap<K, T>(ft_c);
				putMap<K, T>(std_c);
			}
			std::cout << TITLE <<"Diff in map after iterating thought it." << RESET_COLOR << std::endl;
			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
			if (DEBUG_MODE < 1)
				throw failedTest();
			else
				success = false;
		}
	}

	if (print == true && success == true)
		std::cout << TESTOK_TITLE << "[ TEST PASSED: no diff ] map size: ft(" << ft_c.size() << ") std(" << std_c.size() << ")" << RESET_COLOR << "\t  \342\234\205" << std::endl;
	else if (success == true)
		std::cout << "[ TEST PASSED: no diff ] map size: ft(" << ft_c.size() << ") std(" << std_c.size() << ") \t \342\234\205" << std::endl;
	else
		std::cout << ERROR_TITLE << "TEST FAILED !" << RESET_COLOR << std::endl;
}

int main_tester_map(void);
int test_map_instantiation(void);
int test_map_insert_erase(void);
int test_key_compare_value_compare();

int test_map_push_back_pop_back(void);
int test_map_clear(void);
int test_map_find(void);
int test_map_count(void);
int test_map_lower_bound(void);
int test_map_upper_bound(void);
int test_map_equal_range(void);

int test_map_capacities(void);
int test_map_operatorEqual(void);
int test_map_resize(void);
int test_map_assign(void);
int test_map_at_operatorBrackets(void);
int test_map_member_swap(void);
int test_map_swap(void);
int test_map_relational_operators(void);
int test_map_splice(void);
int test_map_remove_if(void);
int test_map_remove(void);
int test_map_unique(void);
int test_map_merge(void);
int test_map_sort(void);
int test_map_iterator(void);
int test_map_reverseIterator(void);
int test_map_reverse(void);
int test_map_element_access(void);


template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };

		void m(void) 		{ std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const	{ std::cout << "foo::m const called [" << this->value << "]" << std::endl; };

		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};

		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}

	private:
		value_type	value;
		bool		_verbose;

};

template <typename T>
class bar {
	public:

		bar(void) {};
		~bar(void) {};

	private:
		T			value;
		bool		_verbose;

};

template < typename T, typename U>
void
test_max_size()	{
	size_t std_c0 = std::map<const T, U>().max_size();
	size_t ft_c0 = ft::Map<const T, U>().max_size();
	std::cout << "Sizes returned : ft("<< ft_c0 <<") std("<< std_c0 <<")" << RESET_COLOR << std::endl;
	try {
		testBool(std_c0 == ft_c0, "", 0, 0);
	}
	catch (failedTest &e) {
		std::cout << ERROR_TITLE << "Sizes returned : ft("<< ft_c0/100000000000000 <<"...) std("<< std_c0/100000000000000 <<"...)" << RESET_COLOR << std::endl;
		throw failedTest();
	}
}

int
test_map_capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 5;

		std::cout << HEADER_TITLE << "[ Empty / size on empty map ]" << RESET_COLOR << std::endl;
		std::map<int, int>		std_c0;
		ft::Map<int, int>		ft_c0;
		testBool(std_c0.empty() == ft_c0.empty(), "", 0, 0);
		testBool(std_c0.size() == ft_c0.size(), "", 0, 0);

		std::cout << HEADER_TITLE << "[ Empty / size on non empty map ]" << RESET_COLOR << std::endl;
		for(int i = 0; i < static_cast<int>(testSize); i++)	{
			std_c0[i] = 1;
			ft_c0[i] = 1;
			testBool(std_c0.empty() == ft_c0.empty(), "", 0, 0);
			testBool(std_c0.size() == ft_c0.size(), "", 0, 0);
		}
	}
	std::cout << HEADER_TITLE << "[ Max Size with various types ]" << RESET_COLOR << std::endl;
	int error_line = __LINE__;
	std::cout << "Test <int, bar<bool> >		: " ;			test_max_size<int, bar<bool> >(); error_line = __LINE__ + 1;
	std::cout << "Test <int, bar<double> >		: " ;			test_max_size<int, bar<double> >(); error_line = __LINE__ + 1;
	std::cout << "Test <bar<unsigned int>, int >		: " ;			test_max_size<bar<unsigned int>, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <bar<int>, int >		: " ;			test_max_size<bar<int>, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, bar<int> >		: " ;			test_max_size<int, bar<int> >(); error_line = __LINE__ + 1;
	std::cout << "Test <int, foo<bool> >		: " ;			test_max_size<int, foo<bool> >(); error_line = __LINE__ + 1;
	std::cout << "Test <int, foo<double> >		: " ;			test_max_size<int, foo<double> >(); error_line = __LINE__ + 1;
	std::cout << "Test <int, foo<int> >		: " ;			test_max_size<int, foo<int> >(); error_line = __LINE__ + 1;
	std::cout << "Test <int, double>		: " ;			test_max_size<int, long>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, int>			: " ;			test_max_size<int, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <float, float>		: " ;			test_max_size<float, float>(); error_line = __LINE__ + 1;
	std::cout << "Test <double, double>		: " ;			test_max_size<double, double>(); error_line = __LINE__ + 1;
	std::cout << "Test <std::string, std::string>		: " ;	test_max_size<std::string, std::string>(); error_line = __LINE__ + 1;
	std::cout << "Test <exampleClass, exampleClass>	: " ;		test_max_size<exampleClass, exampleClass>(); error_line = __LINE__ + 1;
	std::cout << "Test <bool, int>		: " ;				test_max_size<bool, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <short, int>		: " ;				test_max_size<short, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <char, int>		: " ;				test_max_size<char, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, int>		: " ;				test_max_size<int, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <float, int>		: " ;				test_max_size<float, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <double, int>	: " ;				test_max_size<double, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <std::string, int>	: " ;		test_max_size<std::string, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <exampleClass, int>	: " ;		test_max_size<exampleClass, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, bool>			: " ;				test_max_size<int, bool>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, short>			: " ;				test_max_size<int, short>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, char>			: " ;				test_max_size<int, char>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, int>			: " ;				test_max_size<int, int>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, float>			: " ;				test_max_size<int, float>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, double>		: " ;				test_max_size<int, double>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, std::string>	: " ;		test_max_size<int, std::string>(); error_line = __LINE__ + 1;
	std::cout << "Test <int, exampleClass>	: " ;		test_max_size<int, exampleClass>(); error_line = __LINE__ + 1;

	return (0);
}

int main()
{
	test_map_capacities();
	return 0;
}
