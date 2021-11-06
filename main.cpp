#include <vector>
#include "vector.hpp"
#include <math.h>
#include <algorithm>

int main()
{
	std::vector<int> k;
	k.push_back(1);
	k.push_back(2);
	k.push_back(3);
	k.push_back(4);
	k.push_back(5);

	ft::vector<int> k2;
	k2.push_back(1);
	k2.push_back(2);
	k2.push_back(3);
	k2.push_back(4);
	k2.push_back(5);
	k.insert(k.begin() + 1, 5);
	k2.insert(k2.begin() + 1, 5);
	std::cout << "k : " << k.capacity() << " | " << "k2 : " << k2.capacity() << std::endl;
	k.insert(k.begin() + 1, 5, 10);
	k2.insert(k2.begin() + 1, 5, 10);
	for (std::vector<int>::iterator it = k.begin(); it < k.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "-----------------------" << std::endl;
	for (ft::vector<int>::iterator it = k2.begin(); it < k2.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << k.size() << std::endl;
	std::cout << k.capacity() << std::endl;
	std::cout << *k.end() << std::endl;

	std::vector<int>::reverse_iterator it(k.begin() + 4);
	std::vector<int>::reverse_iterator it2(k.begin());
	std::cout << "k.begin() = "<< *k.begin() << std::endl;
	std::cout << "reverse iterator k.begin() + 4 *it, it[2] = "<< *it << " | " << it[2] << std::endl;
	std::cout << "reverse iterator k.begin() + 1 *it2, it2[2] = "<<*it2 << " | " << *(it2 - 1) << std::endl;

	std::cout << ft::is_integral<int>::value << std::endl;
	std::cout << ft::is_integral<ft::vector<int> >::value << std::endl;


	return (0);
}