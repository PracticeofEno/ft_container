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

void
testInserEraseAdvanced ( void )	{
		std::cout << HEADER_TITLE << "[ Insert with two different Compare functions]" << RESET_COLOR << std::endl;
		{
			std::map<char, int>	std_first_greater;
			std_first_greater.insert(std::pair<char, int>('a',10));
			std_first_greater.insert(std::pair<char, int>('b',30));
			std_first_greater.insert(std::pair<char, int>('c',50));
			std_first_greater.insert(std::pair<char, int>('d',70));
			ft::Map<char, int >	ft_first_greater;
			ft_first_greater.insert(ft::pair<char, int>('a',10));
			ft_first_greater.insert(ft::pair<char, int>('b',30));
			ft_first_greater.insert(ft::pair<char, int>('c',50));
			ft_first_greater.insert(ft::pair<char, int>('d',70));

			std::map<char, int>::iterator	std_it = std_first_greater.begin();
			std::map<char, int >::iterator	std_ite = std_first_greater.end();
			ft::Map<char, int >::iterator	ft_it = ft_first_greater.begin();
			ft::Map<char, int>::iterator	ft_ite = ft_first_greater.end();

			std::map<char, int>	std_c0;
			ft::Map<char, int>	ft_c0;
			std_c0.insert(std_it, std_ite);
			ft_c0.insert(ft_it, ft_ite);

			testMap<char, int >(ft_first_greater, std_first_greater, NOPRINT);
			testMap<char, int>(ft_c0, std_c0, NOPRINT);
		}
		{
			int testSize = 35000;
			int findKey = 42;
			std::cout << HEADER_TITLE << "[ Insert Range with " << testSize << " int key and int mapped value ]" << RESET_COLOR << std::endl;

			std::vector<ft::pair<int, int> >	ft_val_0(testSize);
			std::vector<std::pair<int, int> >	std_val_0(testSize);
			srand(time(NULL));
			for (int i = 0; i < testSize; i++)	{
				int val = rand() % testSize;
				if (i == testSize / 2)
					findKey = val;
				ft_val_0[i] = ft::make_pair(val, i);
				std_val_0[i] = std::make_pair(val, i);
			}

			std::map<int, int>	std_c0;
			ft::Map<int, int>	ft_c0;

			std_c0.insert(std_val_0.begin(), std_val_0.end());
			ft_c0.insert(ft_val_0.begin(), ft_val_0.end());
			testMap(ft_c0, std_c0, NOPRINT);

			std::cout << HEADER_TITLE << "[ Insert with Hint ]" << RESET_COLOR << std::endl;

			std::map<int, int>::iterator	std_it = std_c0.find(findKey);
			ft::Map<int, int>::iterator		ft_it = ft_c0.find(findKey);

			std_c0.insert(std_it, std::make_pair(testSize * 2 , 1));
			ft_c0.insert(ft_it, ft::make_pair(testSize * 2 , 1));
			testMap(ft_c0, std_c0, NOPRINT);

			std_c0.insert(std_c0.end(), std::make_pair(-42, 1));
			ft_c0.insert(ft_c0.end(), ft::make_pair(-42, 1));
			testMap(ft_c0, std_c0, NOPRINT);

			std_c0.insert(std_c0.find(-42), std::make_pair(-43, 2));
			ft_c0.insert(ft_c0.find(-42), ft::make_pair(-43, 2));
			testMap(ft_c0, std_c0, NOPRINT);
			std_c0.insert(std_c0.find(-42), std::make_pair(-41, -1));
			ft_c0.insert(ft_c0.find(-42), ft::make_pair(-41, -1));
			testMap(ft_c0, std_c0, NOPRINT);

			std_c0.insert(std_c0.find(testSize * 2), std::make_pair((testSize * 2) + 1, 2));
			ft_c0.insert(ft_c0.find(testSize * 2), ft::make_pair((testSize * 2) + 1, 2));
			testMap(ft_c0, std_c0, NOPRINT);

			std_c0.insert(std_c0.find(testSize * 2), std::make_pair((testSize * 2) - 1, -1));
			ft_c0.insert(ft_c0.find(testSize * 2), ft::make_pair((testSize * 2) - 1, -1));
			testMap(ft_c0, std_c0, NOPRINT);

			for (int i = 0; i < 10; i++)	{
				int	val_insert = rand() % testSize + 10;
				int	val_remove = std_val_0[rand() % (testSize / 2)].first;
				std::cout << HEADER_TITLE << "[Insert key: " << val_insert << " Remove key: " << val_remove << " ]" << RESET_COLOR << std::endl;

				std_it = std_c0.find(val_insert);
				ft_it = ft_c0.find(val_insert);
				if (std_it == std_c0.end())
					std::cout << TESTOK_TITLE << "[Hint position is end()]" << RESET_COLOR << std::endl;
				std_c0.insert(std_it, std::make_pair(val_insert + 1, 42));
				ft_c0.insert(ft_it, ft::make_pair(val_insert + 1, 42));
				testMap(ft_c0, std_c0, NOPRINT);
				std_it = std_c0.insert(std_it, std::make_pair(val_insert - 1, 21));
				ft_it = ft_c0.insert(ft_it, ft::make_pair(val_insert - 1, 21));

				if (std_it == std_c0.end())
					testBool(ft_it == ft_c0.end(), "", 0, 0);
				else if (testBool(ft_it != ft_c0.end(), "", 0, 0) == true)
					testBool(ft_it->first == std_it->first
						&& ft_it->second == std_it->second, "", 0, 0);
				testMap(ft_c0, std_c0, NOPRINT);
				std::cout << ft_c0.size() << " | " << std_c0.size() << std::endl;
				std_c0.erase(val_remove);
				ft_c0.erase(val_remove);
				std::cout << ft_c0.size() << " | " << std_c0.size() << std::endl;
				testMap(ft_c0, std_c0, NOPRINT);
			}
			std::cout << HEADER_TITLE << "[ Remove key 10000000 which does not exist ]" << RESET_COLOR << std::endl;
			std_c0.erase(10000000);
			ft_c0.erase(10000000);
			testMap(ft_c0, std_c0, NOPRINT);
		}
}

void
testCppRefCode( void )	{
	std::cout << HEADER_TITLE << "[ Insert with code from Cpp reference]" << RESET_COLOR << std::endl;
	std::map<char,int> std_c0;
	ft::Map<char,int> ft_c0;

	std::cout << HEADER_TITLE << "[ Insert Function ]" << RESET_COLOR << std::endl;
	// first insert function version (single parameter):
	std_c0.insert ( std::pair<char,int>('a',100) );
	std_c0.insert ( std::pair<char,int>('z',200) );
	ft_c0.insert ( ft::pair<char,int>('a',100) );
	ft_c0.insert ( ft::pair<char,int>('z',200) );

	testMap<char, int>(ft_c0, std_c0, NOPRINT);


	std::cout << HEADER_TITLE << "[ Test boolean returned in a pair in case of pre existing element ]" << RESET_COLOR << std::endl;
	std::pair<std::map<char,int>::iterator,bool> std_ret = std_c0.insert ( std::pair<char,int>('z',500) );
	ft::pair<ft::Map<char,int>::iterator,bool> ft_ret = ft_c0.insert ( ft::pair<char,int>('z',500) );
	testBool((std_ret.second == ft_ret.second), "", 0, 0);
	testMap<char, int>(ft_c0, std_c0, NOPRINT);

	std::cout << HEADER_TITLE << "[ Insert with hint ]" << RESET_COLOR << std::endl;
	// second insert function version (with hint position):
	std::map<char,int>::iterator std_it = std_c0.begin();
	ft::Map<char,int>::iterator ft_it = ft_c0.begin();
	std_c0.insert (std_it, std::pair<char,int>('b',300));  // max efficiency inserting
	std_c0.insert (std_it, std::pair<char,int>('c',400));  // no max efficiency inserting
	ft_c0.insert (ft_it, ft::pair<char,int>('b',300));  // max efficiency inserting
	ft_c0.insert (ft_it, ft::pair<char,int>('c',400));  // no max efficiency inserting
	testMap<char, int>(ft_c0, std_c0, NOPRINT);

	std::cout << HEADER_TITLE << "[ Insert with range ]" << RESET_COLOR << std::endl;
	// third insert function version (range insertion):
	std::map<char,int> std_anothermap;
	ft::Map<char,int> ft_anothermap;
	std_anothermap.insert(std_c0.begin(),std_c0.end());
	ft_anothermap.insert(ft_c0.begin(),ft_c0.end());
	testMap<char, int>(ft_anothermap, std_anothermap, NOPRINT);
}

void
testBracketsInsert( void )	{

	{
		std::cout << HEADER_TITLE << "[ Insert with brackets ]" << RESET_COLOR << std::endl;
		std::map<char,int> 				std_c0;
		ft::Map<char,int> 				ft_c0;

		// insert some values:
		std_c0['a']=10;
		std_c0['b']=20;
		std_c0['c']=30;
		std_c0['d']=40;
		std_c0['e']=50;
		std_c0['f']=60;
		std_c0['g'];

		ft_c0['a']=10;
		ft_c0['b']=20;
		ft_c0['c']=30;
		ft_c0['d']=40;
		ft_c0['e']=50;
		ft_c0['f']=60;
		ft_c0['g'];
		testMap<char, int>(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Insert with brackets and example Class ]" << RESET_COLOR << std::endl;
		std::map<char,exampleClass> 				std_c0;
		ft::Map<char,exampleClass> 					ft_c0;

		// insert some values:
		std_c0['a']=10;
		std_c0['b']=20;
		std_c0['c']=30;
		std_c0['d']=40;
		std_c0['e']=50;
		std_c0['f']=60;
		std_c0['g'];

		ft_c0['a']=10;
		ft_c0['b']=20;
		ft_c0['c']=30;
		ft_c0['d']=40;
		ft_c0['e']=50;
		ft_c0['f']=60;
		ft_c0['g'];

		if (VALGRIND_MODE == true)
			return ;

		try {
			testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);
		}
		catch (std::exception& e)	{
			std::cout << "Example Class has a default value of 42." << std::endl;
			throw failedTest();
		}
	}
}

void
testBasicErase( void )	{

		std::map<char,exampleClass> 				std_c0;
		ft::Map<char,exampleClass> 					ft_c0;

		// insert some values:
		std_c0['a']=10;
		std_c0['b']=20;
		std_c0['c']=30;
		std_c0['d']=40;
		std_c0['e']=50;
		std_c0['f']=60;
		std_c0['g'];

		ft_c0['a']=10;
		ft_c0['b']=20;
		ft_c0['c']=30;
		ft_c0['d']=40;
		ft_c0['e']=50;
		ft_c0['f']=60;
		ft_c0['g'];

		std::map<char,exampleClass>::iterator		std_it = std_c0.begin();
		ft::Map<char,exampleClass>::iterator		ft_it = ft_c0.begin();
		std::map<char,exampleClass>::iterator		std_ite = std_c0.end();
		ft::Map<char,exampleClass>::iterator		ft_ite = ft_c0.end();

		std::cout << HEADER_TITLE << "[ Erase with position argument ]" << RESET_COLOR << std::endl;
		std_c0.erase(std_it);
		ft_c0.erase(ft_it);
		testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);
		testBool( (--std_ite)->first == (--ft_ite)->first , "", 0, 0);
		std_ite++;
		ft_ite++;

		std::cout << HEADER_TITLE << "[ Erase with key argument ]" << RESET_COLOR << std::endl;
		std_c0.erase('c');
		ft_c0.erase('c');
		std_c0.erase('g');
		ft_c0.erase('g');
		testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);

		std::cout << HEADER_TITLE << "[ Erase with range argument + iterator validity ]" << RESET_COLOR << std::endl;
		std_it = std_c0.begin();
		ft_it = ft_c0.begin();
		std_c0.erase(std_it,std_ite);
		ft_c0.erase(ft_it, ft_ite);
		testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);
}

int
test_map_insert_erase( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;

		std::cout << TITLE << "[ INSERT ]" << RESET_COLOR << std::endl;

		testBracketsInsert();
		testCppRefCode();
		std::cout << TITLE << "[ ERASE ]" << RESET_COLOR << std::endl;
		testBasicErase();
		std::cout << TITLE << "[ INSERT / ERASE ]" << RESET_COLOR << std::endl;
		testInserEraseAdvanced();

		return (0);
}

void add(std::map<int, int> *a, ft::Map<int, int> *b, int k)
{
	(*a)[k] = k;
	(*b)[k] = k;
}
void erase(std::map<int, int> *a, ft::Map<int, int> *b, int k)
{
	a->erase(k);
	b->erase(k);
}

void putData(std::map<int, int> *a, ft::Map<int, int> *b)
{
	add(a, b, 500);
	add(a, b, 200);
	add(a, b, 700);
	add(a, b, 150);
	add(a, b, 250);
	add(a, b, 350);
	add(a, b, 450);
	add(a, b, 550);
	add(a, b, 650);
	add(a, b, 750);
	add(a, b, 850);
	add(a, b, 50);
	add(a, b, 175);
	add(a, b, 625);
	add(a, b, 675);
	add(a, b, 725);
	add(a, b, 100);
	add(a, b, 111);
	add(a, b, 222);
	add(a, b, 333);
	add(a, b, 444);
}

void test(int k)
{
	std::map<int,int> 				std_c0;
	ft::Map<int,int> 				ft_c0;

	putData(&std_c0, &ft_c0);
	erase(&std_c0, &ft_c0, k);
	testMap(ft_c0, std_c0, NOPRINT);

}

int main()
{
	std::map<int,int> 				std_c0;
	ft::Map<int,int> 				ft_c0;

	putData(&std_c0, &ft_c0);
	ft::Map<int, int>::iterator its = ft_c0.begin();
	ft::Map<int, int>::iterator ite = ft_c0.end();

	while (its != ite)
	{
		test(its->first);
		its++;
	}
}
