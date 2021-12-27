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

class failedTest :  public std::exception {};

template< typename K, typename T, typename Compare, typename Alloc>
void
putMap( ft::Map<K, T, Compare, Alloc> const & container, int errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ FT::map ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of map ]" << RESET_COLOR << " -> ";
	std::cout << container.size() << std::endl;
	typename ft::Map<K, T, Compare, Alloc>::const_iterator it = container.begin();
	typename ft::Map<K, T, Compare, Alloc>::const_iterator ite = container.end();

	int	printMax;

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

template< typename K, typename T, typename Compare, typename Alloc>
void
putMap( std::map<K, T, Compare, Alloc> const & container, int errorPos = -1 )	{

	std::cout << PRINT_STD_TITLE << "[ STD::map ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_STD_TITLE << "[ size of map ]" << RESET_COLOR << " -> ";
	std::cout << container.size() << std::endl;
	typename std::map<K, T, Compare, Alloc>::const_iterator it = container.begin();
	typename std::map<K, T, Compare, Alloc>::const_iterator ite = container.end();

	int	printMax;

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


template<	class K,
			class T
			>
void
testMap( ft::Map<K, T> const & ft_c, std::map<K, T> const &std_c,
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
		typename ft::Map<K, T>::const_iterator	ft_it = ft_c.begin();
		typename ft::Map<K, T>::const_iterator	ft_ite = ft_c.end();

		typename std::map<K, T>::const_iterator	std_it = std_c.begin();
		typename std::map<K, T>::const_iterator	std_ite = std_c.end();
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

bool	testBool(bool b, const char * file, int const lineNo, int const loopIter )	{
	if (b == true)
		std::cout << "[ TEST PASSED: no diff ] \t \342\234\205" << std::endl;
	else	{
		std::cout << ERROR_TITLE << "[ FAILURE at " << file << ":" << lineNo << "]" << RESET_COLOR << BLINK << " \t \342\235\214" << RESET_COLOR << std::endl;
		if (loopIter != -1)
			std::cout << ERROR_TITLE << " loop iteration = " << loopIter << "." << RESET_COLOR << " \t \342\235\214" << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
	}
	return (b);
}

int	main_tester_map( void );
int	test_map_instantiation( void );
int	test_map_insert_erase( void );
int	test_key_compare_value_compare();

int	test_map_push_back_pop_back( void );
int	test_map_clear( void );
int	test_map_find( void );
int	test_map_count( void );
int	test_map_lower_bound( void );
int	test_map_upper_bound( void );
int	test_map_equal_range( void );

int	test_map_capacities( void );
int	test_map_operatorEqual( void );
int	test_map_resize( void );
int	test_map_assign( void );
int	test_map_at_operatorBrackets( void );
int	test_map_member_swap( void );
int	test_map_swap( void );
int	test_map_relational_operators( void );
int	test_map_splice( void );
int	test_map_remove_if( void );
int	test_map_remove( void );
int	test_map_unique( void );
int	test_map_merge( void );
int	test_map_sort( void );
int	test_map_iterator( void );
int	test_map_reverseIterator( void );
int	test_map_reverse( void );
int	test_map_element_access( void );

void
test_map_const_equal_range(int findKey, std::map<int, exampleClass> const std_c0, ft::Map<int, exampleClass> const ft_c0)	{

		std::cout << HEADER_TITLE << "[ Test equal_range with a value added previously to the map ]" << RESET_COLOR << std::endl;
		std::pair< std::map<int, exampleClass>::const_iterator, std::map<int, exampleClass>::const_iterator>	std_c0_ret = std_c0.equal_range(findKey);
		ft::pair< ft::Map<int, exampleClass>::const_iterator, ft::Map<int, exampleClass>::const_iterator>		ft_c0_ret = ft_c0.equal_range(findKey);

		if (std_c0_ret.first == std_c0.end())
			testBool(ft_c0_ret.first == ft_c0.end(), "", 0,0);
		if (std_c0_ret.second == std_c0.end())
			testBool(ft_c0_ret.second == ft_c0.end(), "", 0,0);
		if (ft_c0_ret.first != ft_c0.end())
			testBool(ft_c0_ret.first->first == std_c0_ret.first->first
				&& ft_c0_ret.first->second == std_c0_ret.first->second, "", 0,0);
		if (ft_c0_ret.second != ft_c0.end())
			testBool(ft_c0_ret.second->first == std_c0_ret.second->first
				&& ft_c0_ret.second->second == std_c0_ret.second->second, "", 0,0);
}

int
test_map_equal_range( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		size_t			valgrind_factor = (VALGRIND_MODE == true) ? 100 : 1;
		size_t			testSize = 5000 / valgrind_factor;
		int findKey = 42;
		std::cout << HEADER_TITLE << "[ Test equal_range function with map of " << testSize << " int key and exampleClass mapped value ]" << RESET_COLOR << std::endl;

		std::vector<ft::pair<int, exampleClass> >	ft_val_0(testSize);
		std::vector<std::pair<int, exampleClass> >	std_val_0(testSize);
		srand(time(NULL));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % testSize;
			if (i == testSize / 2)
				findKey = val;
			ft_val_0[i] = ft::make_pair(val, exampleClass(i));
			std_val_0[i] = std::make_pair(val, i);
		}

		std::map<int, exampleClass>	std_c0(std_val_0.begin(), std_val_0.end());
		ft::Map<int, exampleClass>	ft_c0(ft_val_0.begin(), ft_val_0.end());
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << HEADER_TITLE << "[ Test equal_range with a value added previously to the map ]" << RESET_COLOR << std::endl;
		std::pair< std::map<int, exampleClass>::iterator, std::map<int, exampleClass>::iterator>	std_c0_ret = std_c0.equal_range(findKey);
		ft::pair< ft::Map<int, exampleClass>::iterator, ft::Map<int, exampleClass>::iterator>		ft_c0_ret = ft_c0.equal_range(findKey);

		if (std_c0_ret.first == std_c0.end())
			testBool(ft_c0_ret.first == ft_c0.end(), "", 0,0);
		if (std_c0_ret.second == std_c0.end())
			testBool(ft_c0_ret.second == ft_c0.end(), "", 0,0);
		if (ft_c0_ret.first != ft_c0.end())
			testBool(ft_c0_ret.first->first == std_c0_ret.first->first
				&& ft_c0_ret.first->second == std_c0_ret.first->second, "", 0,0);
		if (ft_c0_ret.second != ft_c0.end())
			testBool(ft_c0_ret.second->first == std_c0_ret.second->first
				&& ft_c0_ret.second->second == std_c0_ret.second->second, "", 0,0);

		test_map_const_equal_range(findKey, std_c0, ft_c0);

		std::cout << HEADER_TITLE << "[ Test equal_range with a value absent from the map (higher than the highest key)]" << RESET_COLOR << std::endl;
		std_c0_ret = std_c0.equal_range(testSize * 2);
		ft_c0_ret = ft_c0.equal_range(testSize * 2);

		if (std_c0_ret.first == std_c0.end())
			testBool(ft_c0_ret.first == ft_c0.end(), "", 0,0);
		if (std_c0_ret.second == std_c0.end())
			testBool(ft_c0_ret.second == ft_c0.end(), "", 0,0);
		if (ft_c0_ret.first != ft_c0.end())
			testBool(ft_c0_ret.first->first == std_c0_ret.first->first
				&& ft_c0_ret.first->second == std_c0_ret.first->second, "", 0,0);
		if (ft_c0_ret.second != ft_c0.end())
			testBool(ft_c0_ret.second->first == std_c0_ret.second->first
				&& ft_c0_ret.second->second == std_c0_ret.second->second, "", 0,0);

		std::cout << HEADER_TITLE << "[ Test equal_range with a value absent from the map (lower than the lowest key)]" << RESET_COLOR << std::endl;
		std_c0_ret = std_c0.equal_range(-42);
		ft_c0_ret = ft_c0.equal_range(-42);

		if (std_c0_ret.first == std_c0.end())
			testBool(ft_c0_ret.first == ft_c0.end(), "", 0,0);
		if (std_c0_ret.second == std_c0.end())
			testBool(ft_c0_ret.second == ft_c0.end(), "", 0,0);
		if (ft_c0_ret.first != ft_c0.end())
			testBool(ft_c0_ret.first->first == std_c0_ret.first->first
				&& ft_c0_ret.first->second == std_c0_ret.first->second, "", 0,0);
		if (ft_c0_ret.second != ft_c0.end())
			testBool(ft_c0_ret.second->first == std_c0_ret.second->first
				&& ft_c0_ret.second->second == std_c0_ret.second->second, "", 0,0);

		std::cout << HEADER_TITLE << "[ Test equal_range with empty map ]" << RESET_COLOR << std::endl;
		ft_c0.clear();
		std_c0.clear();
		testMap(ft_c0, std_c0, NOPRINT);

		std_c0_ret = std_c0.equal_range(42);
		ft_c0_ret = ft_c0.equal_range(42);

		if (std_c0_ret.first == std_c0.end())
			testBool(ft_c0_ret.first == ft_c0.end(), "", 0,0);
		if (std_c0_ret.second == std_c0.end())
			testBool(ft_c0_ret.second == ft_c0.end(), "", 0,0);
		if (ft_c0_ret.first != ft_c0.end())
			testBool(ft_c0_ret.first->first == std_c0_ret.first->first
				&& ft_c0_ret.first->second == std_c0_ret.first->second, "", 0,0);
		if (ft_c0_ret.second != ft_c0.end())
			testBool(ft_c0_ret.second->first == std_c0_ret.second->first
				&& ft_c0_ret.second->second == std_c0_ret.second->second, "", 0,0);
	}
	return (0);
}

int main()
{
	test_map_equal_range();
}