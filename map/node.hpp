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
    ft::pair<T1, T2> _data;

    Node() : parent(0), left(0), right(0), color(BLACK), isNull(false), _data(ft::pair<T1,T2>()){}
    Node(const Node& tmp) : parent(tmp.parent), left(tmp.left), right(tmp.right), color(tmp.color), isNull(tmp.isNull), _data(tmp._data) { }
    Node(const ft::pair<T1,T2> tmp) : parent(0), left(0), right(0), color(BLACK), isNull(false), _data(tmp) {}

    Node& operator=(const Node& tmp)
    {
        parent = tmp.parent;
        left = tmp.left;
        right = tmp.right;
        color = tmp.color;
        isNull = tmp.isNull;
        _data = tmp._data;
        return *this;
    }

    const Node<T1, T2>* getNext() const
    {
        Node<T1, T2> *biggerParent;

        if (isNull)
            return this;

        if (right->isNull == true)
        {
            biggerParent = getBiggerParent(this);
            if (biggerParent == 0)
                return right;
            else
                return biggerParent;
        }
        else
        {
            return findSmallestSubtree(right);
        }
    }

    const Node<T1, T2> *getPrev() const
    {
        Node<T1, T2> *lowerParent;

        if (isNull)
            return parent;
        if (left->isNull == true && *this < *parent)
        {
            lowerParent = const_cast<Node<T1,T2> *>(this);
            while (lowerParent->parent)
                lowerParent = lowerParent->parent;
            while (lowerParent->left)
            {
                lowerParent = lowerParent->left;
                if (lowerParent->left->isNull == true)
                    break;
            }
            if (lowerParent == this)
                return this;
        }

        if (left->isNull == true)
        {
            lowerParent = getLowerParent(const_cast<Node<T1,T2>*>(this));
            if (lowerParent == 0)
                return left;
            else
                return lowerParent;
        }
        else
        {
            return findLargestSubtree(left);
        }
    }

    ft::pair<T1, T2>& operator*()
    {
        return _data;
    }

    ft::pair<T1, T2>* operator->()
    {
        return &_data;
    }

    void setData(ft::pair<T1,T2> tmp)
    {
        _data = tmp;
    }

    ft::pair<T1,T2>& getData()
    {
        return _data;
    }

private:
    Node<T1, T2> *findLargestSubtree(Node<T1, T2> *subtree) const
    {
        while (subtree->right->isNull == false)
        {
            subtree = subtree->right;
        }
        return subtree;
    }

    Node<T1, T2> *findSmallestSubtree(Node<T1, T2> *subtree) const
    {
        while (subtree->left->isNull == false)
        {
            subtree = subtree->left;
        }
        return subtree;
    }

    Node<T1, T2> *getLowerParent(Node<T1, T2> *tmp) const
    {
        Node<T1, T2> *parent;

        parent = tmp->parent;
        while (*tmp < *(parent))
        {
            parent = parent->parent;
            if (parent == 0)
                return 0;
        }
        return parent;
    }

    Node<T1, T2> *getBiggerParent(const Node<T1, T2> *tmp) const
    {
        Node<T1, T2> *parent;

        parent = tmp->parent;
        while (*tmp > *(parent))
        {
            parent = parent->parent;
            if (parent == 0)
                return 0;
        }
        return parent;
    }

    
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

#endif