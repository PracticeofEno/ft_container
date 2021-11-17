#include <vector>
#include "vector.hpp"
#include <math.h>
#include <algorithm>
#include "exampleClass.hpp"
#include "compClass.hpp"

void
putVector( ft::vector<float> const & vct, int errorPos = -1 )	{

	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;
	 ft::vector<float>::const_iterator it = vct.begin();
	 ft::vector<float>::const_iterator ite = vct.end();

	int	printMax;

	if (vct.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(vct.size());
	for (int i = 0; vct.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(vct.size()))
			std::cout <<  "ft: [" << i << "] " <<  *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "ft: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(vct.size()))
		std::cout << " !!\t vector size is too large to print... stoping here." << std::endl;
}

void
putVector( std::vector<float> const & vct, int errorPos = -1 )	{
	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;
	std::vector<float>::const_iterator it = vct.begin();
	std::vector<float>::const_iterator ite = vct.end();

	int	printMax;

	if (vct.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(vct.size());
	for (int i = 0; vct.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(vct.size()))
			std::cout << "std: [" << i << "] " <<  *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "std: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(vct.size()))
		std::cout << " !!\t vector size is too large to print... stoping here." << std::endl;
}

void
testVector( ft::vector<float> const & ft_vct, std::vector<float> const &std_vct,
bool print, std::string message = "" )	{

	bool	success = true;
    (void)message;
	if (print == true)
	{
		putVector(ft_vct);
		putVector(std_vct);
	}

	if(ft_vct.size() != std_vct.size())	{
		if (print == false && success == true)
		{
			putVector(ft_vct);
			putVector(std_vct);
		}
		else
			success = false;
	}

	if (ft_vct.size() > 0)
	{
		int i = 0;
		 ft::vector<float>::const_iterator	ft_it = ft_vct.begin();
		 ft::vector<float>::const_iterator	ft_ite = ft_vct.end();

		 std::vector<float>::const_iterator	std_it = std_vct.begin();
		 std::vector<float>::const_iterator	std_ite = std_vct.end();
		while (ft_it != ft_ite && std_it != std_ite)	{

			if(*ft_it != *std_it)	{
				if (print == false && success == true)
				{
					putVector(ft_vct, i);
					putVector(std_vct, i);
				}
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
				putVector(ft_vct);
				putVector(std_vct);
			}
			else
				success = false;
		}
	}
}

template < typename T >
void
testResize(ft::vector<T> & ft_c0, std::vector<T> & std_c0, size_t testSize, int value = 0)	 {

		if (value == 0)
			std::cout <<  "[ resize to " << testSize << " with no value ]" << std::endl;
		else
			std::cout << "[ resize to " << testSize << " with value " << value << " ]" << std::endl;

		ft_c0.resize(testSize, value);
		std_c0.resize(testSize, value);
		testVector(ft_c0, std_c0, "");
}

bool	testBool(bool b, const char * file, int const lineNo, int const loopIter )	{
	if (b == true)
		std::cout << "[ TEST PASSED: no diff ] \t \342\234\205" << std::endl;
	else	{
		std::cout <<  "[ FAILURE at " << file << ":" << lineNo << "]" << " \t \342\235\214"  << std::endl;
		if (loopIter != -1)
			std::cout << " loop iteration = " << loopIter << "." <<  " \t \342\235\214" << std::endl;
	}
	return (b);
}


void
testReserve(size_t testSize, ft::vector<float> & ft_c0, std::vector<float> & std_c0)	 {
		std::cout <<  "[ reserve("<< testSize << ") ]" << std::endl;

		ft_c0.reserve(testSize);
		std_c0.reserve(testSize);
		testVector(ft_c0, std_c0, "");
		std::cout << "New Capacities after reserve: ft(" << ft_c0.capacity() << ") ; std(" << std_c0.capacity() << ")" << std::endl;
		std::cout << (ft_c0.capacity() >= testSize && std_c0.capacity() >= testSize) << std::endl;
}

int main()
{
	std::cout <<  "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" <<  std::endl;
	{
		std::cout <<  "TEST CLEAR FUNCTION with vector of 1000000 floats" <<  std::endl;
		ft::vector<float> ft_c0 (1000000, 42.21f);
		std::vector<float> std_c0 (1000000, 42.21f);

		testVector(ft_c0, std_c0, "");
		ft_c0.clear();
		std_c0.clear();
		testVector(ft_c0, std_c0, "");

		std::cout << "TEST Clear with forced reallocation by swapping with a default constructed vector" <<  std::endl;
		ft::vector<float>().swap(ft_c0);
		std::vector<float>().swap(std_c0);
		testVector(ft_c0, std_c0, "");
		testBool(ft_c0.capacity() == std_c0.capacity(), "", -1, -1);
	}
	return (0);
}