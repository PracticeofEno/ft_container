#include <vector>
#include "vector.hpp"
#include <math.h>
#include <algorithm>
#include "exampleClass.hpp"
#include "compClass.hpp"


void
putVector( ft::vector<std::string> const & vct, int errorPos = -1 )	{

	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;
	 ft::vector<std::string>::const_iterator it = vct.begin();
	 ft::vector<std::string>::const_iterator ite = vct.end();

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
putVector( std::vector<std::string> const & vct, int errorPos = -1 )	{
	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;
	std::vector<std::string>::const_iterator it = vct.begin();
	std::vector<std::string>::const_iterator ite = vct.end();

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
testVector( ft::vector<std::string> const & ft_vct, std::vector<std::string> const &std_vct,
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
		 ft::vector<std::string>::const_iterator	ft_it = ft_vct.begin();
		 ft::vector<std::string>::const_iterator	ft_ite = ft_vct.end();

		 std::vector<std::string>::const_iterator	std_it = std_vct.begin();
		 std::vector<std::string>::const_iterator	std_ite = std_vct.end();
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
testReserve(size_t testSize, ft::vector<std::string> & ft_c0, std::vector<std::string> & std_c0)	 {
		std::cout <<  "[ reserve("<< testSize << ") ]" << std::endl;

		ft_c0.reserve(testSize);
		std_c0.reserve(testSize);
		testVector(ft_c0, std_c0, "");
		std::cout << "New Capacities after reserve: ft(" << ft_c0.capacity() << ") ; std(" << std_c0.capacity() << ")" << std::endl;
		std::cout << (ft_c0.capacity() >= testSize && std_c0.capacity() >= testSize) << std::endl;
}

int main()
{
	{
		std::cout <<  "[ Instanciate vector of 4 strings ]"  << std::endl;
		ft::vector<std::string>		ft_c0(4, "___");
		std::vector<std::string>	std_c0(4, "___");
		ft::vector<std::string>::iterator	ft_ret;
		std::vector<std::string>::iterator	std_ret;
		testVector(ft_c0, std_c0, "");


		std::cout <<  "[ Insert with insert(iterator, value) ]"  << std::endl;

		ft_ret = ft_c0.insert(ft_c0.begin(), "A");
		std_ret = std_c0.insert(std_c0.begin(), "A");
		std::cout << (*ft_ret == *std_ret) << std::endl;
		testVector(ft_c0, std_c0, "");

		ft_ret = ft_c0.insert(ft_c0.begin(), "B");
		std_ret = std_c0.insert(std_c0.begin(), "B");
		std::cout << (*ft_ret == *std_ret) << std::endl;
		testVector(ft_c0, std_c0, "");

		ft_ret = ft_c0.insert(ft_c0.begin(), "42");
		std_ret = std_c0.insert(++std_c0.begin(), "42");
		std::cout << (*ft_ret == *std_ret) << std::endl;
		testVector(ft_c0, std_c0, "");

		ft_ret = ft_c0.insert(--ft_c0.end(), "The End...");
		std_ret = std_c0.insert(--std_c0.end(), "The End...");
		std::cout << (*ft_ret == *std_ret) << std::endl;
		testVector(ft_c0, std_c0, "");

		ft_ret = ft_c0.insert(ft_c0.end(), "End...");
		std_ret = std_c0.insert(std_c0.end(), "End...");
		std::cout << (*ft_ret == *std_ret) << std::endl;
		testVector(ft_c0, std_c0, "");

		ft_ret = ft_c0.insert(ft_c0.begin() + ft_c0.size() / 2, "middle...");
		std_ret = std_c0.insert(std_c0.begin() + std_c0.size() / 2, "middle...");
		std::cout << (*ft_ret == *std_ret) << std::endl;
		testVector(ft_c0, std_c0, "");


		std::cout <<  "[ test return of insert function ]"  << std::endl;
		std::cout << (*(ft_c0.insert(++ft_c0.begin(), "Return_this")) == *(std_c0.insert(++std_c0.begin(), "Return_this"))) << std::endl;
		
	}
}