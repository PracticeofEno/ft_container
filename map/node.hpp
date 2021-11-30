#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#define RED 1
#define BLACK 2
#define DBLACK 3

template <class T>
class Node
{
public:
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;
    int color;
    bool isLeaf;
    T _data;

    Node() : parent(0), left(0), right(0), color(BLACK), isLeaf(false), _data(T()) { }
    Node(T data) : parent(0), left(0), right(0), color(RED), isLeaf(false) { _data = data; }

    Node<T>& operator=(Node<T>& tmp)
    {
        parent = tmp.parent;
        left = tmp.left;
        right = tmp.right;
        color = tmp.color;
        isLeaf = tmp.isLeaf;
        _data = tmp._data;
    }

private:
    
};

template <class T>
bool operator==(const Node<T> &lhs, const Node<T> &rhs)
{
    return lhs._data.first == rhs._data.first && lhs._data.second == rhs._data.second;
}

template <class T>
bool operator!=(const Node<T> &lhs, const Node<T> &rhs)
{
    return !(lhs == rhs);
}

template <class T>
bool operator<(const Node<T> &lhs, const Node<T> &rhs)
{
    return lhs._data.first < rhs._data.first || (!(rhs._data.first < lhs._data.first) && lhs._data.second < rhs._data.second);
}

template <class T>
bool operator<=(const Node<T> &lhs, const Node<T> &rhs)
{
    return !(rhs < lhs);
}

template <class T>
bool operator>(const Node<T> &lhs, const Node<T> &rhs)
{
    return rhs < lhs;
}

template <class T>
bool operator>=(const Node<T> &lhs, const Node<T> &rhs)
{
    return !(lhs < rhs);
}

template <class T>
void contentSwap(Node<T> &lhs, Node<T> &rhs)
{
    T tmp;
    
    tmp = lhs._data;
    lhs._data = rhs._data;
    rhs._data = tmp;

}

#endif