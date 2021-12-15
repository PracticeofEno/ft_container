#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#define RED 1
#define BLACK 2
#define DBLACK 3

template <class T1, class T2>
class Node
{
public:
    Node<T1, T2> *parent;
    Node<T1, T2> *left;
    Node<T1, T2> *right;
    int color;
    bool isNull;
    ft::pair<T1,T2> _data;

    Node() : parent(0), left(0), right(0), color(BLACK), isNull(false), _data(ft::pair<T1,T2>()) { }
    Node(ft::pair<T1, T2>  data) : parent(0), left(0), right(0), color(RED), isNull(false) { _data = data; }

    Node<T1, T2>& operator=(Node<T1, T2> & tmp)
    {
        parent = tmp.parent;
        left = tmp.left;
        right = tmp.right;
        color = tmp.color;
        isNull = tmp.isNull;
        _data = tmp._data;
        return *this;
    }

private:
    
};

template <class T1, class T2>
bool operator==(const Node<T1, T2> &lhs, const Node<T1, T2> &rhs)
{
    return lhs._data.first == rhs._data.first && lhs._data.second == rhs._data.second;
}

template <class T1, class T2>
bool operator!=(const Node<T1, T2> &lhs, const Node<T1, T2> &rhs)
{
    return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const Node<T1, T2> &lhs, const Node<T1, T2> &rhs)
{
    return lhs._data.first < rhs._data.first || (!(rhs._data.first < lhs._data.first) && lhs._data.second < rhs._data.second);
}

template <class T1, class T2>
bool operator<=(const Node<T1, T2> &lhs, const Node<T1, T2> &rhs)
{
    return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const Node<T1, T2> &lhs, const Node<T1, T2> &rhs)
{
    return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const Node<T1, T2> &lhs, const Node<T1, T2> &rhs)
{
    return !(lhs < rhs);
}

template <class T1, class T2>
void contentSwap(Node<T1, T2> &lhs, Node<T1, T2> &rhs)
{
    ft::pair<T1,T2> tmp;
    
    tmp = lhs._data;
    lhs._data = rhs._data;
    rhs._data = tmp;

}

#endif