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


int main()
{

	std::allocator<ft::pair<int, int> > alloc;
	RBTree<int, int> rb(alloc);
	ft::Map<int, int> map;

	ft::Map<char,int> mymap;

	mymap['a']=10;
  	mymap['b']=20;
  	mymap['c']=30;

	ft::Map<char,int>::reverse_iterator rit = mymap.rbegin();
	ft::Map<char,int>::reverse_iterator rend = mymap.rend();

	while (rit != rend)
	{
		std::cout << rit->first << std::endl;
		rit++;
	}
	std::cout << rit->first << std::endl;
	return (0);
}