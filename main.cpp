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
	RBTree<int, int> _rb(alloc);

	//ft::Map<int, int>::iterator tmp;
	ft::pair<int, int> tmp;
	std::cout << tmp.first << std::endl;

	Node<int, int> a(ft::make_pair(300,300));
	Node<int, int> b(ft::make_pair(150,150));
	Node<int, int> c(ft::make_pair(580,580));
	Node<int, int> d(ft::make_pair(600,600));
	Node<int, int> e(ft::make_pair(550,550));
	Node<int, int> f(ft::make_pair(530,530));
	Node<int, int> g(ft::make_pair(570,570));

	_rb.insert(&a);
	_rb.insert(&b);
	_rb.insert(&c);
	_rb.insert(&d);
	_rb.insert(&e);
	_rb.insert(&f);
	_rb.insert(&g);

	_rb.erase(580);
	_rb.erase(550);
	_rb.erase(570);
	_rb.erase(600);
	_rb.erase(530);
	_rb.erase(150);
	_rb.erase(300);
	
	return (0);
}
