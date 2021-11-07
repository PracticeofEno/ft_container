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

	std::cout << k.capacity() << std::endl;
	k.insert(k.begin() + 1, 5);
	//k2.insert(k2.begin() + 1, 5);
	std::cout << "k : " << k.capacity() << " | " << "k2 : " << k2.capacity() << std::endl;
	k.insert(k.begin() + 1, 5, 10);
	for (std::vector<int>::iterator it = k.begin(); it < k.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	k2.insert(k2.begin() + 1, 5, 10);
	for (std::vector<int>::iterator it = k.begin(); it < k.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "-----------------------" << std::endl;
	//for (ft::vector<int>::iterator it = k2.begin(); it < k2.end(); it++)
		//std::cout << *it << " ";
	return (0);
}