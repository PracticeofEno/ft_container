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
	RBTree<ft::pair<char, int> > _rb;

	Node<ft::pair<char, int> > a(ft::make_pair('5',5));
	Node<ft::pair<char, int> > b(ft::make_pair('3',3));
	Node<ft::pair<char, int> > c(ft::make_pair('8',8));
	Node<ft::pair<char, int> > d(ft::make_pair('2',2));
	Node<ft::pair<char, int> > e(ft::make_pair('1',1));

	_rb.insert(&a);
	_rb.insert(&b);
	_rb.insert(&c);
	_rb.insert(&d);
	_rb.insert(&e);

	
	return (0);
}
