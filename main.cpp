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

	map.insert(ft::make_pair(300,300));
	map.insert(ft::make_pair(300,300));
	map.insert(ft::make_pair(150,150));
	map.insert(ft::make_pair(580,580));
	map.insert(ft::make_pair(600,600));
	map.insert(ft::make_pair(550,550));
	map.insert(ft::make_pair(530,530));
	map.insert(ft::make_pair(570,570));
/*
	map.erase(580);
	map.erase(550);
	map.erase(570);
	map.erase(600);
	map.erase(530);
	map.erase(150);
	map.erase(300);
	*/
	
	return (0);
}
